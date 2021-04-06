import cv2
import numpy as np


# create a black image
img = np.ones((620, 512, 3), dtype=np.uint8) * 255

r_center = (260, 130)
g_center = (140, 340)
b_center = (370, 340)
thickness = 60

# draw big circles
cv2.circle(img, r_center, radius=100, color=(0, 0, 255), thickness=-1)
cv2.circle(img, g_center, radius=100, color=(0, 255, 0), thickness=-1)
cv2.circle(img, b_center, radius=100, color=(255, 0, 0), thickness=-1)

# draw inner small white circles
cv2.circle(img, r_center, radius=40, color=(255, 255, 255), thickness=-1)
cv2.circle(img, g_center, radius=40, color=(255, 255, 255), thickness=-1)
cv2.circle(img, b_center, radius=40, color=(255, 255, 255), thickness=-1)

# draw the fan shape
cv2.ellipse(
    img, center=r_center, axes=(100, 100), angle=0, startAngle=60, endAngle=120, color=(255, 255, 255), thickness=-1
)
cv2.ellipse(
    img, center=g_center, axes=(100, 100), angle=0, startAngle=300, endAngle=360, color=(255, 255, 255), thickness=-1
)
cv2.ellipse(
    img, center=b_center, axes=(100, 100), angle=0, startAngle=240, endAngle=300, color=(255, 255, 255), thickness=-1
)

# draw the text
cv2.putText(
    img,
    text="OpenCV",
    org=(50, 560),
    fontFace=cv2.FONT_HERSHEY_SIMPLEX,
    fontScale=3.5,
    color=(0, 0, 0),
    thickness=12,
    lineType=cv2.LINE_AA,
)

cv2.imshow("image", img)
cv2.waitKey(0)
