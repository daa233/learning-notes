import cv2
import numpy as np
import matplotlib.pyplot as plt


def show_res(res, window_name="res"):
    cv2.imshow(window_name, res)
    cv2.waitKey(0)


def show_compare_res(input, res):
    plt.subplot(121), plt.imshow(img), plt.title("Input")
    plt.subplot(122), plt.imshow(res), plt.title("Output")
    plt.show()


img = cv2.imread(cv2.samples.findFile("messi5.jpg"))
height, width = img.shape[:2]


# Scaling

# specify the scale factor
res = cv2.resize(img, None, fx=2, fy=2, interpolation=cv2.INTER_CUBIC)

# or specify the target size
res = cv2.resize(img, (width * 2, height * 2), interpolation=cv2.INTER_CUBIC)

cv2.imshow("img", img)
show_res(res)


# Translation, M = [[1, 0, t_x], [0, 1, t_y]]
M = np.float32([[1, 0, 100], [0, 1, 50]])
res = cv2.warpAffine(img, M, (width, height))
show_res(res)

# Rotation (simple), M = [[cos{\theta}, -sin{\theta}, 0], [sin{\theta}, cos{\theta}, 0]]
# rotate pi/2 degree according to counter-clockwise
theta = np.pi / 2.0
# the rotation center is (0, 0), so we need translation to see it
M = np.float32([[np.cos(theta), -np.sin(theta), height], [np.sin(theta), np.cos(theta), 0]])
res = cv2.warpAffine(img, M, (width, height))
show_res(res)

# Rotation with adjustable center and scaling
M = cv2.getRotationMatrix2D(((width - 1) / 2.0, (height - 1) / 2), 90, 1)
res = cv2.warpAffine(img, M, (width, height))
show_res(res)

# Affine Transformation
img = cv2.imread(cv2.samples.findFile("chessboard.png"))
height, width = img.shape[:2]

# need three points to create a 2x3 warp affine transformation matrix
pts1 = np.float32([[50, 50], [200, 50], [50, 200]])
pts2 = np.float32([[10, 100], [200, 50], [100, 250]])
M = cv2.getAffineTransform(pts1, pts2)

res = cv2.warpAffine(img, M, (width, height))
show_compare_res(img, res)

# Perspective Transformation
img = cv2.imread(cv2.samples.findFile("sudoku.png"))
height, width = img.shape[:2]

# need four points to create a 3x3 perspective transformation matrix
pts1 = np.float32([[75, 86], [487, 70], [35, 516], [516, 522]])
pts2 = np.float32([[0, 0], [300, 0], [0, 300], [300, 300]])
# NOTE: We may use this operation to crop and resize the ROI
M = cv2.getPerspectiveTransform(pts1, pts2)

res = cv2.warpPerspective(img, M, (300, 300))
show_compare_res(img, res)

# all finished, release resources
cv2.destroyAllWindows()
