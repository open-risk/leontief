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
 * Generate a test Use matrix with an symmetric IO part and a desired number of final demand columns and value added rows
 *
 */
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

/**
 * @brief
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
    if (mode == 2) {
        result.resize(m, fd);
        result << 80, 83;
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

/**
 * @brief
 * @param m
 * @param n
 * @param mode
 * @return
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