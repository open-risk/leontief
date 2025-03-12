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

#ifndef LEONTIEF_OPTIONS_H
#define LEONTIEF_OPTIONS_H

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>
#include <iostream>
#include <Eigen/Dense>


// version

#ifndef LEONTIEF_VERSION_MAJOR
#define LEONTIEF_VERSION_MAJOR 0
#endif

#ifndef LEONTIEF_VERSION_MINOR
#define LEONTIEF_VERSION_MINOR 2
#endif

#ifndef LEONTIEF_VERSION_PATCH
#define LEONTIEF_VERSION_PATCH 0
#endif

#ifdef _MSC_VER
#error Leontief: MSVC is not supported
#endif

#if defined(_OPENMP) && !defined(LEONTIEF_DONT_USE_OPENMP)
#undef LEONTIEF_USE_OPENMP
    #define LEONTIEF_USE_OPENMP
#endif

#if !defined(_OPENMP) && defined(LEONTIEF_USE_OPENMP)
#undef LEONTIEF_USE_OPENMP

    #undef LEONTIEF_DONT_USE_OPENMP
    #define LEONTIEF_DONT_USE_OPENMP
#endif

#ifdef LEONTIEF_DONT_USE_OPENMP
#ifdef LEONTIEF_USE_OPENMP
        #undef LEONTIEF_USE_OPENMP
    #endif
#endif

#ifndef leontief_inline
#define leontief_inline
#endif

// Floating point number type (float or double)

#ifndef LEONTIEF_TOLERANCE
#define LEONTIEF_TOLERANCE 1e-05
#endif

#ifndef LEONTIEF_FPN_TYPE
#define LEONTIEF_FPN_TYPE double
#endif

#if LEONTIEF_FPN_TYPE == float
#undef LEONTIEF_FPN_SMALL_NUMBER
#define LEONTIEF_FPN_SMALL_NUMBER fp_t(1e-05)
#elif LEONTIEF_FPN_TYPE == double
#undef LEONTIEF_FPN_SMALL_NUMBER
    #define LEONTIEF_FPN_SMALL_NUMBER fp_t(1e-08)
#else
    #error Leontief: floating-point number type (LEONTIEF_FPN_TYPE) must be 'float' or 'double'
#endif

//

namespace leontief
{
    using uint_t = unsigned int;
    using fp_t = LEONTIEF_FPN_TYPE;

    using rand_engine_t = std::mt19937_64;

    static const double eps_dbl = std::numeric_limits<fp_t>::epsilon();
    static const double inf = std::numeric_limits<fp_t>::infinity();

    using Mat_t = Eigen::Matrix<fp_t, Eigen::Dynamic, Eigen::Dynamic>;

    using ColVec_t = Eigen::Matrix<fp_t, Eigen::Dynamic, 1>;
    using RowVec_t = Eigen::Matrix<fp_t, 1, Eigen::Dynamic>;

    using ColVecInt_t = Eigen::Matrix<int, Eigen::Dynamic, 1>;
    using RowVecInt_t = Eigen::Matrix<int, 1, Eigen::Dynamic>;

    using ColVecUInt_t = Eigen::Matrix<size_t, Eigen::Dynamic, 1>;
    using RowVecUInt_t = Eigen::Matrix<size_t, 1, Eigen::Dynamic>;
}


#endif //LEONTIEF_OPTIONS_H
