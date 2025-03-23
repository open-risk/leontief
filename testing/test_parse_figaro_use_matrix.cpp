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

TEST_CASE("Test parse FIGARO Use matrix", "[data-io]") {

    int n{}; // sectors
    int m{}; // products
    int va{}; // value added types
    int fd{}; // final demand types

    Eigen::MatrixXd _U;  // m x n use matrix
    Eigen::MatrixXd _VA; // va x n value added matrix (part of use table)
    Eigen::MatrixXd _FD; // m x fd final demand matrix (part of use table)

    constexpr int MAX = 2944; // Matrix dimension
    Eigen::MatrixXd S(MAX, MAX);

    CSVReader reader("../data/matrix_eu-ic-supply_24ed_2022.csv");

    double value = 0;
    std::string label;
    int i = 0;
    for (auto &row: reader) {
        for (int j = 0; j < MAX+1; j++) {
            if (i > 0 && j > 0) {
                value = row[j].get<double>();
                S(i-1, j-1) = value;
            } else {
                label = row[j].get_sv();
            }
        }
        i++;
    }
}
