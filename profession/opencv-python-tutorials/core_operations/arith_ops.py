import cv2
import numpy as np


# Image Addition
x = np.uint8([250])
y = np.uint8([10])

# OpenCV addition, a saturated operation
print("cv2.add(x, y) = {}".format(cv2.add(x, y)))

# Numpy addition, a modulo operation
print("x + y = {}".format(x + y))

# Image Blending
# dst = \alpha * img1 + \beta * img2 + \gamma
img1 = cv2.imread(cv2.samples.findFile("ml.png"))
img2 = cv2.imread(cv2.samples.findFile("opencv-logo-white.png"))

# the added images should have the same shape
height, width = img1.shape[:2]
img2 = cv2.resize(img2, (width, height))

alpha = 1
step = 0.02
while alpha > 0:
    dst = cv2.addWeighted(img1, alpha, img2, 1 - alpha, 0)
    cv2.imshow("dst", dst)
    cv2.waitKey(100)
    alpha -= step

cv2.destroyAllWindows()

# Bitwise Operations
# load two images
img1 = cv2.imread(cv2.samples.findFile("messi5.jpg"))
img2 = cv2.imread(cv2.samples.findFile("opencv-logo-white.png"))

# put the logo on the messi5's top-left corner, create a ROI
rows, cols, channels = img2.shape
roi = img1[0:rows, 0:cols]

# create a mask of logo and also create its inverse mask
img2gray = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
ret, mask = cv2.threshold(img2gray, 10, 255, cv2.THRESH_BINARY)
mask_inv = cv2.bitwise_not(mask)

# black-out the area of logo in ROI
img1_bg = cv2.bitwise_and(roi, roi, mask=mask_inv)

# take only region of logo from logo image
img2_fg = cv2.bitwise_and(img2, img2, mask=mask)

# put logo in ROI and modify the main image
dst = cv2.add(img1_bg, img2_fg)
img1[0:rows, 0:cols] = dst

cv2.imshow("res", img1)
cv2.waitKey(0)
cv2.destroyAllWindows()
