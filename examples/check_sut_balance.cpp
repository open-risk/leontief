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

// TODO investigate FIGARO balance relations

using namespace csv;

/*
 *# EXAMPLE 6: CHECK SUT Balance
 */
int main(int num_args, char **arg_strings) {
    // LOAD FIGARO-E3 SUPPLY MATRIX
    // constexpr int ROWS = 9798;
    // constexpr int COLS = 8096;
    // Eigen::MatrixXd S(ROWS, COLS);
    // CSVReader reader1("../data/supply-e3.csv");

    constexpr int SROWS = 2944;
    constexpr int SCOLS = 2944;
    Eigen::MatrixXd S(SROWS, SCOLS);
    CSVReader reader1("../data/supply.csv");
    double value = 0;
    int i = 0;
    for (auto &row: reader1) {
        for (int j = 0; j < SCOLS; j++) {
            value = S(i, j) = row[j].get<double>();
        }
        i++;
    }
    std::cout << "FIGARO Supply Matrix Checksum: " << S.sum() << std::endl;

    constexpr int UROWS = 2950;
    constexpr int UCOLS = 3174;
    constexpr int FD = 230;
    constexpr int VA = 6;
    CSVReader reader2("../data/use.csv");

    Eigen::MatrixXd UP(UROWS, UCOLS);

    i = 0;
    for (auto &row: reader2) {
        for (int j = 0; j < UCOLS; j++) {
            UP(i, j) = row[j].get<double>();
        }
        i++;
    }
    std::cout << "FIGARO Use Matrix with Rows: " << UP.rows() << std::endl;
    std::cout << "FIGARO Use Matrix with Columns: " << UP.cols() << std::endl;
    std::cout << "FIGARO Use Matrix Checksum: " << UP.sum() << std::endl;

    auto col_sum1 = S.colwise().sum();
    auto col_sum2 = UP.colwise().sum();

    for (int j = 0; j < 100; j++) {
        std::cout << j << " " << col_sum1(j) << " " << col_sum2(j) << std::endl;
    }

}
