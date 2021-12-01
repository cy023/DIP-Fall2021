import numpy as np

img = np.loadtxt('Image/subsample.txt')
print('===== DATA =====')
print(img)

print('===== FFT =====')
y = np.fft.fft2(img)
print(y)

print('===== IFFT =====')
img = np.fft.ifft2(y)
print(img)
