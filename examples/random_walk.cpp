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

#include "core/sut_system.h"
#include "utils/matrix_generation.h"

int main(int num_args, char **arg_strings) {

    // Initialize SUT System
    // Total Output vector
    // Emission Densities
    // f = E.array() / X.array();

    // TEST 1
    // int IO = 10;
    // int FD = 1;
    // int VA = 1;
    // Eigen::MatrixXd S = TestSupplyMatrix(IO, 0);
    // Eigen::MatrixXd U = TestUseMatrix(IO, FD, VA, 0);

    // TEST 2 INPUTS
    int Sectors = 6;
    int IO = 2;
    int FD = 1;
    int VA = 1;
    Eigen::MatrixXd S = TestSupplyMatrix(IO, 1);
    Eigen::MatrixXd U = TestUseMatrix(IO, FD, VA, 1);

    // Construct SUT system
    SUTSystem testSUT;
    testSUT.CreateTransactionsMatrix(S, U);
    testSUT.CreateUpstreamProbabilities(IO, IO);

    std::cout << testSUT.getQu() << std::endl;

    // Construct Markov Chain from Transition Matrix
    // input is the upstream transition probabilities Qu

    Eigen::VectorXd weights(Sectors);
    std::map<int, std::discrete_distribution<> > prob_vector;
    for (int j = 0; j < Sectors; j++) {
        double col_sum = 0;
        for (int i = 0; i < Sectors; i++) {
            col_sum += testSUT.getQu()(i, j);
            weights[i] = testSUT.getQu()(i, j);
        }
        std::discrete_distribution<int> d(weights.begin(), weights.end());
        prob_vector[j] = d;
        // std::cout << j << " " << col_sum << std::endl;
    }

    int Scenarios = 100000;

    // Here the weights are from Q columns and the integers are from the sector index

    std::random_device rd;
    std::mt19937 gen(rd());

    int Steps = 7;

    Eigen::VectorXd Intensity(Sectors); // Impact intensity
    Intensity << 0.5, 0.33, 0, 0, 0, 0;

    // Eigen::VectorXi State(Scenarios);

    Eigen::VectorXd Impact(Steps);
    Impact.setZero();

    for (int fs = 0; fs < Scenarios; fs++) {
        int old_state = 4;
        int k = 0; // Step Count
        // While not absorbed
        while (old_state != 2 && k < Steps) {
            // Compute Next Node
            int new_state = prob_vector[old_state](gen);
            // Compute Impact Intensity
            // std::cout << "Step " << k << " : from " << old_state << " to " << new_state << " with impact " << Intensity[new_state] << std::endl;
            Impact[k] += Intensity[new_state];
            old_state = new_state;
            k += 1;
        }
    }
    std::cout << Impact / Scenarios << std::endl;
}
