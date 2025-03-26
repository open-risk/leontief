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

inline Eigen::VectorXd TestIntensity(const int m, const int n, const int mode) {
    Eigen::VectorXd result;
    result.setZero();
    if (mode == 0) {
        for (int j=0; j<m; j++) {
            result(j) = 1.0;
        }
    } else if (mode == 1) {
        result.resize(6);
        result << 0.5, 0.33, 0, 0, 0, 0;
    }
    return result;
}

inline Eigen::MatrixXd TestVAMatrix(const int n, const int va, const int mode) {
    Eigen::MatrixXd result;
    if (mode == 2) {
        result.resize(va, n);
        result << 60, 95;
    }
    return result;
}

inline Eigen::MatrixXd TestFDMatrix(const int m, const int fd, const int mode) {
    Eigen::MatrixXd result;
    if (mode == 2) {
        result.resize(m, fd);
        result << 80, 83;
    }
    return result;
}

inline Eigen::MatrixXd TestSupplyMatrix(const int m, const int n, const int mode) {
    Eigen::MatrixXd result;
    if (mode == 0) {
        // result.resize(m, m);
        // result.setRandom();
        // result = result.cwiseAbs();
        result = Eigen::MatrixXd::Identity(m, m);
    } else if (mode == 1) {
        result.resize(2, 2);
        result << 16, 0, 0, 12;
    } else if (mode == 2) {
        result.resize(2, 2);
        result << 90, 10, 0, 100;
    }
    return result;
}

/*
 * Generate a test Use matrix with an symmetric IO part and a desired number of final demand columns and value added rows
 *
 */
inline Eigen::MatrixXd TestUseMatrix(const int m, const int n, const int mode) {
    Eigen::MatrixXd result;
    int IO = m;
    int FD = 1;
    int VA = 1;

    if (mode == 0) {
        result.resize(m+1, m+1);
        result.setRandom();
        result = result.cwiseAbs();
    } else if (mode == 3) {
        const int SizeX = IO + FD;
        const int SizeY = IO + VA;

        result.resize(SizeY, SizeX);

        for (int i = 0; i < SizeY; i++) {
            for (int j = 0; j < SizeX; j++) {
                if (i >= IO && j < IO) {
                    result(i, j) = 2;
                } else if (i < IO && j >= IO) {
                    result(i, j) = 3;
                } else if (i >= IO && j >= IO) {
                    result(i, j) = 0;
                } else {
                    result(i, j) = 1;
                }
            }
        }
    } else if (mode == 1) {
        result.resize(3, 3);
        result << 8, 5, 3, 4, 2, 6, 4, 5, 0;
    } else if (mode == 2) {
        result.resize(3, 3);
        result << 12, 8, 80, 10, 7, 83, 68, 95, 0;
    }

    return result;
}


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
