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
#include <random>
#include <iostream>
#include "core/sut_system.h"
#include "utils/matrix_generation.h"
#include "utils/scan_matrix.h"

TEST_CASE("Test SUT system creation", "[sut]") {

    int m = 2; // product count
    int n = 2; // sector count
    int fd = 1; // final demand count
    int va = 1; // value added count
    int mode = 2; // select test

    // Insert test data
    Eigen::MatrixXd S = TestSupplyMatrix(m, n, mode);
    Eigen::MatrixXd U = TestUseMatrix(m, n, mode);
    Eigen::MatrixXd VA = TestVAMatrix(n, va, mode);
    Eigen::MatrixXd FD = TestFDMatrix(m, va, mode);

    // Initialize and compute full SUT system
    SUTSystem testSUT(S, U, VA, FD);
    testSUT.CreateTotalInput();
    std::cout << testSUT.getTI() << std::endl;
    testSUT.CreateTotalOutput();
    std::cout << testSUT.getTO() << std::endl;
    testSUT.CreateTransactionsMatrix(S, U);
    testSUT.CreateUpstreamProbabilities(m, m);
    testSUT.CreateDownstreamProbabilities();

    // Test
    REQUIRE(TestBalance(testSUT.getTI(), testSUT.getTO()) == 1);
    REQUIRE(TestProbabilities(testSUT.getQu()) == 1);
    REQUIRE(TestColumnNorm(testSUT.getQu()) == 1);

}