import cv2
import numpy as np


# create a black image, a window and bind the function to the window
img = np.zeros((512, 512, 3), np.uint8)
cv2.namedWindow("image")

drawing = False  # true if the mouse is pressed
mode = True  # if True, draw rectangle. Press 'm' to toggle to curve
ix, iy = -1, -1


# simple mouse callback function
def draw_circle(event, x, y, flags, param):
    global img

    if event == cv2.EVENT_LBUTTONUP:
        cv2.circle(img, (x, y), 100, (255, 0, 0), -1)


def draw_rectangle_or_circle(event, x, y, flags, param):
    global img, drawing, mode, ix, iy

    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        ix, iy = x, y

    elif event == cv2.EVENT_MOUSEMOVE:
        if drawing:
            if mode:
                cv2.rectangle(img, (ix, iy), (x, y), (0, 255, 0), -1)
            else:
                cv2.circle(img, (x, y), 5, (0, 0, 255), -1)

    elif event == cv2.EVENT_LBUTTONUP:
        drawing = False
        if mode:
            cv2.rectangle(img, (ix, iy), (x, y), (0, 255, 0), -1)
        else:
            cv2.circle(img, (x, y), 5, (0, 0, 255), -1)


# # simple draw circle demo
# cv2.setMouseCallback("image", draw_circle)

# while True:
#     cv2.imshow("image", img)
#     if cv2.waitKey(20) & 0xFF == 27:
#         break


# draw rectangle or circle demo
cv2.setMouseCallback("image", draw_rectangle_or_circle)

while True:
    cv2.imshow("image", img)
    k = cv2.waitKey(1) & 0xFF
    if k == ord("m"):
        # press 'm' to toggle mode
        mode = not mode
    elif k == 27:
        # press 'Esc' to quit the demo
        break

cv2.destroyAllWindows()
