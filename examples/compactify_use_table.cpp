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
#include "utils/csv.h"
#include "utils/compactify_use_matrix.h"

using namespace csv;

/*
 *  Compactify the Final Demand and Value Added columns / rows of a Use matrix into one column and row respectively
 */
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

    // Eigen::IOFormat CleanFmt(4, 0, ", ", "\n", "[", "]");
    // std::cout << S.row(0).format(CleanFmt) << std::endl;

    std::cout << "FIGARO Use Matrix of Total Size: " << U.size() << std::endl;
    std::cout << "FIGARO Use Matrix with Rows: " << U.rows() << std::endl;
    std::cout << "FIGARO Use Matrix with Columns: " << U.cols() << std::endl;

    constexpr int FD = 230;
    constexpr int VA = 6;
    Eigen::MatrixXd U2 = CompactifyUseMatrix(U, FD, VA);

    std::cout << "Compactified Use Matrix of Total Size: " << U2.size() << std::endl;
    std::cout << "Compactified Use Matrix with Rows: " << U2.rows() << std::endl;
    std::cout << "Compactified Use Matrix with Columns: " << U2.cols() << std::endl;

    const static Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n");
    std::ofstream file("test.csv");
    file << U2.format(CSVFormat);

    return 0;
}
