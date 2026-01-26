/*
* This file is part of the Leontief distribution (https://github.com/open-risk/leontief).
* Copyright (c) 2024 - 2026 Open Risk (https://www.openriskmanagement.com)
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
#include "core/io_system.h"
#include "utils/io_matrix_generation.h"
#include "utils/scan_matrix.h"

TEST_CASE("Test IO system mathematics", "[io]") {

    // TODO Examples
    int mode = 3; // select test

    // MODE 1: Open Risk WP 16, Appendix 1 System (Based on Kitzes 2013)
    // int m = 2; // product count
    // int n = 2; // sector count
    // int fd = 1; // final demand count
    // int va = 1; // value added count
    // int mode = 1; // select test

    // MODE 2: Miller-Blair Table 5.3 Page 187
    // int m = 2; // product count
    // int n = 2; // sector count
    // int fd = 1; // final demand count
    // int va = 1; // value added count
    // int mode = 2; // select test

    // Insert test data
    // MODE 0: Trivial System
    //    int n = 1; // sector count
    //    int fd = 1; // final demand count

    // MODE 3: Small MRIO from the Pymrio distribution
    int m = 6; // total product count (3 sectors x 2 regions)
    int n = 6; // total sector count (3 sectors x 2 regions)
    int fd = 2; // final demand matrix (2 regions)

    MatrixXd Z = TestZMatrix(n, n, mode);
    MatrixXd FD = TestFDMatrix(n, fd, mode);
    // Eigen::MatrixXd dummy;

    // Initialize and compute full IO system
    // IOSystem testIO(Z, FD, dummy, 0);

    // Test TODO
    REQUIRE(Z.sum() == 166);
    REQUIRE(FD.rows()*FD.cols() == 12);

}