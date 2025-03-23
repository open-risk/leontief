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
        _TPI = colsum;
    }

    void CreateTotalOutput() {
        auto rowsum = _U.rowwise().sum() + _FD.rowwise().sum();
        _TPO = rowsum;
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
        return _TPO;
    }

    Eigen::MatrixXd &getTI() {
        return _TPI;
    }

private:

    // System dimensions

    int n{}; // sectors
    int m{}; // products
    int va{}; // value added types
    int fd{}; // final demand types

    // Matrices and vectors for SUT system storage
    // both input data and computed data

    // Components
    Eigen::MatrixXd _S;  // m x n supply matrix (transpose of n x m make matrix)
    Eigen::MatrixXd _U;  // m x n use matrix
    Eigen::MatrixXd _VA; // va x n value added matrix (part of use table)
    Eigen::MatrixXd _FD; // m x fd final demand matrix (part of use table)

    // Sums
    Eigen::MatrixXd _TII; // total industry input from supply table (1 x n row vector)
    Eigen::MatrixXd _TIO; // total industry output from use table (1 x n row vector)
    Eigen::MatrixXd _TPI; // total product input from use table (m x 1 column vector)
    Eigen::MatrixXd _TPO; // total product output from supply table (m x 1 column vector)

    // Normalizations
    Eigen::MatrixXd _W;
    Eigen::MatrixXd _Qu;
    Eigen::MatrixXd _Qd;

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
