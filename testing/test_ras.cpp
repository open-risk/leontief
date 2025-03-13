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

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <Eigen/Dense>
#include "utils/utils.h"
#include "utils/matrix_generation.h"

TEST_CASE("Test RAS Algorithm", "[algorithms]") {
    int size = 10;
    float fraction = 0.25;
    Eigen::MatrixXd A0 = RandomSymmetricMatrix(size, fraction);
    Eigen::MatrixXd A = A0;

    Eigen::ArrayXd column_sum;
    Eigen::ArrayXd row_sum;
    Eigen::ArrayXd delta;

    int max_index;
    double max_val, scale;
    double norm = 10.0;

    while (norm > 0.001) {
        row_sum = A.colwise().sum();
        column_sum = A.rowwise().sum().transpose();
        delta = column_sum - row_sum;
        delta = delta.abs();
        norm = delta.sum();
        max_val = delta.maxCoeff(&max_index);
        scale = std::sqrt(row_sum[max_index] / column_sum[max_index]);

        for (int j = 0; j < size; j++) {
            if (j != max_index) {
                A(max_index, j) = scale * A(max_index, j);
            }
        }

        for (int i = 0; i < size; i++) {
            if (i != max_index) {
                A(i, max_index) = A(i, max_index) / scale;
            }
        }

        std::cout << norm << std::endl;
    }

    for (int i = 0; i < size; i++) {
        REQUIRE_THAT(delta(i),
                     Catch::Matchers::WithinAbs(0, 0.001));
    }
}
