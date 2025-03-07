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
# include "utils/csv.h"

using namespace csv;

TEST_CASE("Test loading FIGARO Supply matrix (CSV Format)", "[data-io]") {

    // TOTAL ROWS = 2944 * 2944;

    int MAX = 2944;

    Eigen::MatrixXd S(MAX, MAX);

    CSVReader reader("../data/flatfile_eu-ic-supply_24ed_2022.csv");

    double value = 0;
    int index  = 0;
    int row_index, col_index;
    for (auto& row: reader) {
        value = row["obsValue"].get<double>();
        col_index = index % MAX;
        row_index = (int) index / MAX;
        S(row_index, col_index) = value;
        index++;
        // std::cout << index << " " << row_index  << " " << col_index << " " << value << std::endl;
    }
}
