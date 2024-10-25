#  Copyright (C) 2022-2024 Open Risk (www.openriskmanagement.com)
#
#  This file is part of the matrix2json project.
#
#  Licensed under the GPL;
#  you may not use this file except in compliance with the License.


import scipy as sp
import numpy as np
import json

# Create as random sparse matrix

# Select a storage format
# csc: Compressed Sparse Column format
# csr: Compressed Sparse Row format
# bsr: Block Sparse Row format
# lil: List of Lists format
# dok: Dictionary of Keys format
# coo: COOrdinate format (aka IJV or triplet format)
# dia: DIAgonal format

rng = np.random.default_rng()
M = 4
a = sp.sparse.random_array((M, M), density=0.2, format='coo', dtype=float, random_state=rng)
print(a)
b = a.todense()
# Serialize to JSON
s_out = json.dumps(b.tolist())
# Save to disk
f = open("b.json", "w")
f.write(s_out)
f.close()
