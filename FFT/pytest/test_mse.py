from PIL import Image
import numpy as np

def mse(img1, img2) -> float:
    err = np.sum((img1 - img2) ** 2)
    err /= (img1.shape[0] * img1.shape[1])
    return err

def psnr(img1, img2) -> float:
    return 10 * np.log10(255*255 / mse(img1, img2))

def pretf(matrix):
    buff = np.zeros(matrix.shape, np.uint8)
    for i in range(matrix.shape[0]):
        for j in range(matrix.shape[1]):
            buff[i][j] = matrix[i][j] * (-1) ** (i + j)    
    return buff

# Read Origin image
origin = np.loadtxt('Image/_subsample.txt')
origin = np.flip(origin, 0)

# FFT
data = pretf(origin)
y = np.fft.fft2(data)

spectrum = 10 * np.log(np.abs(y))
img = Image.fromarray(np.uint8(np.round_(spectrum)), 'L')
img.save('./Image/_pyfft.bmp')

# IFFT
x = np.fft.ifft2(y)
x = pretf(x.real)

img = Image.fromarray(np.uint8(x), 'L')
img.save('./Image/_pyifft.bmp')

print("MSE  :", mse(origin, x))
print("PSNR :", psnr(origin, x), "dB")
