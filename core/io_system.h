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
    *   A - System dynamics matrix
    *   C - Output matrix
    *   Q - Process noise covariance
    *   R - Measurement noise covariance
    *   P - Estimate error covariance
    */
    IOSystem(
            double dt,
            const Eigen::MatrixXd& A,
            const Eigen::MatrixXd& C,
            const Eigen::MatrixXd& Q,
            const Eigen::MatrixXd& R,
            const Eigen::MatrixXd& P
    );

    /**
    * Create a blank estimator.
    */
    IOSystem();

    /**
    * Initialize the system with initial states as zero.
    */
    void init();

    /**
    * Initialize the filter with a guess for initial states.
    */
    void init(double t0, const Eigen::VectorXd& x0);

    /**
    * Update the estimated state based on measured values.
    */
    void update(const Eigen::VectorXd& y);

    /**
    * Update the estimated state based on measured values
    */
    void update(const Eigen::VectorXd& y, double dt, Eigen::MatrixXd A);

    /**
    * Return the current state and time.
    */
    Eigen::VectorXd state() { return x_hat; };
    [[nodiscard]] double current_time() const { return t; };

private:

    // Matrices for computation
    Eigen::MatrixXd A, C, Q, R, P, K, P0;

    // System dimensions
    int m{}, n{};

    // Initial and current time
    double t0{}, t{};

    // Discrete time step
    double dt{};

    // Is the system initialized?
    bool initialized{};

    // n-size identity
    Eigen::MatrixXd I;

    // Estimated states
    Eigen::VectorXd x_hat, x_hat_new;
};

IOSystem::IOSystem(double dt, const Eigen::MatrixXd &A, const Eigen::MatrixXd &C, const Eigen::MatrixXd &Q,
                   const Eigen::MatrixXd &R, const Eigen::MatrixXd &P) {

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
