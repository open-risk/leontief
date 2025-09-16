# This file is part of the Leontief distribution (https://github.com/open-risk/leontief).
# Copyright (c) 2024 - 2025 Open Risk (https://www.openriskmanagement.com)
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

# load use table in both flat file and matrix format
import pandas as pd
import numpy as np

u_fla = pd.read_csv('../data/flatfile_eu-ic-use_24ed_2022.csv')
u_mat = pd.read_csv('../data/matrix_eu-ic-use_24ed_2022.csv')

# icuseCol_mat = u_mat.columns.tolist()[1:]
# icuseRow_mat = u_mat['rowLabels'].to_list()
# icuseRow_fla = u_fla['icuseRow'].to_list()
# icuseCol_fla = u_fla['icuseCol'].to_list()
# print(len(icuseCol_fla))
# print(len(icuseRow_fla))

u_mat = u_mat.drop('rowLabels', axis=1)
mat = u_mat.to_numpy()
# print(mat)

ROWS = 2950
COLS = 3174
index = 0
fla = np.empty(shape=(ROWS, COLS))
for row in u_fla.itertuples(index=False):
    value = row[6]
    row_label = row[0]
    col_label = row[1]
    col_index = index % COLS
    row_index = int(index / COLS)
    fla[row_index, col_index] = value
    index += 1
    # print(index, row_label, row_index, col_label, col_index, value)

# print(fla)

# error_count = 0
# for i in range(MAX):
#     for j in range(MAX):
#         if mat[i, j] != fla[i, j]:
#             print(icsupRow_mat[i], icsupCol_mat[j], mat[i, j])
#             print(s_fla.iloc[i * MAX + j, s_fla.columns.get_loc('icsupRow')], s_fla.iloc[i * MAX + j, s_fla.columns.get_loc('icsupCol')], s_fla.iloc[i * MAX + j, s_fla.columns.get_loc('obsValue')], fla[i, j])
#             print(80*'=')
#             error_count += 1
#
# print(error_count)
