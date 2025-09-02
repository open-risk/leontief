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

#pragma once

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>


using namespace std;


/*
 * Bin Su et al. example
 * 3 x 3 system
 * Domestic and export demand
 * Emissions
 */

inline Eigen::MatrixXd BinSuZ() {
    Eigen::MatrixXd z(3,3);
    z << 5, 2, 2, 3, 10, 3, 1, 1, 3;
    return z;
}

inline Eigen::MatrixXd BinSuY() {
    Eigen::MatrixXd y(3,2);
    y << 3, 3, 3, 6, 4, 1;
    return y;
}

inline Eigen::MatrixXd BinSuE() {
    Eigen::MatrixXd e(3,1);
    e << 10, 20, 20;
    return e;
}

/*
 * Random Symmetric Matrix
 */
inline Eigen::MatrixXd RandomSymmetricMatrix(int Size, float Fraction) {
    Eigen::MatrixXd result;
    srand((unsigned int) time(0));
    result.resize(Size, Size);
    result.setRandom();

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (Eigen::Index i = 0; i < Size; i++) {
        for (Eigen::Index j = 0; j < Size; j++) {
            double draw = distribution(generator);
            if (draw < Fraction) {
                result(i, j) = 0.0;
            } else {
                result(i, j) = std::abs(result(i, j));
            }
        }
    }
    return result;
}

