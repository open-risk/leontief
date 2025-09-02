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

#ifndef LEONTIEF_IO_SYSTEM_H
#define LEONTIEF_IO_SYSTEM_H

#include <Eigen/Core>
#include <iostream>

#pragma once

/**
 * @brief Class holding an entire IO system
 *
 * @details Holds both input and processed data
 *
 * @note For SUT systems see corresponding class
 *
 * @warning WIP
 *
 * @tparam T Description of template parameter (if applicable)
 *
 * @see sut_system for SUT class
 *
 * @date 2025-09-02
 *
 */
class IOSystem {

public:

    /**
     * @brief
     * @param X
     * @param Y
     * @param Z
     * @param mode
     */
    IOSystem(const Eigen::MatrixXd &X, const Eigen::MatrixXd &Y, const Eigen::MatrixXd &Z, int mode);

    /**
     * @brief Create a blank system.
     */
    IOSystem();

    /**
     * @brief calculate standard flow (inputs Z, Y)
     */
    void calc_from_z();

    /**
     * @brief
     */
    void calc_from_z2();

    /**
      * calculate shortcut flow (inputs A, Y)
    */
    void calc_from_a();

    Eigen::MatrixXd getZ() {
        return _z;
    }
    Eigen::MatrixXd getY() {
        return _y;
    }
    Eigen::MatrixXd getX() {
        return _x;
    }
    Eigen::MatrixXd getA() {
        return _a;
    }
    Eigen::MatrixXd getL() {
        return _l;
    }
    Eigen::MatrixXd getE() {
        return _e;
    }
    Eigen::MatrixXd getF() {
        return _f;
    }

private:

    // Matrices and vectors for computation
    Eigen::MatrixXd _a, _z, _y, _l;
    Eigen::VectorXd _x, _e, _f, _v, _u;

    // System dimensions (for Symmetric IO should be identical)
    int n{}; // rows
    int m{}; // columns

    // Is the system initialized?
    bool initialized{};

    // n x n - sized identity
    Eigen::MatrixXd I;

};

/**
 * @brief
 */
inline IOSystem::IOSystem() = default;

/**
 *
 * @brief Create an Input-Output system with the specified matrices.
 *
 * @details Component Matrices:
 * Z Flow matrix, X Industry output vector, A Coefficients matrix, L Leontief inverse matrix
 * y Final demand vector / matrix
 *
 * @param X
 * @param Y
 * @param Z
 * @param mode
 */
inline IOSystem::IOSystem(const Eigen::MatrixXd &X, const Eigen::MatrixXd &Y, const Eigen::MatrixXd &Z, int mode) {

    if (mode == 0) {  // Initialize with Z and Y matrix
        _z = X;
        _y = Y;

        _x.resize(_z.rows());
        _e.resizeLike(_x);
        _f.resizeLike(_e);
        _a.resizeLike(_z);
        _l.resizeLike(_z);
    }
    else if (mode == 1) { // Initialize with A and Y matrix
        _a = X;
        _y = Y;

        _e.resizeLike(_y); // TODO vector only
        _f.resizeLike(_e);
        _l.resizeLike(_a);
    }
    else if (mode == 2) { // Initialize with Z and X matrix
        _z = X;
        _x = Y;

        _e.resizeLike(_x); // TODO vector only
        _f.resizeLike(_e);
        _l.resizeLike(_a);
    }
    else if (mode == 3) { // Initialize with Z, Y and E matrix
        _z = X;
        _y = Y;
        _e = Z;

        _x.resize(_z.rows());
        _f.resizeLike(_e);
        _a.resizeLike(_z);
        _l.resizeLike(_z);
    }
    initialized = true;
}

#endif //LEONTIEF_IO_SYSTEM_H
