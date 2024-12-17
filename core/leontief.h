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

#ifndef LEONTIEF_LEONTIEF_H
#define LEONTIEF_LEONTIEF_H


#include <Eigen/Core>
#include <iostream>

namespace leontief {
    //// RAS algorithm

    inline Eigen::MatrixXd RAS(Eigen::MatrixXd &A0) {
        int size = A0.cols();
        Eigen::MatrixXd A = A0;
        Eigen::ArrayXd column_sum;
        Eigen::ArrayXd row_sum;
        Eigen::ArrayXd delta;

        column_sum.resize(size);
        row_sum.resize(size);
        delta.resize(size);

        int max_index;
        double max_val, scale;
        double norm = 10.0;

        while (norm > 0.001) {
            row_sum = A.colwise().sum();
            column_sum = A.rowwise().sum().transpose();
            delta = column_sum - row_sum;
            delta = delta.abs();
            norm = delta.sum();
            max_val = delta.maxCoeff(&max_index);
            scale = std::sqrt(row_sum[max_index] / column_sum[max_index]);

            for (int j = 0; j < size; j++) {
                std::cout << "j: " << j << std::endl;
                if (j != max_index) {
                    A(max_index, j) = scale * A(max_index, j);
                }
            }

            for (int i = 0; i < size; i++) {
                std::cout << "i: " << i << std::endl;
                if (i != max_index) {
                    A(i, max_index) = A(i, max_index) / scale;
                }
            }
        }

        return A;
    }
}

#endif //LEONTIEF_LEONTIEF_H
