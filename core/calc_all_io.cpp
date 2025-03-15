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

void IOSystem::calc_all_io() {

/*
    *Z Table (Industry Transactions):
    F    E
    F  200  100
    E   80   50

    Y Table (Demand):
    G    A
    F  300  100
    E  200  150

    x Vector (Total Output):
    indout
    F     700
    E     480

    A Table (Normalized Transactions):
    F         E
    F  0.285714  0.208333
    E  0.114286  0.104167

    L Table (Leontief Inverse):
    F         E
    F  1.454106  0.338164
    E  0.185507  1.159420
    */



    _x = _Z.rowwise().sum() + _Y.rowwise().sum();
    std::cout << _x << std::endl;

    _f = _E.array() / _x.array();
    Eigen::DiagonalMatrix<double, Eigen::Dynamic, Eigen::Dynamic> xh(_x.size());
    xh = _x.asDiagonal().inverse();

    std::cout << xh.toDenseMatrix() << std::endl;

    _A = _Z * xh;

    std::cout << _A << std::endl;

    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(_x.size(), _x.size());

    std::cout << I << std::endl;

    _L = (I - _A).inverse();

    std::cout << _L << std::endl;

    _v = _f.transpose() * _L;

    std::cout << _v << std::endl;

    _U = _v.array() * _Y.rowwise().sum().array();

    std::cout << _U << std::endl;

}
