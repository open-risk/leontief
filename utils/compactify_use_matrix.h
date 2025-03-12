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

#ifndef COMPACTIFY_USE_MATRIX_H
#define COMPACTIFY_USE_MATRIX_H

#include <Eigen/Core>

#include <fstream>
#include <iostream>
#include <random>
#include <chrono>


inline Eigen::MatrixXd CompactifyUseMatrix(Eigen::MatrixXd &U, int FD, int VA) {
    int MAX_ROW = U.rows();
    int MAX_COL = U.cols();

    // Eigen Block Syntax
    // Block of size (p,q), starting at (i,j)
    // matrix.block(i, j, p, q);
    // matrix.block<p, q>(i, j);

    // STEP 1
    // Extract final demand block (230 last columns) into matrix UFD
    auto ufd = U.block(0, MAX_COL - FD, MAX_ROW, FD);
    // STEP 2
    // Horizontal Sum (Scan) UFD into column vector FD (One Per Region!)
    auto tmp = ufd.rowwise().sum();
    // STEP 3
    // Attach column vector FD to U'
    U.block(0, MAX_COL - FD, MAX_ROW, 1) = tmp;
    // STEP 4
    // Extract value added bloc (6 last rows) from U' into matrix UVA
    auto uva = U.block(MAX_ROW - VA, 0, VA, MAX_COL);
    int NEW_COL = MAX_COL - FD;
    int NEW_ROW = MAX_ROW - VA;
    // STEP 5
    // Vertical Sum UvA into row vector VA
    auto tmp1 = uva.colwise().sum();
    // STEP 6
    // Attach row vector VA to U' -> U''
    U.block(NEW_ROW, 0, 1, MAX_COL) = tmp1;

    return U.block(0, 0, NEW_ROW + 1, NEW_COL + 1);
}


#endif /* COMPACTIFY_USE_MATRIX_H */
