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
#include <algorithm>
#include <iostream>
#include "utils/io_matrix_generation.h"
#include "utils/agg_matrix_generation.h"
#include "core/agg_system.h"

TEST_CASE("Test Aggregation Algorithm", "[algorithms]") {

    int m = 20;
    int n = 5;

    float fraction = 0.25;
    Eigen::MatrixXd A0 = RandomSymmetricMatrix(m, fraction);
    Eigen::MatrixXd S = BlockAggregation(m, n);

    Eigen::MatrixXd A(n, n);
    A = S * A0 * S.transpose();

    Eigen::MatrixXd B(n, n);
    AggSystem MyAgg (S);
    B = MyAgg.Aggregate(A0);

    std::cout << "Row Sum Micro:" << S * A0.colwise().sum().transpose() << std::endl;
    std::cout << "Col Sum Micro:" << A0.rowwise().sum().transpose() * S.transpose() << std::endl;

    std::cout << "Row Sum Macro A:" << A.colwise().sum() << std::endl;
    std::cout << "Col Sum Macro A:" << A.rowwise().sum().transpose() << std::endl;

    std::cout << "Row Sum Macro B:" << B.colwise().sum() << std::endl;
    std::cout << "Col Sum Macro B:" << B.rowwise().sum().transpose() << std::endl;
}
