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

/*
 * # EXAMPLE 5: Generic IO Calculations
 */

int main(int num_args, char **arg_strings) {

    // TODO break into multiple examples

    // Initialize Trivial IO System
    // mode=0
    // Eigen::Matrix<double, 1,1> Z {{1}};
    // Eigen::Matrix<double, 1,1> Y {{2}};

    // Initialize 2x2 System
    // mode=0
    // Eigen::MatrixXd Z(2,2);
    // Z << 200, 100, 80, 50;
    // Eigen::MatrixXd Y(2, 2);
    // Y << 300, 100, 200, 150;
    // IOSystem io(Z, Y);

    // Calculate everything that can be calculated (starting with Z,Y)
    // io.calc_from_z();

    // Initialize 7x7 System
    // mode=1

    // TODO move to matrix generation, add reference
    Eigen::MatrixXd A(7,7);
    A << .2008, .0000, .0011, .0338, .0001, .0018, .0009, .0010, .0658, .0035, .0219, .0151, .0001, .0026,.0034, .0002, .0012, .0021, .0035, .0071, .0214, .1247, .0684, .1801, .2319, .0339, .0414, .0726, .0855, .0529, .0914, .0952, .0645, .0315, .0528, .0897, .1668, .1332, .1255, .1647, .2712, .1873, .0093, .0129, .0095, .0197, .0190, .0184, .022;

    Eigen::VectorXd Y(7);
    Y << 1.2, 0, 0, 6.8, 0, 0, 0;

    Eigen::VectorXd E(7);
    E.setZero();

    IOSystem io(A, Y, E, 1);

    // Calculate everything that can be calculated (starting with Z,Y)
    io.calc_from_a();

    std::cout << io.getZ() << std::endl;
    std::cout << io.getY() << std::endl;
    std::cout << io.getX() << std::endl;
    std::cout << io.getA() << std::endl;
    std::cout << io.getL() << std::endl;

}
