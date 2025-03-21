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
    * Create a Supply-Use system with the specified matrices.
    *   S - Supply matrix
    *   U - Use matrix
    *   W - Transactions matrix
    *   Qu - Upstream probabilities
    *   Qd - Downstream probabilities
    */
    SUTSystem(
        Eigen::MatrixXd &S,
        Eigen::MatrixXd &U,
        Eigen::MatrixXd &W,
        Eigen::MatrixXd &Qu,
        Eigen::MatrixXd &Qd
    );

    /**
    * Create an empty system.
    */
    SUTSystem();

    /**
    * Initialize the system with initial states as zero.
    */
    void init();

    void CreateTransactionsMatrix(const Eigen::MatrixXd &S, const Eigen::MatrixXd U) {
        int wx = S.cols() + U.cols() + 1;
        int wy = S.rows() + U.rows() + 1;
        _W.resize(wx, wy);
        _W.setZero();
        _W.block(U.rows(),0, S.rows(), S.cols()) = S;
        _W.block(0,S.cols()+1, U.rows(), U.cols()) = U;
    }

    /*
     * Inputs are the matrix coordinates of the unit value
     */
    void CreateUpstreamProbabilities(int unitCol, int unitRow) {

        _Qu.resizeLike(_W);
        _Qu.setZero();

        auto colsum = _W.colwise().sum();

         for (int j = 0; j < _W.cols(); j++)
             if (colsum(j) > 0) _Qu.col(j) = _W.col(j) / colsum(j);

        _Qu(unitRow, unitCol) = 1.0;

    }

    void CreateDownstreamProbabilities() {
        _Qd = _W;
    }

    Eigen::MatrixXd &getW() {
        return _W;
    }

    Eigen::MatrixXd &getQu() {
        return _Qu;
    }

private:
    // Matrices and vectors for computation
    Eigen::MatrixXd
            _S, _U, _W, _Qu, _Qd;

    // System dimensions

    int N{}; // total size
    int n{}; // sectors
    int m{}; // products

    // Is the system initialized?
    bool initialized{};
};

inline SUTSystem::SUTSystem(Eigen::MatrixXd &S, Eigen::MatrixXd &U, Eigen::MatrixXd &W, Eigen::MatrixXd &Qu,
                            Eigen::MatrixXd &Qd) {
    _S = S;
    _U = U;
    _W = W;
    _Qu = Qu;
    _Qd = Qd;
    initialized = true;
}

inline SUTSystem::SUTSystem() = default;

inline void SUTSystem::init() {
}

#endif //LEONTIEF_SUT_SYSTEM_H
