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


#include <Eigen/LU>

#include "core/io_system.h"

using namespace Eigen;


void IOSystem::calc_x() {
    _x = _z.rowwise().sum() + _y.rowwise().sum();
}

void IOSystem::calc_x_from_L() {
    _x = _l * _y;
}

void IOSystem::calc_Z() {
    _z = _a * _x;
}

void IOSystem::calc_A() {
    DiagonalMatrix<double, Dynamic, Dynamic> xh(_x.size());
    xh = _x.asDiagonal().inverse();
    _a = _z * xh;
}

void IOSystem::calc_B() {
    DiagonalMatrix<double, Dynamic, Dynamic> xh(_x.size());
    xh = _x.asDiagonal().inverse();
    _b = xh * _z;
}

void IOSystem::calc_L() {
    MatrixXd I = MatrixXd::Identity(_x.size(), _x.size());
    _l = (I - _a).inverse();
}

void IOSystem::calc_G() {
    MatrixXd I = MatrixXd::Identity(_x.size(), _x.size());
    _g = (I - _b).inverse();
}

void IOSystem::calc_S() {
    DiagonalMatrix<double, Dynamic, Dynamic> xh(_x.size());
    xh = _x.asDiagonal().inverse();
    _f = _e * xh;
}



void IOSystem::calc_from_z() {

    _x = _z.rowwise().sum() + _y.rowwise().sum();
    _f = _e.array() / _x.array();
    DiagonalMatrix<double, Dynamic, Dynamic> xh(_x.size());
    xh = _x.asDiagonal().inverse();
    _a = _z * xh;
    MatrixXd I = MatrixXd::Identity(_x.size(), _x.size());
    _l = (I - _a).inverse();
    _v = _f.transpose() * _l;
    _u = _v.array() * _y.rowwise().sum().array();

}

void IOSystem::calc_from_z2() {

    DiagonalMatrix<double, Dynamic, Dynamic> xh(_x.size());
    std::cout << "Calculate Normalization" << std::endl;
    xh = _x.asDiagonal().inverse();
    std::cout << "Calculate A Matrix" << std::endl;
    _a = _z * xh;
    MatrixXd I = MatrixXd::Identity(_x.size(), _x.size());
    std::cout << "Calculate Leontief Inverse" << std::endl;
    _l = (I - _a).inverse();

}

void IOSystem::calc_from_a() {

    MatrixXd I = MatrixXd::Identity(_a.rows(), _a.rows());
    _l = (I - _a).inverse();
    _v = _f.transpose() * _l;
    _u = _v.array() * _y.rowwise().sum().array();

}