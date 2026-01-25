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
  This data is from the chapter 2 of
    Input-output analysis: foundations and extensions -- Miller, Ronald E
    and Blair, Peter D -- 2009 (ISBN: 9780521517133)
  Table 2.3 of the Book
*/

int main(int num_args, char **arg_strings) {
    int mode = 0;

    Eigen::MatrixXd Z(2,2);
    Z << 150, 500, 200, 100;
    Eigen::MatrixXd Y(2, 1);
    Y << 350, 1700;
    Eigen::MatrixXd E(2, 1);
    E << 650, 1400;

    IOSystem io(Z, Y, E, mode);

    // Calculate everything that can be calculated (starting with inputs Z, Y)
    io.calc_from_z();

}
