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

    int Sectors;
    Eigen::VectorXd x;
    int IO = 10;
    int FD = 1;
    int VA = 1;

    Eigen::MatrixXd S = TestSupplyMatrix(IO);
    Eigen::MatrixXd U = TestUseMatrix(IO, FD, VA);
    SUTSystem testSUT;
    testSUT.CreateTransactionsMatrix(S, U);
    testSUT.CreateUpstreamProbabilities(IO, IO);

    // IO Storage (Calculated Values)
    Eigen::MatrixXd W; // Weight Matrix
    Eigen::VectorXd Intensity; // Upstream total intensity
    Eigen::VectorXd Impact; // Upstream absolute impact

    // input transition probabilities Q
    Eigen::VectorXd weights(Sectors);

    std::map<int, std::discrete_distribution<> > prob_vector;
    for (int i = 0; i < Sectors; i++) {
        double row_sum = 0;
        for (int j = 0; j < Sectors; j++) {
            row_sum += testSUT.getQu()(i, j);
            weights[j] = testSUT.getQu()(i, j);
        }
        std::discrete_distribution<int> d(weights.begin(), weights.end());
        prob_vector[i] = d;
        std::cout << i << " " << row_sum << std::endl;
    }

    int Scenarios = 10;

    // Here the weights are from Q columns and the integers are from the sector index

    std::random_device rd;
    std::mt19937 gen(rd());

    // For each unique random walk path

    double impact = 0, cumulative_impact = 0;

    std::vector<double> F(Scenarios);

    for (int fs = 0; fs < Scenarios; fs++) {

        int old_state = static_cast<int>(x[0]);
        int k = 0; // Step Count
        // While not absorbed
        while (old_state != 3 && k < 3) {
            // Compute Next Node
            int new_state = prob_vector[old_state](gen);
            // Compute Impact Intensity
            std::cout << "Step " << k << " : from " << old_state << " to " << new_state << " with impact " << Intensity[new_state] << std::endl;
            // Store desired k-round result
            if (k == 1) {
                F[fs] = Intensity[new_state];
            }

            old_state = new_state;
            k += 1;
        }
    }
}
