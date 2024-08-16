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

#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iostream>
#include <random>
#include <chrono>



std::string get_current_time();

std::string get_current_time() {
    time_t t = time(nullptr);
    struct tm *now = localtime(&t);
    std::stringstream current_time;

    current_time << (now->tm_year + 1900) << '-'
                 << (now->tm_mon + 1) << '-'
                 << now->tm_mday << '-'
                 << now->tm_hour << '-'
                 << now->tm_min << '-'
                 << now->tm_sec;

    std::string c_time = current_time.str();
    return c_time;
}


#endif /* UTILS_H */

