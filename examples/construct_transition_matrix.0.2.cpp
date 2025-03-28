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
#include "utils/scan_matrix.h"

using namespace csv;

// Load U and S tables (clean form - without labels)
// Concatenate them into a single matrix
//   - putting the S, U pieces together (block operations)
//   - adding additional entries (manual)
// Normalize entries to create probability matrix

int main(int num_args, char **arg_strings) {

    // STEP 1: LOAD SUPPLY MATRIX
    constexpr int MAX = 2944;
    Eigen::MatrixXd S(MAX, MAX);
    CSVReader reader1("../data/supply.csv");

    double value = 0;
    int i = 0;
    for (auto &row: reader1) {
        for (int j = 0; j < MAX; j++) {
            value =
            S(i, j) = row[j].get<double>();
        }
        i++;
    }

    std::cout << "Loaded Supply Matrix" << std::endl;
    std::cout << "FIGARO Supply Matrix of Total Size: " << S.size() << std::endl;
    std::cout << "FIGARO Supply Matrix with Rows: " << S.rows() << std::endl;
    std::cout << "FIGARO Supply Matrix with Columns: " << S.cols() << std::endl;
    std::cout << "FIGARO Supply Matrix Checksum: " << S.sum() << std::endl;

    // STEP 2: LOAD USE MATRIX

    constexpr int MAX_ROW = 2950;
    constexpr int MAX_COL = 3174;

    Eigen::MatrixXd UP(MAX_ROW, MAX_COL);

    CSVReader reader2("../data/use.csv");

    i = 0;
    for (auto &row: reader2) {
        for (int j = 0; j < MAX_COL; j++) {
                UP(i, j) = row[j].get<double>();
            }
        i++;
    }

    std::cout << "Loaded Use Matrix" << std::endl;
    std::cout << "FIGARO Use Matrix of Total Size: " << UP.size() << std::endl;
    std::cout << "FIGARO Use Matrix with Rows: " << UP.rows() << std::endl;
    std::cout << "FIGARO Use Matrix with Columns: " << UP.cols() << std::endl;
    std::cout << "FIGARO Use Matrix Checksum: " << UP.sum() << std::endl;

    constexpr int FD = 230;
    constexpr int VA = 6;
    Eigen::MatrixXd U = CompactifyUseMatrix(UP, FD, VA);

    std::cout << "Compactified Use Matrix" << std::endl;
    std::cout << "New Use Matrix with Rows: " << U.rows() << std::endl;
    std::cout << "New Use Matrix with Columns: " << U.cols() << std::endl;
    std::cout << "New Use Matrix Checksum: " << U.sum() << std::endl;

    int IO = S.cols();

    // Construct SUT system
    SUTSystem figaro;
    figaro.CreateTransactionsMatrix(S, U);
    std::cout << "Combined Matrix Checksum: " << figaro.getW().sum() << std::endl;
    std::cout << "Component Checksum: " << S.sum() + U.sum() << std::endl;

    figaro.CreateUpstreamProbabilities(IO, IO);

    // std::cout << figaro.getQu() << std::endl;

    std::cout << "Constructed Probability Matrix" << std::endl;
    std::cout << "Number of Rows: " << figaro.getQu().rows() << std::endl;
    std::cout << "Number of Columns: " << figaro.getQu().cols() << std::endl;
    std::cout << "Column-wise norm check: " << TestColumnNorm(figaro.getQu()) << std::endl;
    std::cout << "Probability check: " << TestProbabilities(figaro.getQu()) << std::endl;

    const static Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n");
    std::ofstream file("../data/figaro_qu.csv");
    file << figaro.getQu().format(CSVFormat);

    return 0;
}
