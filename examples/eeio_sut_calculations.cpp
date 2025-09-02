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
#include "core/sut_system.h"
#include "utils/scan_matrix.h"
#include "utils/sut_matrix_generation.h"

/*
 * # EXAMPLE 7: EEIO SUT Calculations
 */
int main(int num_args, char **arg_strings) {

    int m = 2; // product count
    int n = 2; // sector count
    int fd = 1; // final demand count
    int va = 1; // value added count
    int mode = 1; // select test

    // Insert test data
    Eigen::MatrixXd S = TestSupplyMatrix(m, n, mode);
    Eigen::MatrixXd U = TestUseMatrix(m, n, mode);
    Eigen::MatrixXd VA = TestVAMatrix(n, va, mode);
    Eigen::MatrixXd FD = TestFDMatrix(m, va, mode);

    SUTSystem SUT(S, U, VA, FD);
    SUT.CreateTransactionsMatrix(S, U);
    SUT.CreateUpstreamProbabilities(m, m);
    std::cout << "W: " << SUT.getW() << std::endl;

    std::cout << "Column-wise norm check: " << TestColumnNorm(SUT.getQu()) << std::endl;
    std::cout << "Probability check: " << TestProbabilities(SUT.getQu()) << std::endl;

    // std::cout << "W: " << testSUT.getW() << std::endl;
    auto Q = SUT.getQu();
    std::cout << "Q: " << Q << std::endl;
    std::cout << "|Q|: " << Q.determinant() << std::endl;

    int size = Q.cols();

    // auto QR = Q.block(0, 0, size-1, size-1);
    auto QR = Q;

    std::cout << "QR: " << QR << std::endl;
    std::cout << "|QR|: " << QR.determinant() << std::endl;

    // Impact intensity per product (zero for sectors)
    Eigen::VectorXd Intensity = TestIntensity(m, n, 1);
    std::cout << "Intensity: " << Intensity.transpose() << std::endl;

    int iterations = 11;
    Eigen::VectorXd Impact(iterations);
    Impact.setZero();

    Eigen::VectorXd Pm1(size);
    Eigen::VectorXd P(size);
    Pm1.setZero();
    // Pm1(n + m + 1) = 1.0;
    Pm1(3) = 1.0;
    std::cout << "Probability: " << Pm1.transpose() << std::endl;

    std::cout.precision(2);
    std::cout << "P(0) = " << Pm1.transpose() << std::endl;
    for (int k=0; k < iterations; k++) {
        P = QR * Pm1;
        Pm1 = P;
        Impact(k) = Intensity.transpose() * P;
        std::cout << "P(" << k+1 << ") = " << P.transpose() << std::endl;
        std::cout << "I(" << k+1 << ") = " << Impact(k) << std::endl;
    }

    std::cout << "------------------" << std::endl;
    std::cout << "I: " << Impact.sum() << std::endl;

}
