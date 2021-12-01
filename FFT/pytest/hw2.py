import cv2 as cv
import numpy as np
from PIL import Image
import random

def uniform_noise(image, upb, lowb):
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

def gaussian_noise(image, mean=0, var=0.01):
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

def saveRaw(data, path):
    img = Image.fromarray(np.uint8(data), 'L')
    img.save(path)

origin = cv.imread('./Image/DIPpic1_gray.bmp', 0)
origin = cv.pyrDown(origin)
saveRaw(origin, './Image/_down.bmp')

shift = pretf(origin)
freq = np.fft.fft2(shift)
magnitude = 20 * np.log10(np.abs(freq))
saveRaw(magnitude, './Image/_freq.bmp')

time = np.fft.ifft2(freq)
time = pretf(time.real)
saveRaw(time, './Image/_restore.bmp')

print("MSE  :", mse(origin, time))
print("PSNR :", psnr(origin, time), "dB")

###########################################################
origin = cv.imread('./Image/DIPpic1_gray.bmp', 0)

print("\n===== S&P noise =====")
sp = sp_noise(origin, 0.01)
print("MSE  :", mse(origin, sp))
print("PSNR :", psnr(origin, sp), "dB")
saveRaw(sp, './Image/_sp.bmp')

print("\n===== Gaussian noise  =====")
gau = gaussian_noise(origin)
print("MSE  :", mse(origin, gau))
print("PSNR :", psnr(origin, gau), "dB")
saveRaw(sp, './Image/_gua.bmp')

print("\n===== Uniform noise =====")
unf = uniform_noise(origin, 10, -10)
print("MSE  :", mse(origin, unf))
print("PSNR :", psnr(origin, unf), "dB")
saveRaw(unf, './Image/_unf.bmp')