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

#include <iostream>
#include <Eigen/Core>

#include "core/io_system.h"


int main(int num_args, char **arg_strings) {

    // Initialize IO System

    // Eigen::Matrix<double, 1,1> Z {{1}};
    // Eigen::Matrix<double, 1,1> Y {{2}};

    Eigen::MatrixXd Z(2,2);
    Z << 200, 100, 80, 50;
    Eigen::MatrixXd Y(2, 2);
    Y << 300, 100, 200, 150;

    IOSystem io(Z, Y);

    // Calculate everything that can be calculated
    io.calc_all_io();

    std::cout << io.getZ() << std::endl;
    std::cout << io.getY() << std::endl;
    std::cout << io.getX() << std::endl;
    std::cout << io.getA() << std::endl;
    std::cout << io.getL() << std::endl;

}
