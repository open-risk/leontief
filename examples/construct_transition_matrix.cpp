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

#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include "utils/csv.h"

using namespace csv;

// Load U and S tables
// Concatenate them into a single matrix
//   - putting the S, U pieces together (block operations)
//   - adding additional entries (manual)
// Normalize entries to create probability matrix

int main(int num_args, char **arg_strings) {

    constexpr int MAX_ROW = 2950; // Matrix row size
    constexpr int MAX_COL = 3174; // Matrix col size

    Eigen::MatrixXd U(MAX_ROW, MAX_COL);

    CSVReader reader("../data/matrix_eu-ic-use_24ed_2022.csv");

    double value = 0;
    std::string label;
    int i = 0;
    for (auto &row: reader) {
        for (int j = 0; j < MAX_COL + 1; j++) {
            if (j > 0) {
                value = row[j].get<double>();
                U(i, j - 1) = value;
                // std::cout << i  << " " << j - 1 << " " << value << std::endl;
            } else {
                label = row[j].get_sv();
                // std::cout << i << " " << label << std::endl;
            }
        }
        i++;
        // if (i > 1) break;
    }

    std::cout << "FIGARO Use Matrix of Total Size: " << U.size() << std::endl;
    std::cout << "FIGARO Use Matrix with Rows: " << U.rows() << std::endl;
    std::cout << "FIGARO Use Matrix with Columns: " << U.cols() << std::endl;

    // STEP 1
    // Extract final demand block (230 last columns) into matrix UFD
    // Block of size (p,q), starting at (i,j)
    constexpr int FD = 230;
    Eigen::Map<Eigen::MatrixXd> UFD(U.block<MAX_ROW, FD>(0, MAX_COL - FD).data(), MAX_ROW, FD);

    // Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
    // std::cout << S.row(0).format(CleanFmt) << std::endl;
    // std::cout << UFD.row(0).format(CleanFmt) << std::endl;

    // STEP 2
    // Horizontal Sum (Scan) UFD into column vector FD (One Per Region!)
    const auto tmp = UFD.rowwise().sum();
    // Block of size (p,q), starting at (i,j) 	matrix.block(i, j, p, q);     matrix.block<p, q>(i, j);
    U.block(0, MAX_COL - FD + 1, MAX_ROW, 1) = tmp;

    // std::cout << V << std::endl;
    // std::cout << S.col(MAX_COL - FD + 1) << std::endl;

    // STEP 3
    // Remove block UFD from U -> U'
    // Attach column vector FD to U'
    Eigen::Map<Eigen::MatrixXd> U1(U.block<MAX_ROW, MAX_COL - FD + 1>(0, 0).data(), MAX_ROW, MAX_COL - FD + 1);


    constexpr int NEW_COL = MAX_COL - FD + 1; // New Matrix col size

    // STEP 4
    // Extract value added bloc (6 last rows) from U' into matrix UVA
    // Block of size (p,q), starting at (i,j) 	matrix.block(i, j, p, q);     matrix.block<p, q>(i, j);
    constexpr int VA = 6;
    Eigen::Map<Eigen::MatrixXd> UVA(U1.block<VA, NEW_COL>(MAX_ROW - VA, 0).data(), VA, NEW_COL);

    // STEP 5
    // Vertical Sum UvA into row vector VA
    constexpr int NEW_ROW = MAX_ROW - VA + 1;
    const auto tmp1 = UVA.colwise().sum();
    U1.block(NEW_ROW, 0, 1, NEW_COL) = tmp1;

    // STEP 6
    // Attach row vector VA to U' -> U''
    Eigen::Map<Eigen::MatrixXd> U2(U1.block<NEW_ROW, NEW_COL>(0, 0).data(), NEW_ROW, NEW_COL);

    std::cout << "FIGARO Use Matrix of Total Size: " << U2.size() << std::endl;
    std::cout << "FIGARO Use Matrix with Rows: " << U2.rows() << std::endl;
    std::cout << "FIGARO Use Matrix with Columns: " << U2.cols() << std::endl;

    const static Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n");
    std::ofstream file("test.csv");
    file << U2.format(CSVFormat);

    return 0;
}
