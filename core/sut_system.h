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

#ifndef LEONTIEF_SUT_SYSTEM_H
#define LEONTIEF_SUT_SYSTEM_H

#include <Eigen/Core>

#pragma once

class SUTSystem {

public:

    /**
    * Create an Supply-Use system with the specified matrices.
    *   S - Supply matrix
    *   U - Use matrix
    */
    SUTSystem(
            const Eigen::MatrixXd &S,
            const Eigen::MatrixXd &U
    );

    /**
    * Create a blank system.
    */
    SUTSystem();

    /**
    * Initialize the system with initial states as zero.
    */
    void init();


private:

    // Matrices and vectors for computation
    Eigen::MatrixXd S, U;

    // System dimensions

    int n{}; // rows
    int m{}; // columns

    // Is the system initialized?
    bool initialized{};


};

SUTSystem::SUTSystem(const Eigen::MatrixXd &S, const Eigen::MatrixXd &U) {

}

SUTSystem::SUTSystem() = default;

void SUTSystem::init() {

}

#endif //LEONTIEF_SUT_SYSTEM_H
