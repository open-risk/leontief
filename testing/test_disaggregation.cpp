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
#include "utils/io_matrix_generation.h"

TEST_CASE("Test Disaggregation Algorithm", "[algorithms]") {
    constexpr int size = 5;
    constexpr float fraction = 0.25;
    const Eigen::MatrixXd A0 = RandomSymmetricMatrix(size, fraction);

    Eigen::MatrixXd A(10, 10);
    A.setZero();

    /** Disaggregation method / data
     *
     * column index (J) to expand into N new columns (corresponding rows)
     *
     */

    int J = 4;
    int inserts = 5;

    A.block(0, 0, size, size) = A0;
    std::cout << A << std::endl;
}
