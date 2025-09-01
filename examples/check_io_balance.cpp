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
#include "utils/csv.h"
#include "utils/scan_matrix.h"

// TODO investigate OECD-ICIO balance relations

using namespace csv;

int main(int num_args, char **arg_strings) {
    int n = 4050; // total sectors
    int fd = 486; // final demand types
    int va = 2; // value added types


    Eigen::MatrixXd Z(n, n);      // n x n transactions matrix
    Eigen::MatrixXd FD(n, fd);    // n x fd final demand matrix
    Eigen::MatrixXd VA(va, n + fd);    // va x n value added matrix

    Eigen::VectorXd Oc(n);   // output column vector
    Eigen::RowVectorXd Or(n);         // output row vector

    constexpr int ROWS = 4053; // csv row dimension (not used by csvreader)
    constexpr int COLS = 4537; // csv col dimension

    CSVFormat format;
    format.delimiter(',').no_header();

    CSVReader reader("../data/oecd-2017-2022/icio.csv", format);

    double value;
    int i = 0;
    for (auto &row: reader) {
        for (int j = 0; j < COLS; j++) {
            value = row[j].get<double>();
            if (i < n && j < n) {
                Z(i, j) = value;
            } else if (i < n && j < COLS - 1 && j >= n) {
                FD(i, j - n) = value;
            } else if (i < n && j == COLS - 1) {
                Oc(i) = value;
            } else if (i >= ROWS - va - 1  && i < ROWS - 1 && j < COLS - 1) {
                std::cout << "VA: " << i << " - " << j << " - " << value << std::endl;
                VA(i - n, j) = value;
            } else if (i == ROWS - 1 && j < n) {
                Or(j) = value;
                std::cout << "Or: " << i << " - " << j << " - " << value << std::endl;
            }
        }
        i++;
    }

    std::cout << Or.sum() << std::endl;
    std::cout << Oc.sum() << std::endl;
}
