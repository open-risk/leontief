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
#include <iostream>
#include <Poco/Environment.h>
#include <filesystem>
#include <fstream>


TEST_CASE("Test reading EXIOBASE data", "[data-io]") {

    std::string filename = "../data/IOT_2022_pxp/A_Clean.txt";
    const char *cstr = filename.c_str();

    if (std::filesystem::exists(filename)) {
        std::cout << "Ok" << std::endl;

        std::ifstream t(cstr);
        std::stringstream buffer;

        try {
            buffer << t.rdbuf();
            std::cout << "Ok++" << std::endl;
        } catch (...) {
            std::cout << "ERROR: Problem loading IO data" << std::endl;
            abort();
        };

    }
    else {
        std::cout << "ERROR: Input File does not exist" << std::endl;
        abort();
    }
}