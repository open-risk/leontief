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

/*
 * Various utilities for checking IO / SUT table properties
 */

// Eigen::MatrixXd RandomSymmetricMatrix(int Size, float Fraction);
// Eigen::MatrixXd RandomAggregationatrix(int Size1, int Size2);

using namespace std;
using namespace Eigen;

inline bool TestColumnNorm(Eigen::MatrixXd &S) {
    bool test = true;
    auto colsum = S.colwise().sum();
    for (int j = 0; j < S.cols(); j++) {
        if (abs(colsum(j) - 1.0) > LEONTIEF_TOLERANCE) {
            // std::cout << "Column: " << j << " " << colsum(j) << std::endl;
            test = false;
        }
    }
    return test;
}

inline bool TestColumnSum(Eigen::MatrixXd &S) {
    bool test = true;
    auto colsum = S.colwise().sum();
    for (int j = 0; j < S.cols(); j++) {
        if (abs(colsum(j)) < LEONTIEF_TOLERANCE) {
            std::cout << "Column: " << j << " " << colsum(j) << std::endl;
            test = false;
        }
    }
    return test;
}

inline bool TestProbabilities(Eigen::MatrixXd &S) {
    bool test = true;
    for (int i = 0; i < S.rows(); i++) {
        for (int j = 0; j < S.cols(); j++) {
            if (S(i, j) > 1.0) {
                test = false;
                std::cout << i << " " << j << " " << S(i, j) << std::endl;
            }
        }
    }
    return test;
}

inline bool TestPositivity(Eigen::MatrixXd &S) {
    bool test = true;
    for (int i = 0; i < S.rows(); i++) {
        for (int j = 0; j < S.cols(); j++) {
            if (S(i, j) < 0.0) {
                test = false;
                std::cout << i << " " << j << " " << S(i, j) << std::endl;
            }
        }
    }
    return test;
}

inline bool TestBalance(Eigen::MatrixXd &TI, Eigen::MatrixXd &TO) {
    bool test = true;
    for (int i = 0; i < TI.rows(); i++) {
        if (abs(TI(i) - TO(i)) > LEONTIEF_TOLERANCE) test = false;
    }
    return test;
}
