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

#include <iostream>
#include <Eigen/LU>

#include "core/io_system.h"

void IOSystem::calc_from_z() {

    _x = _Z.rowwise().sum() + _Y.rowwise().sum();
    _f = _E.array() / _x.array();
    Eigen::DiagonalMatrix<double, Eigen::Dynamic, Eigen::Dynamic> xh(_x.size());
    xh = _x.asDiagonal().inverse();
    _A = _Z * xh;
    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(_x.size(), _x.size());
    _L = (I - _A).inverse();
    _v = _f.transpose() * _L;
    _U = _v.array() * _Y.rowwise().sum().array();

}

void IOSystem::calc_from_a() {

    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(_A.rows(), _A.rows());
    _L = (I - _A).inverse();
    _v = _f.transpose() * _L;
    _U = _v.array() * _Y.rowwise().sum().array();

}