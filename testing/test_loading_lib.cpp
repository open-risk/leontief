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

#include "core/leontief.h"

#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include "core/options.h"
#include "core/io_system.h"
#include "utils/utils.h"


TEST_CASE("Test loading IO/Leontief classes", "[environment]") {

    leontief::Mat_t my_mat;
    IOSystem MyIO = IOSystem();
    int size = 10;
    float fraction = 0.25;
    Eigen::MatrixXd A0 = RandomSymmetricMatrix(size, fraction);
    std::cout << A0 << std::endl;
    Eigen::MatrixXd result = leontief::RAS(A0);

}