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
#include <filesystem>
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include "utils/csv.h"

using namespace csv;

TEST_CASE("Test parse OECD_ICIO matrix", "[data-io]") {

    int n = 4050; // total sectors
    int fd = 486; // final demand types
    int va = 2; // value added types


    Eigen::MatrixXd Z(n, n);      // n x n transactions matrix
    Eigen::MatrixXd FD(n, fd);    // n x fd final demand matrix
    Eigen::MatrixXd VA(va, n + fd);    // va x n value added matrix

    Eigen::VectorXd Oc(n);   // output column vector
    Eigen::RowVectorXd Or(n);         // output row vector

    constexpr int ROWS = 4053; // csv row dimension (not used by csvreader)
    constexpr int COLS = 4537; // csv col dimension

    CSVReader reader("../data/oecd-2017-2022/icio.csv");

    double value;
    int i = 0;
    for (auto &row: reader) {
        for (int j = 0; j < COLS; j++) {
            value = row[j].get<double>();
            if (i < n && j < n) {
                Z(i, j) = value;
            }
            else if (i < n && j < COLS - 1 && j >= n) {
                FD(i, j - n) = value;
            }
            else if (i < n && j == COLS - 1) {
                Oc(i) = value;
            }
            else if (i < ROWS - 1 && j < COLS - 1) {
                VA(i - n, j) = value;
            }
            else if (i == ROWS - 1 && j < n) {
                Or(j) = value;
            }
        }
        i++;
    }
    UNSCOPED_INFO("Output Row Sum: " << Z);
    UNSCOPED_INFO("Output Row Sum: " << Or.sum());
    UNSCOPED_INFO("Output Col Sum: " << Oc.sum());
    REQUIRE(41 == 42);
}
