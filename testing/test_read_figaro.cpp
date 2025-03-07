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


TEST_CASE("Test reading FIGARO data", "[data-io]") {
    std::string filename = "../data/flatfile_eu-ic-supply_24ed_2022.csv";
    const char *cstr = filename.c_str();

    if (std::filesystem::exists(filename)) {
        std::cout << "Ok" << std::endl;

        std::ifstream t(cstr);
        std::stringstream buffer;

        try {
            buffer << t.rdbuf();
            std::cout << "Ok++" << std::endl;
        } catch (...) {
            std::cout << "ERROR: Problem loading FIGARO data" << std::endl;
            abort();
        };
    } else {
        std::cout << "ERROR: FIGARO Input File does not exist" << std::endl;
        abort();
    }
}
