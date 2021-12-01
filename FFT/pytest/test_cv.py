import cv2 as cv
import numpy as np
# from matplotlib import pyplot as plt
from PIL import Image

img = cv.imread('./Image/_subsample.bmp', 0)
f = np.fft.fft2(img)
fshift = np.fft.fftshift(f)
mag_spectrum = 20 * np.log(np.abs(fshift))

image = Image.fromarray(np.uint8(img), 'L')
image.save('./Image/_cvtime.bmp')

image = Image.fromarray(np.uint8(mag_spectrum), 'L')
image.save('./Image/_cvfreq.bmp')

# plt.imshow(img, cmap='gray')
# plt.show()
# plt.imshow(mag_spectrum, cmap='gray')
# plt.show()

# for i in range(magnitude_spectrum.shape[0]):
#     for j in range(magnitude_spectrum.shape[1]):
#         if magnitude_spectrum[i, j] < 0 or magnitude_spectrum[i, j] > 255:
#             print("fuck", magnitude_spectrum[i, j], i, j)
# print('end')
# img = Image.fromarray(np.uint8(magnitude_spectrum), 'L')
# img.save('./Image/_pysubsamplefft___.bmp')

# plt.subplot(121)
# plt.imshow(imga, cmap = 'gray')
# plt.title('Input Image')
# plt.xticks([])
# plt.yticks([])

# plt.subplot(122)
# plt.imshow(magnitude_spectrum, cmap = 'gray')
# plt.title('Magnitude Spectrum')
# plt.xticks([])
# plt.yticks([])
# plt.show()
