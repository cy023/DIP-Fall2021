from PIL import Image
import numpy as np

# Read Origin image
data = np.loadtxt('Image/_subsample.txt')
data = np.flip(data, 0)

# print(data)
# img = Image.fromarray(np.uint8(data), 'L')
# img.save('./Image/_pytime.bmp')
# img.show()

# (-1) ^ (x + y)
for i in range(data.shape[0]):
    for j in range(data.shape[1]):
        data[i, j] = data[i, j] * (-1) ** (i + j)
# print(data)

# FFT
y = np.fft.fft2(data)
spectrum = 10 * np.log(np.abs(y))
# print(spectrum)
img = Image.fromarray(np.uint8(np.round_(spectrum)), 'L')
img.save('./Image/_pyfft.bmp')
# img.show()

# IFFT
x = np.fft.ifft2(y)
for i in range(data.shape[0]):
    for j in range(data.shape[1]):
        x[i, j] = x[i, j] * (-1) ** (i + j)
# print(x)
img = Image.fromarray(np.uint8(x.real), 'L')
img.save('./Image/_pyifft.bmp')
# img.show()
