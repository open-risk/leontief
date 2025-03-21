from PIL import Image
import numpy as np
# array_data = np.loadtxt('../data/use.csv', delimiter=",")
array_data = np.loadtxt('../data/figaro_qu.csv', delimiter=",")
array_data = np.abs(array_data)
print(array_data.min(), array_data.max())
shift = 0.01
array_data += shift
print(array_data.min(), array_data.max())
data = np.log(array_data)
print(data.min(), data.max())
shift = data.min()
data -= shift
print(data.min(), data.max())
data *= 255.0/data.max()
data = data.astype(np.uint8)
image_file_name = 'supply.png'
image = Image.fromarray(data)
image.save(image_file_name)