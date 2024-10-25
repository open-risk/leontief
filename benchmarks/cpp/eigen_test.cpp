/**
 ################################################################################
 ##
 ##  Copyright (C) 2022-2024 Open Risk (www.openriskmanagement.com)
 ##
 ##  This file is part of the matrix2json project.
 ##
 ##  Licensed under the GPL;
 ##  you may not use this file except in compliance with the License.
 ################################################################################
 */

///
/// File:   eigen_test.cpp
///

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>

using namespace std;
using namespace Eigen;

int main(int argc, const char **argv) {

    IOFormat HeavyFmt(FullPrecision, 0, ", ", ",\n", "[", "]", "[", "]");

    // Initialize and print a random sparse matrix
    int n = 4;  // size of matrix
    int k = 4; // number of non-zero elements
    typedef Eigen::Triplet<double> T;
    std::vector<T> tripletList;
    tripletList.reserve(4);

    std::cout << "Sparse Matrix B in Coordinates Format" << std::endl;
    std::cout << "i" << "  " <<  "j" << "  " << "v" << std::endl;
    for (int e = 0; e < k; e++) {
        int i = rand() % 4;
        int j = rand() % 4;
        double v = rand() % 1000;
        std::cout << i << "  " <<  j << "  " << v << std::endl;
        tripletList.push_back(T(i, j, v));
    }
    SparseMatrix<double> B(n, n);
    B.setFromTriplets(tripletList.begin(), tripletList.end());
    std::cout << "Sparse Matrix B in Array of Arrays Format:\n" << B.toDense().format(HeavyFmt) << std::endl;

    return 0;
}