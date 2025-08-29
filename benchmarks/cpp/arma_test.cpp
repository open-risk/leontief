/**
 ################################################################################
 ##
 ##  Copyright (C) 2022 - 2025 Open Risk (www.openriskmanagement.com)
 ##
 ##  This file is part of the matrix2json project.
 ##
 ##  Licensed under the GPL;
 ##  you may not use this file except in compliance with the License.
 ################################################################################
 */


///
/// File:   arma_test.cpp
///

#include <iostream>
#include <armadillo>

int main(int argc, const char **argv) {
    // Initialize the random generator
    arma::arma_rng::set_seed_random();

    // Create a 4x4 random matrix and print it on the screen
    arma::Mat<double> A = arma::randu(4, 4);
    std::cout << "A:\n" << A << "\n";

    // Create a new diagonal matrix using the main diagonal of A:
    arma::Mat<double> B = arma::diagmat(A);
    std::cout << "B:\n" << B << "\n";

    // Save matrices A and B using COO format:
    A.save("A_mat.txt", arma::coord_ascii);
    B.save("B_mat.txt", arma::coord_ascii);

    return 0;
}