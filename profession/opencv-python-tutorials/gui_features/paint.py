import cv2
import numpy as np


def get_init_canvas(shape):
    img = np.ones(shape, dtype=np.uint8) * 255
    return img


canvas_shape = (512, 512, 3)
img = get_init_canvas(canvas_shape)
window_name = "paint"
cv2.namedWindow(window_name)

drawing = False  # true if the mouse is pressed
mode = True  # if True, draw rectangle. Press 'm' to toggle to curve
ix, iy = -1, -1
color = (0, 0, 0)
brush_size = 5
min_brush_size = 1
max_brush_size = 100


def draw(event, x, y, flags, param):
    global img, drawing, mode, ix, iy, color, brush_size

    if event == cv2.EVENT_LBUTTONDOWN:
        drawing = True
        cv2.circle(img, (x, y), brush_size // 2, color, -1)
        ix, iy = x, y
    elif event == cv2.EVENT_MOUSEMOVE:
        if drawing:
            cv2.line(img, (ix, iy), (x, y), color, brush_size, lineType=cv2.LINE_AA)
            ix, iy = x, y
    elif event == cv2.EVENT_LBUTTONUP:
        drawing = False


def change_color(x):
    global color

    r = cv2.getTrackbarPos("R", window_name)
    g = cv2.getTrackbarPos("G", window_name)
    b = cv2.getTrackbarPos("B", window_name)
    color = (b, g, r)


def change_brush_size(x):
    global brush_size

    brush_trackbar_value = cv2.getTrackbarPos("Brush Size", window_name)

    if brush_trackbar_value <= 0:
        brush_size = 1
    else:
        brush_size = brush_trackbar_value


# set mouse callback to draw
cv2.setMouseCallback(window_name, draw)

# create trackbars for color change
cv2.createTrackbar("R", window_name, color[2], 255, change_color)
cv2.createTrackbar("G", window_name, color[1], 255, change_color)
cv2.createTrackbar("B", window_name, color[0], 255, change_color)

# create trackbar for brush radius change
cv2.createTrackbar("Brush Size", window_name, brush_size, max_brush_size, change_brush_size)

while True:
    cv2.imshow(window_name, img)
    k = cv2.waitKey(1) & 0xFF
    if k == ord("m"):
        # press 'm' to toggle mode
        mode = not mode
    if k == ord("r"):
        # press 'r' to reset the canvas
        img = get_init_canvas(canvas_shape)
    if k == ord("+"):
        # press '+' to increase the brush size
        brush_size += 1
        brush_size = min(brush_size, max_brush_size)
        cv2.setTrackbarPos("Brush Size", window_name, brush_size)
    if k == ord("-"):
        # press '-' to increase the brush size
        brush_size -= 1
        brush_size = max(brush_size, min_brush_size)
        cv2.setTrackbarPos("Brush Size", window_name, brush_size)
    elif k == 27:
        # press 'Esc' to quit the demo
        break

cv2.destroyAllWindows()
