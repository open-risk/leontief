/*
* This file is part of the Leontief distribution (https://github.com/open-risk/leontief).
* Copyright (c) 2024 - 2026 Open Risk (https://www.openriskmanagement.com)
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


/*
* Example of a 2x2 IO System Calculation
*/

int main(int num_args, char **arg_strings) {
    int mode = 0;

    Eigen::MatrixXd Z(2,2);
    Z << 200, 100, 80, 50;
    Eigen::MatrixXd Y(2, 2);
    Y << 300, 100, 200, 150;

    Eigen::VectorXd E;

    IOSystem io(Z, Y, E, mode);

    // Calculate everything that can be calculated (starting with inputs Z, Y)
    io.calc_from_z();

    // Report
    std::cout << "Z Table (Industry Transactions):\n" << io.getZ() << std::endl;
    std::cout << "Y Table (Demand): \n" << io.getY() << std::endl;
    std::cout << "x Vector (Total Output): \n" << io.getX() << std::endl;
    std::cout << "A Table (Normalized Transactions): \n" << io.getA() << std::endl;
    std::cout << "L Table (Leontief Inverse): \n" << io.getL() << std::endl;
}
