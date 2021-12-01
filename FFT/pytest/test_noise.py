from PIL import Image
import numpy as np
import random

def uniform_noise(image, lowb, upb):
    buff = np.zeros(image.shape, np.uint8)
    prob = 1 / (upb - lowb)
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            rdn = random.random()
            tmp = image[i][j]
            if rdn < prob:
                _noise = random.uniform(upb, lowb)
                if tmp + _noise > 255:
                    buff[i][j] = 255
                elif tmp + _noise < 0:
                    buff[i][j] = 0
                else:
                    buff[i][j] = tmp + _noise
            else:
                buff[i][j] = tmp
    return buff

def sp_noise(image, prob):
    buff = np.zeros(image.shape, np.uint8)
    thres = 1 - prob
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            rdn = random.random()
            if rdn < prob:
                buff[i][j] = 0
            elif rdn > thres:
                buff[i][j] = 255
            else:
                buff[i][j] = image[i][j]
    return buff

def gaussian_noise(image, mean=0, var=0.001):
    image = np.array(image/255, dtype=float)
    noise = np.random.normal(mean, var ** 0.5, image.shape)
    buff = image + noise
    if buff.min() < 0:
        low_clip = -1.
    else:
        low_clip = 0.
    buff = np.clip(buff, low_clip, 1.0)
    buff = np.uint8(buff*255)
    return buff

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

print("\n===== FFT =====")
print("MSE  :", mse(origin, x))
print("PSNR :", psnr(origin, x), "dB")

sp = sp_noise(x, 0.001)
img = Image.fromarray(np.uint8(sp), 'L')
img.save('./Image/_sp.bmp')

print("\n===== S&P noise =====")
print("MSE  :", mse(origin, sp))
print("PSNR :", psnr(origin, sp), "dB")

gau = gaussian_noise(x)
img = Image.fromarray(np.uint8(gau), 'L')
img.save('./Image/_gua.bmp')

print("\n===== Gaussian noise  =====")
print("MSE  :", mse(origin, gau))
print("PSNR :", psnr(origin, gau), "dB")

unf = uniform_noise(x, -20, 20)
img = Image.fromarray(np.uint8(unf), 'L')
img.save('./Image/_unf.bmp')

print("\n===== Uniform noise =====")
print("MSE  :", mse(origin, unf))
print("PSNR :", psnr(origin, unf), "dB")

# Parameters
# ----------
# image : ndarray
#     Input image data. Will be converted to float.
# mode : str
#     One of the following strings, selecting the type of noise to add:

#     'gauss'     Gaussian-distributed additive noise.
#     'poisson'   Poisson-distributed noise generated from the data.
#     's&p'       Replaces random pixels with 0 or 1.
#     'speckle'   Multiplicative noise using out = image + n*image,where
#                 n is uniform noise with specified mean & variance.
# import numpy as np
# import os
# import cv2
# def noisy(noise_typ,image):
#     if noise_typ == "gauss":
#         row,col,ch= image.shape
#         mean = 0
#         var = 0.1
#         sigma = var**0.5
#         gauss = np.random.normal(mean,sigma,(row,col,ch))
#         gauss = gauss.reshape(row,col,ch)
#         noisy = image + gauss
#         return noisy
#     elif noise_typ == "s&p":
#         row,col,ch = image.shape
#         s_vs_p = 0.5
#         amount = 0.004
#         out = np.copy(image)
#         # Salt mode
#         num_salt = np.ceil(amount * image.size * s_vs_p)
#         coords = [np.random.randint(0, i - 1, int(num_salt))
#                 for i in image.shape]
#         out[coords] = 1

#         # Pepper mode
#         num_pepper = np.ceil(amount* image.size * (1. - s_vs_p))
#         coords = [np.random.randint(0, i - 1, int(num_pepper))
#                 for i in image.shape]
#         out[coords] = 0
#         return out
#     elif noise_typ == "poisson":
#         vals = len(np.unique(image))
#         vals = 2 ** np.ceil(np.log2(vals))
#         noisy = np.random.poisson(image * vals) / float(vals)
#         return noisy
#     elif noise_typ =="speckle":
#         row,col,ch = image.shape
#         gauss = np.random.randn(row,col,ch)
#         gauss = gauss.reshape(row,col,ch)        
#         noisy = image + image * gauss
#         return noisy
