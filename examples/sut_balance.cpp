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
#include <map>
#include <random>
#include "utils/csv.h"
#include "core/sut_system.h"
#include "utils/scan_matrix.h"
#include "utils/matrix_generation.h"
#include "utils/compactify_use_matrix.h"

using namespace csv;

int main(int num_args, char **arg_strings) {

    // LOAD FIGARO-E3 SUPPLY MATRIX
    constexpr int ROWS = 9798;
    constexpr int COLS = 8096;
    Eigen::MatrixXd S(ROWS, COLS);
    CSVReader reader1("../data/supply-e3.csv");

    int Products = S.rows();
    int Sectors = S.cols();

    // Transpose S (Rows->Sectors, Cols->Products)
    // Iterate over rows (Sectors)
    // Sum rows

    auto row_sum = S.transpose().rowwise().sum();
    auto col_sum = S.transpose().colwise().sum();
    for (int j = 0; j < Sectors; j++) {
        std::cout << col_sum(j) << std::endl;
    }
}
