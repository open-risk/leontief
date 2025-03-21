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

#ifndef LEONTIEF_IO_SYSTEM_H
#define LEONTIEF_IO_SYSTEM_H

#include <Eigen/Core>

#pragma once

class IOSystem {

public:

    /**
    * Create an Input-Output system with the specified matrices.
    *   Z - Flow matrix
    *   x - Industry output vector
    *   A - Coefficients matrix
    *   L - Leontief matrix
    *   y - Final demand vector / matrix
    */
    IOSystem(
            const Eigen::MatrixXd &Z,
            const Eigen::MatrixXd &Y,
            int mode
            // const Eigen::MatrixXd &A,
            // const Eigen::MatrixXd &x,
            // const Eigen::MatrixXd &L
    );

    /**
    * Create a blank system.
    */
    IOSystem();

    /**
    * Initialize the system with initial states as zero.
    */
    void init();

    /**
    * Initialize with data
    */
    void init(double t0, const Eigen::VectorXd &x0);

    /**
    * Update with data
    */
    void update(const Eigen::VectorXd &y);

    /**
    * Update
    */
    void update(const Eigen::VectorXd &y, double dt, Eigen::MatrixXd A);

    /**
     * calculate standard flow (inputs Z, Y)
     */
    void calc_from_z();
    /**
      * calculate shortcut flow (inputs A, Y)
    */
    void calc_from_a();

    Eigen::MatrixXd getZ() {
        return _Z;
    }
    Eigen::MatrixXd getY() {
        return _Y;
    }
    Eigen::MatrixXd getX() {
        return _x;
    }
    Eigen::MatrixXd getA() {
        return _A;
    }
    Eigen::MatrixXd getL() {
        return _L;
    }


private:

    // Matrices and vectors for computation
    Eigen::MatrixXd _A, _Z, _Y, _L;
    Eigen::VectorXd _x, _E, _f, _v, _U;

    // System dimensions (for Symmetric IO should be identical)
    int n{}; // rows
    int m{}; // columns

    // Is the system initialized?
    bool initialized{};

    // n x n -sized identity
    Eigen::MatrixXd I;

};

inline IOSystem::IOSystem() = default;


inline IOSystem::IOSystem(const Eigen::MatrixXd &Z, const Eigen::MatrixXd &Y, int mode) {

    if (mode == 0) {  // Initialize with Z and Y matrix
        _Z = Z;
        _Y = Y;

        _x.resize(_Z.rows());
        _E.resizeLike(_x);
        _f.resizeLike(_E);
        _A.resizeLike(_Z);
        _L.resizeLike(_Z);
    }
    else if (mode == 1) { // Initialize with A and Y matrix
        _A = Z;
        _Y = Y;

        _E.resizeLike(_Y); // TODO vector only
        _f.resizeLike(_E);
        _L.resizeLike(_A);
    }

    initialized = true;
}

#endif //LEONTIEF_IO_SYSTEM_H
