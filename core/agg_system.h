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

#ifndef LEONTIEF_AGG_SYSTEM_H
#define LEONTIEF_AGG_SYSTEM_H

#include <Eigen/Core>
#include <iostream>

#pragma once

/**
 * @brief Class holding an IO aggregation system
 * *
 * @date 2025-09-02
 *
 */
class AggSystem {

public:

    AggSystem();

    AggSystem(const Eigen::MatrixXd &X);

    Eigen::MatrixXd getS() {
        return _s;
    }

    Eigen::MatrixXd getSt() {
        return _s.transpose();
    }

private:

    // Matrix for Aggregation
    Eigen::MatrixXd _s;

    // System dimensions
    int n{}; // rows
    int m{}; // columns

    // Is the system initialized?
    bool initialized{};


};

/**
 * @brief
 */
inline AggSystem::AggSystem() = default;

/**
 *
 * @brief Create an Input-Output aggregation system with a specified matrix.
 *
 *
 * @param X
 */
inline AggSystem::AggSystem(const Eigen::MatrixXd &X) {

    _s = X;
    initialized = true;
}

#endif //LEONTIEF_AGG_SYSTEM_H
