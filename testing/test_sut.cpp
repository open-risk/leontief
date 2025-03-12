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
#include <random>
#include <Eigen/Dense>
#include <iostream>
#include "core/sut_system.h"
#include "utils/matrix_generation.h"
#include "utils/check_norms.h"

TEST_CASE("Test SUT system creation", "[sut]") {

    int IO = 10;
    int FD = 1;
    int VA = 1;

    Eigen::MatrixXd S = TestSupplyMatrix(IO);
    Eigen::MatrixXd U = TestUseMatrix(IO, FD, VA);
    SUTSystem testSUT;
    testSUT.CreateTransactionsMatrix(S, U);
    testSUT.CreateUpstreamProbabilities(IO, IO);
    testSUT.CreateDownstreamProbabilities();

    REQUIRE(TestColumnNorm(testSUT.getQu()) == 1);

}