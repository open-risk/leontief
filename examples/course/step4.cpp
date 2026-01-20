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
* Constructing the Leontief Inverse "by hand"
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

    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(2,2);
    Eigen::MatrixXd A2 = io.getA() * io.getA();
    Eigen::MatrixXd A3 = A2 * io.getA();
    Eigen::MatrixXd A4 = A3 * io.getA();
    Eigen::MatrixXd L_4 = I + io.getA() + A2 + A3 + A4;

    std::cout << "4-th order approximation of Leontief Inverse\n" << L_4 << std::endl;
    std::cout << "Actual Solution\n" << io.getL() << std::endl;

}
