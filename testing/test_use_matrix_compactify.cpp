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
#include <Eigen/Dense>
#include "utils/compactify_use_matrix.h"
#include "utils/matrix_generation.h"

TEST_CASE("Test the compactification of Use matrix data", "[algorithms]") {

    int IO = 10;
    int FD = 3;
    int VA = 4;

    Eigen::MatrixXd U = TestUseMatrix(IO, FD, VA);
    std::cout << U << std::endl;
    std::cout << "----------------" << std::endl;

    Eigen::MatrixXd U2 = CompactifyUseMatrix(U, FD, VA);
    std::cout << U2 << std::endl;

    int xsize = U2.cols();
    int ysize = U2.rows();

    REQUIRE(xsize == IO + 1);
    REQUIRE(ysize == IO + 1);
    REQUIRE(U2(IO, 0) == 8);
    REQUIRE(U2(0, IO) == 9);
    REQUIRE(U2(IO, IO) == 0);

}
