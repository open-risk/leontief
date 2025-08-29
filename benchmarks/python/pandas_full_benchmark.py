#  Copyright (C) 2022 - 2025 Open Risk (www.openriskmanagement.com)
#
#  This file is part of the matrix2json project.
#
#  Licensed under the GPL;
#  you may not use this file except in compliance with the License.


import numpy as np
import pandas as pd
import json
import time

# Create the matrix
M = 5000
N = M * M
a = np.arange(1, N + 1).reshape(M, M)
print(a[M - 1, M - 1])
# Convert to a data frame
df = pd.DataFrame(a)
start = time.perf_counter()
# Serialize
s_out = df.to_json()
# Save to disk
f = open("a.json", "w")
f.write(s_out)
f.close()
end1time = time.perf_counter()
# Load from disk
m = pd.read_json("a.json").values
print(m[M - 1, M - 1])
end2time = time.perf_counter()
print('Output:', end1time - start)
print('Input:', end2time - end1time)
