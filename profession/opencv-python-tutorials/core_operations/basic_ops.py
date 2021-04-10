import cv2
import numpy as np
from matplotlib import pyplot as plt


# NOTE: samples submodule is available in opencv-python version 4.0.0.21
# The "starry_night.jpg" can be downloaded from https://github.com/opencv/opencv/blob/master/samples/data/starry_night.jpg
img = cv2.imread(cv2.samples.findFile("starry_night.jpg"))

# Accessing and Modifying pixel values

# access a pixel value
px = img[100, 100]
print("img[100, 100] = {}".format(px))

# access only blue pixel
blue = img[100, 100, 0]
print("img[100, 100, 0] = {}".format(blue))

# modify the pixel value
img[100, 100] = [255, 255, 255]
print("img[100, 100] = {}".format(img[100, 100]))

# it is better to use 'array.item()' or 'array.itemset()' for individual pixel
print("img.item(10, 10, 2) = {}".format(img.item(10, 10, 2)))
img.itemset((10, 10, 2), 100)
print("img.item(10, 10, 2) = {}".format(img.item(10, 10, 2)))

# Accessing Image Properties
print("img.shape = {}".format(img.shape))
print("img.size = {}".format(img.size))
print("img.dtype = {}".format(img.dtype))

# Image ROI
cv2.imshow("original", img)
cv2.waitKey(0)

moon = img[20:180, 580:740]
cv2.imshow("moon", moon)
cv2.waitKey(0)


# Splitting and Merging Image Channels
b, g, r = cv2.split(img)  # a time-consuming operation, use numpy instead
cv2.imshow("b", b)
cv2.waitKey(0)

cv2.imshow("g", g)
cv2.waitKey(0)

cv2.imshow("r", r)
cv2.waitKey(0)

img_merge = cv2.merge((b, g, r))

assert (img == img_merge).all()

# set all the red pixels to zero
img_vis = img.copy()
img_vis[:, :, 2] = 0
cv2.imshow("image with zero red", img_vis)
cv2.waitKey(0)

cv2.destroyAllWindows()

# Making Borders for Images (Padding)
BLUE = [255, 0, 0]
opencv_logo_img = cv2.imread(cv2.samples.findFile("opencv-logo-white.png"), cv2.IMREAD_COLOR)
replicate = cv2.copyMakeBorder(opencv_logo_img, 10, 10, 10, 10, cv2.BORDER_REPLICATE)
# > With BORDER_REFLECT also the outer-most border is reflected (copied), while with BORDER_REFLECT_101, the outer-most border is not part of the border.
# Reference: https://answers.opencv.org/question/50706/border_reflect-vs-border_reflect_101/
reflect = cv2.copyMakeBorder(opencv_logo_img, 10, 10, 10, 10, cv2.BORDER_REFLECT)
reflect101 = cv2.copyMakeBorder(opencv_logo_img, 10, 10, 10, 10, cv2.BORDER_REFLECT101)
wrap = cv2.copyMakeBorder(opencv_logo_img, 10, 10, 10, 10, cv2.BORDER_WRAP)
constant = cv2.copyMakeBorder(opencv_logo_img, 10, 10, 10, 10, cv2.BORDER_CONSTANT, value=BLUE)

plt.subplot(231), plt.imshow(opencv_logo_img[:, :, ::-1]), plt.title("ORIGINAL")
plt.subplot(232), plt.imshow(replicate[:, :, ::-1]), plt.title("REPLICATE")
plt.subplot(233), plt.imshow(reflect[:, :, ::-1]), plt.title("REFLECT")
plt.subplot(234), plt.imshow(reflect101[:, :, ::-1]), plt.title("REFLECT_101")
plt.subplot(235), plt.imshow(wrap[:, :, ::-1]), plt.title("WRAP")
plt.subplot(236), plt.imshow(constant[:, :, ::-1]), plt.title("CONSTANT")
plt.tight_layout()

plt.show()
