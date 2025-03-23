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

// ATTN the two file formats do not agree on ~6986 elements (Factors 2, 7, 499)
// Tested 2022, 2021
// TOTAL NUMERICAL ROWS = 2944 * 2944;
// TODO test that labels agree (python script)


TEST_CASE("Test parsing FIGARO Supply matrix", "[data-io]") {

    constexpr int MAX = 2944;

    Eigen::MatrixXd S1(MAX, MAX);
    Eigen::MatrixXd S2(MAX, MAX);

    CSVReader reader1("../data/flatfile_eu-ic-supply_24ed_2021.csv");
    CSVReader reader2("../data/matrix_eu-ic-supply_24ed_2021.csv");

    double value = 0;
    int index = 0;
    // We only read the numerical values skipping labels
    for (auto &row: reader1) {
        value = row["obsValue"].get<double>();
        const int col_index = index % MAX;
        const int row_index = (int) index / MAX;
        S1(row_index, col_index) = value;
        index++;
    }
    std::string label;
    int i = 0;
    for (auto &row: reader2) {
        for (int j = 0; j < MAX + 1; j++) {
            if (j > 0) {
                value = row[j].get<double>();
                S2(i, j - 1) = value;
                // std::cout << i << " " << j << " " << value << std::endl;
            } else {
                label = row[j].get_sv();
                // std::cout << i << " " << j << " " << label << std::endl;
            }
        }
        i++;
    }

    int error_count = 0;
    for (int j = 0; j < MAX; j++) {
        for (int i = 0; i < MAX; i++) {
            if (S1(i, j) != S2(i, j)) {
                std::cout << i << " " << j << " " << S1(i, j) << " " << S2(i, j) << std::endl;
                error_count++;
            }
        }
    }

    REQUIRE(error_count == 0);
}
