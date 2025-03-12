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
#include "core/options.h"

// Eigen::MatrixXd RandomSymmetricMatrix(int Size, float Fraction);

// Eigen::MatrixXd RandomAggregationatrix(int Size1, int Size2);

using namespace std;
using namespace Eigen;

bool TestColumnNorm(Eigen::MatrixXd &S) {
    bool test = true;
    auto colsum = S.colwise().sum();
    for (int i = 0; i < S.cols(); i++)
        if (abs(colsum(i) - 1.0) > LEONTIEF_TOLERANCE) test = false;
    return test;
}
