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
#include "utils/matrix_generation.h"

int main(int num_args, char **arg_strings) {

    int m = 20; //  cols
    int n = 5; // rows

    Eigen::MatrixXd S = RandomAggregationMatrix(n, m);
    std::cout << "Aggregation Matrix: " << S << std::endl;

    float fraction = 0.25;
    Eigen::MatrixXd A0 = RandomSymmetricMatrix(m, fraction);

    Eigen::MatrixXd  A(n, n);
    A = S * A0 * S.transpose();
    std::cout << A << std::endl;

    std::cout << "Row Sum Micro:" << S * A0.colwise().sum().transpose() << std::endl;
    std::cout << "Row Sum Macro:" << A.colwise().sum() << std::endl;
    std::cout << "Col Sum Micro:" << A0.rowwise().sum().transpose() * S.transpose() << std::endl;
    std::cout << "Col Sum Macro:" << A.rowwise().sum().transpose() << std::endl;

    return 0;
}


