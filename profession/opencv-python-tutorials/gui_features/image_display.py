import cv2
import sys


# NOTE: samples submodule is available in opencv-python version 4.0.0.21
# The "starry_night.jpg" can be downloaded from https://github.com/opencv/opencv/blob/master/samples/data/starry_night.jpg
img = cv2.imread(cv2.samples.findFile("starry_night.jpg"))

if img is None:
    sys.exit("Could not read the image.")

cv2.imshow("Display window", img)
k = cv2.waitKey(0)

if k == ord("s"):
    cv2.imwrite("starry_night.png", img)

cv2.destroyAllWindows()
