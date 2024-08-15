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

#include "utils.h"

using namespace std;
using namespace Eigen;


Eigen::MatrixXd RandomSymmetricMatrix(int Size, float Fraction) {

    Eigen::MatrixXd result;
    srand((unsigned int) time(0));
    result.resize(Size, Size);
    result.setRandom();

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);

    for (Eigen::Index i = 0; i < Size; i++) {
        for (Eigen::Index j = 0; j < Size; j++) {
            double draw = distribution(generator);
            if (draw < Fraction) {
                result(i, j) = 0.0;
            }
            else {
                result(i, j) = std::abs(result(i, j));
            }
        }
    }
    return result;
}

Eigen::MatrixXd RandomAggregationMatrix(int Size1, int Size2) {

    Eigen::MatrixXd result;
    srand((unsigned int) time(0));
    result.resize(Size1, Size1);

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0,1.0);
//    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);

    for (Eigen::Index i = 0; i < Size1; i++) {
        for (Eigen::Index j = 0; j < Size2; j++) {
            double draw = distribution(generator);
            if (draw < 0.5) {
                result(i, j) = 0;
            }
            else {
                result(i, j) = 1;
            }
        }
    }
    return result;
}