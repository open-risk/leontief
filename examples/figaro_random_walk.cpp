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

    // LOAD FIGARO TRANSITION MATRIX
    constexpr int MAX = 2944;
    Eigen::MatrixXd Q(MAX, MAX);
    CSVReader reader1("../data/figaro_qu.csv");
    std::cout << "Column-wise norm check: " << TestColumnNorm(Q) << std::endl;

    // Construct Markov Chain from Transition Matrix
    // input is the upstream transition probabilities Qu
    // Computed and stored separately
    int Sectors = Q.cols();

    Eigen::VectorXd weights(Sectors);
    std::map<int, std::discrete_distribution<> > prob_vector;
    for (int j = 0; j < Sectors; j++) {
        double col_sum = 0;
        for (int ii = 0; ii < Sectors; ii++) {
            col_sum += Q(ii, j);
            weights[ii] = Q(ii, j);
        }
        std::cout << weights << std::endl;
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
