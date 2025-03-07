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
#include <Poco/Environment.h>
#include <Poco/Path.h>
#include <iostream>

TEST_CASE("Runtime OS/Poco C++ Environment is ready", "[environment]") {
    // Use SANITY_CHECK = 1 as a compilation parameter to check the basic sanity of the Leontief environment.
    // This test will simply fetch and print some relevant environment variables

    std::cout << "------------------------------------" << std::endl;
    std::cout << "OS Name: " << Poco::Environment::osName() << std::endl
            << "OS Version: " << Poco::Environment::osVersion() << std::endl
            << "OS Arch: " << Poco::Environment::osArchitecture() << std::endl
            << "Node Name: " << Poco::Environment::nodeName() << std::endl
            << "Node ID: " << Poco::Environment::nodeId() << std::endl
            << "Current Dir: " << Poco::Path::current() << std::endl;
}
