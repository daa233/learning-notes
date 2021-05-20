import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt


img = cv.imread(cv.samples.findFile("gradient.png", 0))

# Simple Thresholding
# If the pixel value is smaller than the threshold, it is set to 0, otherwise it is set to a
# maximum value.
ret, thresh1 = cv.threshold(img, 127, 255, cv.THRESH_BINARY)
ret, thresh2 = cv.threshold(img, 127, 255, cv.THRESH_BINARY_INV)
ret, thresh3 = cv.threshold(img, 127, 255, cv.THRESH_TRUNC)
ret, thresh4 = cv.threshold(img, 127, 255, cv.THRESH_TOZERO)
ret, thresh5 = cv.threshold(img, 127, 255, cv.THRESH_TOZERO_INV)

titles = ["Original Image", "BINARY", "BINARY_INV", "TRUNC", "TOZERO", "TOZERO_INV"]
images = [img, thresh1, thresh2, thresh3, thresh4, thresh5]

for i in range(6):
    plt.subplot(2, 3, i + 1), plt.imshow(images[i], "gray", vmin=0, vmax=255)
    plt.title(titles[i])
    plt.xticks([]), plt.yticks([])

plt.show()

# Adpative Thresholding
# The algorithm determines the threshold for a pixel based on a small region around it.
img = cv.imread(cv.samples.findFile("sudoku.png"), 0)
img = cv.medianBlur(img, 5)

ret, th1 = cv.threshold(img, 127, 255, cv.THRESH_BINARY)
th2 = cv.adaptiveThreshold(img, 255, cv.ADAPTIVE_THRESH_MEAN_C, cv.THRESH_BINARY, 11, 2)
th3 = cv.adaptiveThreshold(img, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 11, 2)
titles = [
    "Original Image",
    "Global Thresholding (v = 127)",
    "Adaptive Mean Thresholding",
    "Adaptive Gaussian Thresholding",
]
images = [img, th1, th2, th3]

for i in range(4):
    plt.subplot(2, 2, i + 1), plt.imshow(images[i], "gray")
    plt.title(titles[i])
    plt.xticks([]), plt.yticks([])

plt.show()

# Otsu's Binarization for Bimodal Images
# Otsu's method determines an optimal global threshold value from the image histogram.
img = np.ones((300, 400)) * 60
img[100:200, 100:300] = 150

# generate Gaussian noise
mean = 0
var = 0.35
sigma = var ** 0.5
noise = np.random.normal(mean, sigma, (300, 400)) * (2 * np.pi * var) * 25

# add the noise to the image
img += noise
mask = cv.inRange(img, 0, 255)
img = cv.bitwise_and(img, img, mask=mask)
img = img.astype(np.uint8)

# global thresholding
ret1, th1 = cv.threshold(img, 127, 255, cv.THRESH_BINARY)

# Otsu's thresholding
ret2, th2 = cv.threshold(img, 0, 255, cv.THRESH_BINARY + cv.THRESH_OTSU)

# Otsu's thresholding after Gaussian filtering
blur = cv.GaussianBlur(img, (5, 5), 0)
# blur = img
ret3, th3 = cv.threshold(blur, 0, 255, cv.THRESH_BINARY + cv.THRESH_OTSU)
# plot all the images and their histograms
images = [img, 0, th1, img, 0, th2, blur, 0, th3]
titles = [
    "Original Noisy Image",
    "Histogram",
    "Global Thresholding (v=127)",
    "Original Noisy Image",
    "Histogram",
    "Otsu's Thresholding",
    "Gaussian filtered Image",
    "Histogram",
    "Otsu's Thresholding",
]

for i in range(3):
    plt.subplot(3, 3, i * 3 + 1), plt.imshow(images[i * 3], "gray")
    plt.title(titles[i * 3]), plt.xticks([]), plt.yticks([])
    plt.subplot(3, 3, i * 3 + 2), plt.hist(images[i * 3].ravel(), 256)
    plt.title(titles[i * 3 + 1]), plt.xticks([]), plt.yticks([])
    plt.subplot(3, 3, i * 3 + 3), plt.imshow(images[i * 3 + 2], "gray")
    plt.title(titles[i * 3 + 2]), plt.xticks([]), plt.yticks([])


plt.tight_layout()
plt.show()
