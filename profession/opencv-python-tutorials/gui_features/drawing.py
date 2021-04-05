import cv2
import numpy as np


# create a black image
img = np.zeros((512, 512, 3), dtype=np.uint8)

# draw a diagonal blue line with thickness of 5 px
cv2.line(img, (0, 0), (511, 511), color=(255, 0, 0), thickness=5)

# draw a rectangle with top-left corner and bottom-right corner specified
cv2.rectangle(img, (384, 0), (512, 128), color=(0, 255, 0), thickness=3)

# Draw a circle with center coordinates and radius specified.
# thickness = -1 will filled the shape
cv2.circle(img, (447, 63), 63, color=(0, 0, 255), thickness=-1)

# Draw a ellipse with center, axes and three angles specified.
# angle is the angle of rotation of ellipse in clockwise direction.
# startAngle and endAngle denotes the starting and ending of ellipse arc measured in clockwise
# direction from major axis. i.e. giving values 0 and 360 gives the full ellipse.
cv2.ellipse(img, center=(256, 256), axes=(100, 50), angle=0, startAngle=0, endAngle=180, color=255, thickness=-1)

# Draw polygon with a series of coordinates of vertices speficied.
pts = np.array([[10, 5], [20, 30], [70, 20], [50, 10]], np.int32)
pts = pts.reshape((-1, 1, 2))
cv2.polylines(img, [pts, pts + 20], isClosed=True, color=(0, 255, 255))

# Adding text to images
# The position is the bottom-left corner where data starts.
font = cv2.FONT_HERSHEY_SIMPLEX
cv2.putText(img, "OpenCV", (10, 480), font, fontScale=4, color=(255, 255, 255), thickness=2, lineType=cv2.LINE_AA)

cv2.imshow("image", img)
cv2.waitKey(0)

cv2.destroyAllWindows()
