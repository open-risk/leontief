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
#include <iostream>
#include <filesystem>
#include <fstream>

/*
 * Test that a basic collection of FIGARO files is available and readable. NB: This does not ensure the desired collection is available.
 */

TEST_CASE("Test reading FIGARO data", "[data-io]") {

    std::string filename1 = "../data/matrix_eu-ic-supply_24ed_2022.csv";
    std::string filename2 = "../data/matrix_eu-ic-use_24ed_2022.csv";

    const char *cstr1 = filename1.c_str();
    const char *cstr2 = filename2.c_str();

    bool test = false;

    if (std::filesystem::exists(filename1) && std::filesystem::exists(filename2)) {
        std::cout << "Files Found" << std::endl;

        std::ifstream t1(cstr1);
        std::ifstream t2(cstr2);
        std::stringstream buffer;

        try {
            buffer << t1.rdbuf();
            std::cout << "Ok Buffering File 1" << std::endl;
        } catch (...) {
            std::cout << "ERROR: Problem loading FIGARO data" << std::endl;
            abort();
        };

        try {
            buffer << t1.rdbuf();
            std::cout << "Ok Buffering File 1" << std::endl;
        } catch (...) {
            std::cout << "ERROR: Problem loading FIGARO data" << std::endl;
            abort();
        };

        test = true;

    } else {
        std::cout << "ERROR: FIGARO Input File does not exist" << std::endl;
        abort();
    }
    REQUIRE(test == true);
}
