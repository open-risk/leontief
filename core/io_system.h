/*
* This file is part of the Leontief distribution (https://github.com/open-risk/leontief).
* Copyright (c) 2024 - 2026 Open Risk (https://www.openriskmanagement.com)
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

using namespace Eigen;

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

    IOSystem(const MatrixXd &X, const MatrixXd &Y, const MatrixXd &Z, int mode);

    /**
     * @brief Create a blank system.
     */
    IOSystem();

    /**
     * @brief Calculate the industry output x from the Z and Y matrix
     * industry output (x) = flows (sum_columns(Z)) + final demand (sum_columns(Y))
     */
    void calc_x();

    /**
     * @brief Calculate the industry output x from L and a y vector.
     * x = Ly
     */
    void calc_x_from_L();

    /**
     * @brief Calculate the Z matrix (flows) from A and x
     */
    void calc_Z();

    /**
     * @brief Calculate the A matrix (coefficients) from Z and x
     */
    void calc_A();

    /**
     * @brief Calculate the B matrix (coefficients) from Z and x
     */
    void calc_B();

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

    /**
     * @brief Calculate the Leontief L from A
     * L = inverse matrix of (I - A)
     */
    void calc_L();

    /**
     * @brief Calculate Ghosh inverse G from B
     * G = inverse matrix of (I - B)
     */
    void calc_G();

    /**
     * @brief Calculate extensions/factor inputs coefficients
     */
    void calc_S();

    //
    // Getters
    //

    MatrixXd getZ() {
        return _z;
    }
    MatrixXd getY() {
        return _y;
    }
    MatrixXd getX() {
        return _x;
    }
    MatrixXd getA() {
        return _a;
    }
    MatrixXd getB() {
        return _b;
    }
    MatrixXd getL() {
        return _l;
    }
    MatrixXd getE() {
        return _e;
    }
    MatrixXd getF() {
        return _f;
    }

private:

    // Matrices and vectors for storage and computation
    // Basic system
    MatrixXd _a, _b, _z, _y;
    VectorXd _x;
    // inverses
    MatrixXd _l, _g;
    // extensions
    VectorXd _e, _f, _v, _u;

    // System dimensions (for Symmetric IO should be identical)
    int n{}; // rows
    int m{}; // columns

    // Is the system initialized?
    bool initialized{};

    // n x n - sized identity
    MatrixXd I;

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
inline IOSystem::IOSystem(const MatrixXd &X, const MatrixXd &Y, const MatrixXd &Z, int mode) {

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
