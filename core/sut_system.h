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

#ifndef LEONTIEF_SUT_SYSTEM_H
#define LEONTIEF_SUT_SYSTEM_H

#include <Eigen/Core>

#pragma once

using namespace Eigen;

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
        MatrixXd &S,
        MatrixXd &U,
        MatrixXd &VA,
        MatrixXd &FD
    );

    SUTSystem() = default;

    void CreateTransactionsMatrix(const MatrixXd &M, const MatrixXd U) {
        int wy = M.cols() + U.cols() + 1;
        int wx = M.rows() + U.rows() + 1;
        _W.resize(wx, wy);
        _W.setZero();
        _W.block(U.rows(), 0, M.rows(), M.cols()) = M;
        _W.block(0, M.cols() + 1, U.rows(), U.cols()) = U;
    }

    /*
     * Inputs are the matrix coordinates of the unit value
     */
    void CreateUpstreamProbabilities(int unitRow, int unitCol) {
        _Qu.resizeLike(_W);
        _Qu.setZero();

        auto colsum = _W.colwise().sum();

        // Normalize non-zero columns
        for (int j = 0; j < _W.cols(); j++) {
            if (colsum(j) != 0) {
                _Qu.col(j) = _W.col(j) / colsum(j);
            }
        }

        // Set absorbing node
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

    MatrixXd &getW() {
        return _W;
    }

    MatrixXd &getQu() {
        return _Qu;
    }

    MatrixXd &getTO() {
        return _TPO;
    }

    MatrixXd &getTI() {
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
    MatrixXd _S; // m x n supply matrix (transpose of n x m make matrix)
    MatrixXd _U; // m x n use matrix
    MatrixXd _VA; // va x n value added matrix (part of use table)
    MatrixXd _FD; // m x fd final demand matrix (part of use table)

    // Sums
    MatrixXd _TII; // total industry input from supply table (1 x n row vector)
    MatrixXd _TIO; // total industry output from use table (1 x n row vector)
    MatrixXd _TPI; // total product input from use table (m x 1 column vector)
    MatrixXd _TPO; // total product output from supply table (m x 1 column vector)

    // Normalizations
    MatrixXd _W;
    MatrixXd _Qu;
    MatrixXd _Qd;

    // Is the system initialized?
    bool initialized{};
};

inline SUTSystem::SUTSystem(MatrixXd &S, MatrixXd &U, MatrixXd &VA, MatrixXd &FD) {
    _S = S;
    _U = U;
    _VA = VA;
    _FD = FD;
    initialized = true;
}

#endif //LEONTIEF_SUT_SYSTEM_H
