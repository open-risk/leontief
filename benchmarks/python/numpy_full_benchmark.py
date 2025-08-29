#  Copyright (C) 2022 - 2025 Open Risk (www.openriskmanagement.com)
#
#  This file is part of the matrix2json project.
#
#  Licensed under the GPL;
#  you may not use this file except in compliance with the License.


import numpy as np
import json
import time

# Create the matrix
M = 5000
N = M * M
a = np.arange(1, N + 1).reshape(M, M)
print(a[M - 1, M - 1])
start = time.perf_counter()
# Serialize
s_out = json.dumps(a.tolist())
# Save to disk
f = open("a.json", "w")
f.write(s_out)
f.close()
end1time = time.perf_counter()
# Load from disk
f = open("a.json", "r")
m = np.array(json.loads(f.read()))
print(m[M - 1, M - 1])
end2time = time.perf_counter()
print('Output:', end1time - start)
print('Input:', end2time - end1time)
