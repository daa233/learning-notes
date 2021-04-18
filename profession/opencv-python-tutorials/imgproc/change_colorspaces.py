import cv2
import numpy as np


flags = [i for i in dir(cv2) if i.startswith("COLOR_")]

cap = cv2.VideoCapture(0)

while True:

    # take each frame
    _, frame = cap.read()

    # convert BGR to HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # define the range of blue color in HSV
    lower_blue = np.array([85, 50, 50])
    upper_blue = np.array([130, 255, 255])

    # define the range of red color in HSV, there are two segments of red in hue
    lower_red0 = np.array([0, 100, 100])
    upper_red0 = np.array([5, 255, 255])
    lower_red1 = np.array([160, 50, 50])
    upper_red1 = np.array([179, 255, 255])

    # threshold the HSV image to get only blue colors
    blue_mask = cv2.inRange(hsv, lower_blue, upper_blue)

    # threshold the HSV image to get only red colors
    red_mask0 = cv2.inRange(hsv, lower_red0, upper_red0)
    red_mask1 = cv2.inRange(hsv, lower_red1, upper_red1)
    red_mask = cv2.bitwise_or(red_mask0, red_mask1)

    # track blue or red objects
    mask = cv2.bitwise_or(blue_mask, red_mask)

    # bitwise-and mask and original image
    res = cv2.bitwise_and(frame, frame, mask=mask)

    cv2.imshow("frame", frame)
    cv2.imshow("mask", mask)
    cv2.imshow("res", res)

    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        # press 'Esc' to quit
        break

cv2.destroyAllWindows()
