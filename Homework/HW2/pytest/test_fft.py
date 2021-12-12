import numpy as np

x = np.array([4.0, 2.0, 1.0, -3.0, 1.5, 0, 0, 0])

print('===== DATA =====')
print(x)

print('===== FFT =====')
y = np.fft.fft(x)
print(y)

print('===== IFFT =====')
x = np.fft.ifft(y)
print(x)
