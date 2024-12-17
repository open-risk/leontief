/*
* This file is part of the Leontief distribution (https://github.com/open-risk/leontief).
* Copyright (c) 2024 Open Risk (https://www.openriskmanagement.com)
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
#include <fstream>
#include <Eigen/Dense>


TEST_CASE("Test loading EXIOBASE A matrix", "[data-io]") {
    std::ifstream input_file("../data/IOT_2022_pxp/A_Clean.txt");
    std::string data_row;
    int row_index = 0;
    int col_index;

    Eigen::MatrixXd A(9800, 9800);

    if (input_file.is_open()) {
        while (std::getline(input_file, data_row)) {
            char *ptr = (char *) data_row.c_str();
            auto row_length = data_row.length();
            col_index = 0;
            char *start = ptr;
            for (int i = 0; i < row_length; i++) {
                if (ptr[i] == '\t') {
                    A(row_index, col_index++) = atof(start);
                    start = ptr + i + 1;
                }
            }
            A(row_index, col_index) = atof(start);
            row_index++;
        }
        input_file.close();
    }
}
