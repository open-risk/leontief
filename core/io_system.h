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
    *   y - Final demand vector
    */
    IOSystem(
            const Eigen::MatrixXd &Z,
            const Eigen::MatrixXd &Y,
            const Eigen::MatrixXd &A,
            const Eigen::MatrixXd &x,
            const Eigen::MatrixXd &L
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

private:

    // Matrices and vectors for computation
    Eigen::MatrixXd A, Z, Q, R, P, K, P0;

    // System dimensions (for Symmetric IO should be identical)
    int n{}; // rows
    int m{}; // columns

    // Is the system initialized?
    bool initialized{};

    // n x n -sized identity
    Eigen::MatrixXd I;

};

IOSystem::IOSystem(const Eigen::MatrixXd &A, const Eigen::MatrixXd &Z, const Eigen::MatrixXd &x, const Eigen::MatrixXd &y, const Eigen::MatrixXd &L) {

}

IOSystem::IOSystem() = default;

void IOSystem::init() {

}

void IOSystem::init(double t0, const Eigen::VectorXd &x0) {

}

void IOSystem::update(const Eigen::VectorXd &y) {

}

void IOSystem::update(const Eigen::VectorXd &y, double dt, const Eigen::MatrixXd A) {

}

#endif //LEONTIEF_IO_SYSTEM_H
