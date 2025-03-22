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
    *   VA - Value Added matrix
    *   FD - Final Demand matrix
    *   W - Transactions matrix
    *   Qu - Upstream probabilities
    *   Qd - Downstream probabilities
    */
    SUTSystem(
        Eigen::MatrixXd &S,
        Eigen::MatrixXd &U,
        Eigen::MatrixXd &VA,
        Eigen::MatrixXd &FD
    );

    SUTSystem() = default;

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

        // TODO test for squareness

        _Qu.resizeLike(_W);
        _Qu.setZero();

        auto colsum = _W.colwise().sum();

         for (int j = 0; j < _W.cols(); j++)
             if (colsum(j) > 0) _Qu.col(j) = _W.col(j) / colsum(j);

        _Qu(unitRow, unitCol) = 1.0;

    }

    void CreateTotalInput() {
        auto colsum = _S.colwise().sum() + _VA.colwise().sum();
        _TI = colsum;
    }

    void CreateTotalOutput() {
        auto rowsum = _U.rowwise().sum() + _FD.rowwise().sum();
        _TO = rowsum;
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

    Eigen::MatrixXd &getTO() {
        return _TO;
    }

    Eigen::MatrixXd &getTI() {
        return _TI;
    }

private:
    // Matrices and vectors for computation
    Eigen::MatrixXd
            _S, _U, _VA, _FD, _TI, _TO, _W, _Qu, _Qd;

    // System dimensions

    int N{}; // total size
    int n{}; // sectors
    int m{}; // products
    int va{}; // value added types
    int fd{}; // final demand types

    // Is the system initialized?
    bool initialized{};
};

inline SUTSystem::SUTSystem(Eigen::MatrixXd &S, Eigen::MatrixXd &U,Eigen::MatrixXd &VA, Eigen::MatrixXd &FD) {
    _S = S;
    _U = U;
    _VA = VA;
    _FD = FD;
    initialized = true;
}

#endif //LEONTIEF_SUT_SYSTEM_H
