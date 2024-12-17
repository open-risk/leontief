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
#pragma once

#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

// Eigen::MatrixXd RandomSymmetricMatrix(int Size, float Fraction);

// Eigen::MatrixXd RandomAggregationatrix(int Size1, int Size2);

using namespace std;
using namespace Eigen;


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

inline Eigen::MatrixXd RandomAggregationMatrix(int Size1, int Size2) {

    /** Aggregation method / data
     *
     * Standard Linear Aggregation matrix S
     *
     */

    Eigen::MatrixXd result;
    result.resize(Size1, Size2);
    result.setZero();

    std::vector<int> in(Size2), out;
    std::iota(in.begin(), in.end(), 1);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(in.begin(), in.end(), g);

    for (int j = 0; j < Size2; j++) {
        result(j % Size1, in[j] - 1) = 1;
    }

    return result;
}