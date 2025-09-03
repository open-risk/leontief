/*
* This file is part of the Leontief distribution (https://github.com/open-risk/leontief).
* Copyright (c) 2024 - 2025 Open Risk (https://www.openriskmanagement.com)
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <fstream>
#include "utils/csv.h"
#include "core/sut_system.h"
#include "utils/compactify_use_matrix.h"
#include "utils/io_matrix_generation.h"
#include "utils/scan_matrix.h"

using namespace csv;

/*
 *  # EXAMPLE 3: Construct Transition Matrix
 */

// Create Upstream Transition Probabilities Matrix
//
// Load U and S tables (clean form - without labels)
// Transpose S matrix
// Split Use Table into U, VA and FD matrices
// Concatenate VA and FD matrices in vectors sums VAS, FDS
// Concatenate U, VA, FD into a single matrix (block operation)
// Put the S, U pieces together (block operation)
// Add additional (VA sink node)
// Normalize entries to create probability matrix

/**
 * @brief
 * @param num_args
 * @param arg_strings
 * @return
 */
int main(int num_args, char **arg_strings) {

    // STEP 1: CONFIGURATION

    // MILLER-BLAIR SYSTEM
    // constexpr int SROWS = 2;
    // constexpr int SCOLS = 2;
    // constexpr int UROWS = 3;
    // constexpr int UCOLS = 3;
    // constexpr int FD = 1;
    // constexpr int VA = 1;

    // FIGARO SYSTEM
    constexpr int SROWS = 2944;
    constexpr int SCOLS = 2944;
    constexpr int UROWS = 2950;
    constexpr int UCOLS = 3174;
    constexpr int FD = 230;
    constexpr int VA = 6;
    CSVReader reader1("../data/supply.csv");
    CSVReader reader2("../data/use.csv");

    // FIGARO-E3
    // constexpr int UROWS = 9809;
    // constexpr int UCOLS = 8096;
    // constexpr int SROWS = 9798;
    // constexpr int SCOLS = 8096;
    // constexpr int FD = 230;
    // constexpr int VA = 11;
    // CSVReader reader1("../data/supply-e3.csv");
    // CSVReader reader2("../data/use-e3.csv");

    Eigen::MatrixXd S(SROWS, SCOLS);
    Eigen::MatrixXd M(SCOLS, SROWS);
    Eigen::MatrixXd UP(UROWS, UCOLS);

    // STEP 2: SET OR LOAD SUPPLY / USE MATRIX

    // S = TestSupplyMatrix(SROWS, SCOLS, 2);
    // UP = TestUseMatrix(SROWS, SCOLS, 2);

    double value = 0;
    int i = 0;
    for (auto &row: reader1) {
        for (int j = 0; j < SCOLS; j++) {
            value = S(i, j) = row[j].get<double>();
        }
        i++;
    }
    i = 0;
    for (auto &row: reader2) {
        for (int j = 0; j < UCOLS; j++) {
                UP(i, j) = row[j].get<double>();
            }
        i++;
    }

    M = S.transpose();

    std::cout << "------------- Supply Matrix" << std::endl;
    std::cout << "Supply Matrix of Total Size: " << S.size() << std::endl;
    std::cout << "Supply Matrix with Rows: " << S.rows() << std::endl;
    std::cout << "Supply Matrix with Columns: " << S.cols() << std::endl;
    std::cout << "Supply Matrix Checksum: " << S.sum() << std::endl;
    std::cout << "------------- Use Matrix" << std::endl;
    std::cout << "Use Matrix of Total Size: " << UP.size() << std::endl;
    std::cout << "Use Matrix with Rows: " << UP.rows() << std::endl;
    std::cout << "Use Matrix with Columns: " << UP.cols() << std::endl;
    std::cout << "Use Matrix Checksum: " << UP.sum() << std::endl;

    // STEP 3: FIX ZERO COLUMN ISSUE AND NEGATIVE VALUE ISSUES
    std::random_device rd;
    std::mt19937 rng(rd());

    std::uniform_int_distribution<int> uni1(0, SROWS);
    auto col_sum = M.colwise().sum();
    for (int j = 0; j < M.cols(); j++) {
        if (col_sum(j) == 0) {
            auto row = uni1(rng);
            M(row, j) = 1.0;
        }
    }
    std::uniform_int_distribution<int> uni2(0, UROWS);
    auto col_sum2 = UP.colwise().sum();
    for (int j = 0; j < UP.cols(); j++) {
        if (col_sum2(j) == 0) {
            auto row = uni2(rng);
            UP(row, j) = 1.0;
        }
    }

    for (int i = 0; i < M.rows(); i++) {
        for (int j = 0; j < M.cols(); j++) {
            if (M(i, j) < 0.0) {
                M(i, j) = abs(M(i, j));
            }
        }
    }

    for (int i = 0; i < UP.rows(); i++) {
        for (int j = 0; j < UP.cols(); j++) {
            if (UP(i, j) < 0.0) {
                UP(i, j) = abs(UP(i, j));
            }
        }
    }

    std::cout << "Column-wise norm check M: " << TestColumnSum(M) << std::endl;
    std::cout << "Adjusted Make Matrix Checksum: " << M.sum() << std::endl;
    std::cout << "Column-wise norm check UP: " << TestColumnSum(UP) << std::endl;
    std::cout << "Adjusted Use Matrix Checksum: " << UP.sum() << std::endl;

    // STEP 4: COMPACTIFY USE MATRIX
    Eigen::MatrixXd U = CompactifyUseMatrix(UP, FD, VA);
    std::cout << "Compactified Use Matrix" << std::endl;
    std::cout << "Column-wise norm check U: " << TestColumnSum(U) << std::endl;
    std::cout << "New Use Matrix with Rows: " << U.rows() << std::endl;
    std::cout << "New Use Matrix with Columns: " << U.cols() << std::endl;
    std::cout << "New Use Matrix Checksum: " << U.sum() << std::endl;

    // STEP 5: Construct SUT system
    SUTSystem figaro;
    figaro.CreateTransactionsMatrix(M, U);
    std::cout << "Combined Matrix Checksum: " << figaro.getW().sum() << std::endl;
    std::cout << "Component Checksum: " << M.sum() + U.sum() << std::endl;
    std::cout << "Checksum Difference: " << M.sum() + U.sum() - figaro.getW().sum() << std::endl;
    std::cout << "Positivity check: " << TestPositivity(figaro.getW()) << std::endl;
    // std::cout << figaro.getW() << std::endl;

    int unitRow = U.rows() - 1;
    int unitCol = M.cols();
    std::cout << "Unit Row: " << unitRow << std::endl;
    std::cout << "Unit Col: " << unitCol << std::endl;
    figaro.CreateUpstreamProbabilities(unitRow, unitCol);
    std::cout << "Probability Sum: " << figaro.getQu().sum() << std::endl;
    // std::cout << figaro.getQu() << std::endl;

    std::cout << "Constructed Probability Matrix" << std::endl;
    std::cout << "Q Matrix with Rows: " << figaro.getQu().rows() << std::endl;
    std::cout << "Q with Columns: " << figaro.getQu().cols() << std::endl;
    std::cout << "Column-wise norm check Q: " << TestColumnNorm(figaro.getQu()) << std::endl;
    std::cout << "Probability check: " << TestProbabilities(figaro.getQu()) << std::endl;

    const static Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n");
    std::ofstream file("../data/figaro_qu.csv");
    // std::ofstream file("../data/test_qu.csv");
    file << figaro.getQu().format(CSVFormat);

    return 0;
}
