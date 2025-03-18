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
#include <map>
#include <random>
#include "utils/csv.h"
#include "core/sut_system.h"
#include "utils/check_norms.h"
#include "utils/matrix_generation.h"
#include "utils/compactify_use_matrix.h"

using namespace csv;

int main(int num_args, char **arg_strings) {

    // Initialize SUT System
    // Total Output vector
    // Emission Densities
    // f = E.array() / X.array();

    // TEST 1 INPUTS
    // int IO = 10;
    // int FD = 1;
    // int VA = 1;
    // Eigen::MatrixXd S = TestSupplyMatrix(IO, 0);
    // Eigen::MatrixXd U = TestUseMatrix(IO, FD, VA, 0);

    // TEST 2 INPUTS
    // int Sectors = 6;
    // int IO = 2;
    // int FD = 1;
    // int VA = 1;
    // Eigen::MatrixXd S = TestSupplyMatrix(IO, 1);
    // Eigen::MatrixXd U = TestUseMatrix(IO, FD, VA, 1);
    // Eigen::VectorXd Intensity(Sectors); // Impact intensity
    // Intensity << 0.5, 0.33, 0, 0, 0, 0;

    // LOAD SUPPLY MATRIX
    constexpr int MAX = 2944;
    Eigen::MatrixXd S(MAX, MAX);
    CSVReader reader1("../data/matrix_eu-ic-supply_24ed_2022.csv");

    double value = 0;
    std::string label;
    int i = 0;
    for (auto &row: reader1) {
        for (int j = 0; j < MAX+1; j++) {
            if (i > 0 && j > 0) {
                value = row[j].get<double>();
                S(i-1, j-1) = value;
            } else {
                label = row[j].get_sv();
            }
        }
        i++;
    }

    std::cout << "Loaded Supply Matrix" << std::endl;
    std::cout << "FIGARO Supply Matrix of Total Size: " << S.size() << std::endl;
    std::cout << "FIGARO Supply Matrix with Rows: " << S.rows() << std::endl;
    std::cout << "FIGARO Supply Matrix with Columns: " << S.cols() << std::endl;

    constexpr int MAX_ROW = 2950;
    constexpr int MAX_COL = 3174;

    Eigen::MatrixXd UP(MAX_ROW, MAX_COL);

    CSVReader reader2("../data/matrix_eu-ic-use_24ed_2022.csv");

    i = 0;
    for (auto &row: reader2) {
        for (int j = 0; j < MAX_COL + 1; j++) {
            if (j > 0) {
                value = row[j].get<double>();
                UP(i, j - 1) = value;
            } else {
                label = row[j].get_sv();
            }
        }
        i++;
    }

    std::cout << "Loaded Use Matrix" << std::endl;
    std::cout << "FIGARO Use Matrix of Total Size: " << UP.size() << std::endl;
    std::cout << "FIGARO Use Matrix with Rows: " << UP.rows() << std::endl;
    std::cout << "FIGARO Use Matrix with Columns: " << UP.cols() << std::endl;

    constexpr int FD = 230;
    constexpr int VA = 6;
    Eigen::MatrixXd U = CompactifyUseMatrix(UP, FD, VA);

    std::cout << "Compactified Use Matrix" << std::endl;
    std::cout << "New Use Matrix with Rows: " << U.rows() << std::endl;
    std::cout << "New Use Matrix with Columns: " << U.cols() << std::endl;

    int Sectors = S.cols() + U.cols();
    int IO = S.cols();

    // Construct SUT system
    SUTSystem testSUT;
    testSUT.CreateTransactionsMatrix(S, U);
    testSUT.CreateUpstreamProbabilities(IO, IO);

    // std::cout << testSUT.getQu() << std::endl;

    std::cout << "Constructed Probability Matrix" << std::endl;
    std::cout << "Column-wise norm check: " << TestColumnNorm(testSUT.getQu()) << std::endl;

    // Construct Markov Chain from Transition Matrix
    // input is the upstream transition probabilities Qu

    Eigen::VectorXd weights(Sectors);
    std::map<int, std::discrete_distribution<> > prob_vector;
    for (int j = 0; j < Sectors; j++) {
        double col_sum = 0;
        for (int ii = 0; ii < Sectors; ii++) {
            col_sum += testSUT.getQu()(ii, j);
            weights[ii] = testSUT.getQu()(ii, j);
        }
        std::discrete_distribution<int> d(weights.begin(), weights.end());
        prob_vector[j] = d;
    }

    std::cout << "Constructed Markov Chain" << std::endl;

    int Scenarios = 1;

    // Here the weights are from Q columns and the integers are from the sector index

    std::random_device rd;
    std::mt19937 gen(rd());

    int Steps = 7;

    Eigen::VectorXd Intensity(Sectors); // Impact intensity
    Intensity.setOnes();

    Eigen::VectorXd Impact(Steps);
    Impact.setZero();

    for (int fs = 0; fs < Scenarios; fs++) {
        int old_state = 400;
        int k = 0; // Step Count
        // While not absorbed
        while (old_state != 2 && k < Steps) {
            // Compute Next Node
            int new_state = prob_vector[old_state](gen);
            // Compute Impact Intensity
            std::cout << "Step " << k << " : from " << old_state << " to " << new_state << " with impact " << Intensity[new_state] << std::endl;
            Impact[k] += Intensity[new_state];
            old_state = new_state;
            k += 1;
        }
    }
    std::cout << "Simulate" << std::endl;
    // std::cout << Impact / Scenarios << std::endl;
}
