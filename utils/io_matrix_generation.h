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
    Eigen::MatrixXd z(3, 3);
    z << 5, 2, 2, 3, 10, 3, 1, 1, 3;
    return z;
}

inline Eigen::MatrixXd BinSuY() {
    Eigen::MatrixXd y(3, 2);
    y << 3, 3, 3, 6, 4, 1;
    return y;
}

inline Eigen::MatrixXd BinSuE() {
    Eigen::MatrixXd e(3, 1);
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

/**
 * Collection of simple IO systems for testing
 * Selected by the mode variable
 * mode = 0, trivial IO system
 * mode = 1, 2x2 system
 * mode = 2, 7x7 system
 */

/**
 * @brief Generate value added matrices for testing
 * @param n
 * @param va
 * @param mode
 * @return
 */
inline Eigen::MatrixXd TestVAMatrix(const int n, const int va, const int mode) {
    Eigen::MatrixXd result;
    if (mode == 2) {
        result.resize(va, n);
        result << 60, 95;
    }
    return result;
}

/**
 * @brief
 * @param m
 * @param fd
 * @param mode
 * @return
 */
inline Eigen::MatrixXd TestFDMatrix(const int m, const int fd, const int mode) {
    Eigen::MatrixXd result;

    // Miller Blair page 29
    if (mode == 2) {
        result.resize(m, fd);
        result<< 1.2, 0, 0, 6.8, 0, 0, 0;
    }
    return result;
}

/**
 * @brief
 * @param m
 * @param n
 * @param mode
 * @return
 */
inline Eigen::MatrixXd TestZMatrix(const int m, const int n, const int mode) {
    Eigen::MatrixXd result;
    int IO = m;
    int FD = 1;
    int VA = 1;

    if (mode == 0) {
        // trivial
    } else if (mode == 1) {
        // 2x2
    } else if (mode == 2) {
        // 7x7
    }
    return result;
}

/**
 * @brief
 * @param m
 * @param n
 * @param mode
 * @return
 */
inline Eigen::MatrixXd TestAMatrix(const int m, const int n, const int mode) {
    Eigen::MatrixXd result;
    int IO = m;
    int FD = 1;
    int VA = 1;

    if (mode == 2) {
        result.resize(7, 7);
        // 7x7
        // Table 2.7 The 2003 US Domestic Direct Requirements Matrix, A
        // Miller Blair page 29
        result << .2008, .0000, .0011, .0338, .0001, .0018, .0009, .0010, .0658, .0035, .0219, .0151, .0001, .0026,.0034, .0002, .0012, .0021, .0035, .0071, .0214, .1247, .0684, .1801, .2319, .0339, .0414, .0726, .0855, .0529, .0914, .0952, .0645, .0315, .0528, .0897, .1668, .1332, .1255, .1647, .2712, .1873, .0093, .0129, .0095, .0197, .0190, .0184, .0228;
    }
    return result;
}