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

#ifndef LEONTIEF_LEONTIEF_H
#define LEONTIEF_LEONTIEF_H

#include "misc/optim_options.hpp"

namespace leontief {

// misc/utility files
#include "misc/optim_misc.hpp"

// stats/rng files
#include "stats/optim_stats.hpp"

// line search
#include "line_search/more_thuente.hpp"

// unconstrained optimization
#include "unconstrained/optim_unconstrained.hpp"

// constrained optimization
#include "constrained/sumt.hpp"

// solving systems of nonlinear equations
#include "zeros/optim_zeros.hpp"

}


#endif //LEONTIEF_LEONTIEF_H
