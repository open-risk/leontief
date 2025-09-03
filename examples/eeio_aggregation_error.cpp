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
#include <fstream>
#include "utils/io_matrix_generation.h"
#include "core/io_system.h"

/*
 * Aggregation errors in EEIO calculations
 * From Input–output analysis of CO2 emissions embodied in trade: The effects of sector aggregation
 * Bin Su, H.C. Huang, B.W. Ang, P. Zhou
 * Energy Economics 32 (2010) 166–175
 */
int main(int num_args, char **arg_strings) {

    Eigen::MatrixXd Z = BinSuZ();
    Eigen::MatrixXd Y = BinSuY();
    Eigen::MatrixXd E = BinSuE();

    IOSystem io(Z, Y, E,3);
    std::cout << "Z: " << io.getZ() << std::endl;
    std::cout << "Y: " << io.getY() << std::endl;
    std::cout << "E: " << io.getE() << std::endl;

    io.calc_from_z();
    std::cout << "X: " << io.getX() << std::endl;
    std::cout << "A: " << io.getA() << std::endl;
    std::cout << "L: " << io.getL() << std::endl;
    std::cout << "F: " << io.getF() << std::endl;


    return 0;
}


