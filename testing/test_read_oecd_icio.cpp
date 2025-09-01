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
 * Test that a basic collection of OECD-ICIO files is available and readable.
 */

TEST_CASE("Test reading OECD-ICIO data", "[data-io]") {

    std::string filename = "../data/oecd-2017-2022/icio.csv";
    const char *cstr = filename.c_str();
    bool test = false;

    if (std::filesystem::exists(filename) && std::filesystem::exists(filename)) {
        std::cout << "OECD ICIO Files Found" << std::endl;

        std::ifstream t(cstr);
        std::stringstream buffer;

        try {
            buffer << t.rdbuf();
            std::cout << "Ok Buffering File" << std::endl;
        } catch (...) {
            std::cout << "ERROR: Problem loading OECD-ICIO data" << std::endl;
            abort();
        };

        test = true;

    } else {
        std::cout << "ERROR: OECD-ICIO Input File does not exist" << std::endl;
        abort();
    }
    REQUIRE(test == true);
}
