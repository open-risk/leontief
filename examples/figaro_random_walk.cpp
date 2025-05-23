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
#include "utils/scan_matrix.h"
#include "utils/matrix_generation.h"
#include "utils/compactify_use_matrix.h"

using namespace csv;

int main(int num_args, char **arg_strings) {

    // LOAD FIGARO TRANSITION MATRIX
    constexpr int MAX = 5890;
    Eigen::MatrixXd Q(MAX, MAX);
    CSVReader reader1("../data/figaro_qu.csv");
    double value = 0;
    int i = 0;
    for (auto &row: reader1) {
        for (int j = 0; j < MAX; j++) {
            value = Q(i, j) = row[j].get<double>();
        }
        i++;
    }

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
        // std::cout << weights << std::endl;
        std::discrete_distribution<int> d(weights.begin(), weights.end());
        prob_vector[j] = d;
    }

    std::cout << "Constructed Markov Chain" << std::endl;

    int Scenarios = 1;

    // Here the weights are from Q columns and the integers are from the sector index

    // std::random_device rd;
    //std::mt19937 gen(rd());
    // std::default_random_engine eng{static_cast<long unsigned int>(time(0))};

    std::random_device rd;
    std::size_t seed;
    if (rd.entropy())
        seed = rd();
    else
        seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);

    int Steps = 10;

    Eigen::VectorXd Intensity(Sectors); // Impact intensity
    Intensity.setOnes();

    Eigen::VectorXd Impact(Steps);
    Impact.setZero();

    for (int fs = 0; fs < Scenarios; fs++) {
        int old_state = 100;
        int k = 0; // Step Count
        // While not absorbed
        while (old_state != 2944 && k < Steps) {
            // Compute Next Node
            int new_state = prob_vector[old_state](gen);
            // Compute Impact Intensity
            std::cout << "Step " << k << " : from " << old_state << " to " << new_state << " with impact " << Intensity[new_state] << std::endl;
            Impact[k] += Intensity[new_state];
            old_state = new_state;
            k += 1;
        }
    }
    // std::cout << Impact / Scenarios << std::endl;
}
