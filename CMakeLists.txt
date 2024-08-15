# This file is part of the Leontief distribution (https://github.com/open-risk/leontief).
# Copyright (c) 2024 Open Risk (https://www.openriskmanagement.com)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.


# Project metadata
set(PROJECT_VENDOR "Open Risk")
set(PROJECT_CONTACT "info@openrisk.eu")
set(PROJECT_URL "https://github.com/open-risk/leontief")
set(PROJECT_DESCRIPTION "Leontief is a C++ package to work with Input-Output models")

cmake_minimum_required(VERSION 3.19)

# Project name and version
project(leontief)
set(LEONTIEF_VERSION_MAJOR 0)
set(LEONTIEF_VERSION_MINOR 1)
set(LEONTIEF_VERSION_PATCH 0)
set(LEONTIEF_VERSION ${LEONTIEF_VERSION_MAJOR}.${LEONTIEF_VERSION_MINOR}.${LEONTIEF_VERSION_PATCH})

# compiler choices. c++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -std=c++17)
add_definitions("-std=c++17")

# Create verbose output
# TODO Production options
set(CMAKE_VERBOSE_MAKEFILE on)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS_DEBUG)
set(CMAKE_PREFIX_PATH cmake-build-release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_C_FLAGS_RELEASE "-O3")

# Find dependencies (installed via Conan)
find_package(Poco REQUIRED COMPONENTS Foundation Util Net)
find_package(Catch2 REQUIRED)
find_package(Eigen3 REQUIRED)

find_package(OpenMP)

#
#  SOURCE FILES
#

include_directories(.)

# TODO
set(CORE_FILES
        core/leontief.h
        core/options.h
        core/io_system.h
)

# TODO
set(ALGORITHM_FILES
        )

# TODO
set(UTIL_FILES
        utils/generate_matrix.cpp
        utils/utils.h
)

set(TEST_FILES
        testing/test_sanity.cpp
        testing/test_eigen_setup.cpp
        testing/test_loading_lib.cpp
        testing/test_read_exiobase.cpp
        testing/test_load_a_matrix.cpp
        testing/test_leontief_inverse.cpp
        testing/test_ras.cpp
        testing/test_agg.cpp
        testing/test_disagg.cpp
)

set(SOURCE_FILES
        ${CORE_FILES}
        ${ALGORITHM_FILES}
        ${UTIL_FILES})


# DEBUG MODE EXECUTABLE
add_executable(leontief.dbg examples/benchmark.cpp ${SOURCE_FILES})
target_include_directories(leontief.dbg PRIVATE ${Catch2_INCLUDE_DIRS})
target_include_directories(leontief.dbg PRIVATE ${Eigen3_INCLUDE_DIRS})
target_compile_definitions(leontief.dbg PRIVATE DEBUG_MODE=1 LOG_LEVEL=7 VERSION=${LEONTIEF_VERSION})
target_link_libraries(leontief.dbg Catch2::Catch2WithMain Eigen3::Eigen Poco::Foundation Poco::Util Poco::Net)

# PRODUCTION MODE EXECUTABLE
add_executable(leontief.tty examples/benchmark.cpp ${SOURCE_FILES})
target_include_directories(leontief.tty PRIVATE ${Eigen3_INCLUDE_DIRS})
add_compile_options("-O3")
target_compile_definitions(leontief.tty PRIVATE DEBUG_MODE=0 LOG_LEVEL=7 VERSION=${LEONTIEF_VERSION})
target_link_libraries(leontief.tty Eigen3::Eigen Poco::Foundation Poco::Util Poco::Net)

# CATCH2 TESTING
include(Catch)
include(CTest)
enable_testing()

add_executable(unit_tests ${TEST_FILES} ${SOURCE_FILES})

catch_discover_tests(unit_tests)

target_include_directories(unit_tests PRIVATE ${Catch2_INCLUDE_DIRS})
target_include_directories(unit_tests PRIVATE ${Eigen3_INCLUDE_DIRS})
target_compile_definitions(unit_tests PRIVATE DEBUG_MODE=1 LOG_LEVEL=7 VERSION=${LEONTIEF_VERSION})
target_link_libraries(unit_tests Catch2::Catch2WithMain Eigen3::Eigen Poco::Foundation Poco::Util Poco::Net)