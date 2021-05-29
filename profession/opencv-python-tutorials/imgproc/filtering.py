import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt


img = cv.imread(cv.samples.findFile("opencv-logo-white.png"), cv.IMREAD_COLOR)


# 2D Convolution (Image Filtering)
kernel = np.ones((5, 5), np.float32) / 25
e1 = cv.getTickCount()
dst = cv.filter2D(img, -1, kernel)
e2 = cv.getTickCount()
t1 = (e2 - e1) / cv.getTickFrequency()


def custom_filter2D(img, kernel):
    ih, iw, ic = img.shape
    kh, kw = kernel.shape
    rows = ih + kh
    cols = iw + kw

    border_top = kh // 2
    border_bottom = rows - ih - border_top
    border_left = kw // 2
    border_right = cols - iw - border_left

    src = cv.copyMakeBorder(img, border_top, border_bottom, border_left, border_right, cv.BORDER_DEFAULT)

    assert src.shape[:2] == (rows, cols), "src.shape = {}, while (rows, cols) = {}".format(src.shape[:2], (rows, cols))

    dst = np.zeros((img.shape), img.dtype)

    for i in range(ih):
        for j in range(iw):
            for k in range(ic):
                dst[i, j, k] = (np.sum(src[i : i + kh, j : j + kw, k] * kernel)).astype(np.uint8)

    return dst


e1 = cv.getTickCount()
custom_dst = custom_filter2D(img, kernel)
e2 = cv.getTickCount()
t2 = (e2 - e1) / cv.getTickFrequency()
print("t1 = {}, t2 = {}".format(t1, t2))

plt.subplot(131), plt.imshow(cv.cvtColor(img, cv.COLOR_BGR2RGB)), plt.title("Original")
plt.xticks([]), plt.yticks([])
plt.subplot(132), plt.imshow(cv.cvtColor(dst, cv.COLOR_BGR2RGB)), plt.title("Averaging")
plt.xticks([]), plt.yticks([])
plt.subplot(133), plt.imshow(cv.cvtColor(custom_dst, cv.COLOR_BGR2RGB)), plt.title("Custom Averaging")
plt.xticks([]), plt.yticks([])
plt.tight_layout()
plt.show()


def add_noise(image, noise_type=""):
    """
    Add noise to the given image.
    See https://stackoverflow.com/questions/22937589/how-to-add-noise-gaussian-salt-and-pepper-etc-to-image-in-python-with-opencv
    """
    image = image.astype(np.float32)
    if noise_type == "gauss":
        row, col, ch = image.shape
        mean = 0
        var = 0.1
        sigma = var ** 0.5
        gauss = np.random.normal(mean, sigma, (row, col, ch))
        gauss = gauss.reshape(row, col, ch)
        noisy = image + gauss
        return noisy.astype(np.uint8)
    elif noise_type == "s&p":
        row, col, ch = image.shape
        s_vs_p = 0.5
        amount = 0.1
        out = np.copy(image)
        # Salt mode
        num_salt = np.ceil(amount * image.size * s_vs_p)
        coords = [np.random.randint(0, i - 1, int(num_salt)) for i in image.shape]
        out[coords] = 1
        # Pepper mode
        num_pepper = np.ceil(amount * image.size * (1.0 - s_vs_p))
        coords = [np.random.randint(0, i - 1, int(num_pepper)) for i in image.shape]
        out[coords] = 0
        return out.astype(np.uint8)
    elif noise_type == "poisson":
        vals = len(np.unique(image))
        vals = 2 ** np.ceil(np.log2(vals))
        noisy = np.random.poisson(image * vals) / float(vals)
        return noisy.astype(np.uint8)
    elif noise_type == "speckle":
        row, col, ch = image.shape
        gauss = np.random.randn(row, col, ch)
        gauss = gauss.reshape(row, col, ch)
        noisy = image + image * gauss
        return noisy.astype(np.uint8)
    else:
        raise NotImplementedError("noise type {} not supported!".format(noise_type))


# Image Blurring (Image Smoothing)

noise_type_list = ["", "gauss", "s&p", "poisson", "speckle"]
for i, noise_type in enumerate(noise_type_list, start=1):
    if noise_type == "":
        src_title = "Original"
        src_img = img
    else:
        src_title = noise_type
        src_img = add_noise(img, noise_type=noise_type)

    averaging_blur = cv.blur(src_img, (5, 5))
    gassian_blur = cv.GaussianBlur(src_img, (5, 5), 0)
    median_blur = cv.medianBlur(src_img, 5)
    bilateral_filtering = cv.bilateralFilter(src_img, 9, 75, 75)

    plt.subplot(1, 5, 1), plt.imshow(cv.cvtColor(src_img, cv.COLOR_BGR2RGB)), plt.title(src_title)
    plt.xticks([]), plt.yticks([])
    plt.subplot(1, 5, 2), plt.imshow(cv.cvtColor(averaging_blur, cv.COLOR_BGR2RGB)), plt.title("Averaging Blurred")
    plt.xticks([]), plt.yticks([])
    plt.subplot(1, 5, 3), plt.imshow(cv.cvtColor(gassian_blur, cv.COLOR_BGR2RGB)), plt.title("Gaussian Blurred")
    plt.xticks([]), plt.yticks([])
    plt.subplot(1, 5, 4), plt.imshow(cv.cvtColor(median_blur, cv.COLOR_BGR2RGB)), plt.title("Median Blurred")
    plt.xticks([]), plt.yticks([])
    plt.subplot(1, 5, 5), plt.imshow(cv.cvtColor(bilateral_filtering, cv.COLOR_BGR2RGB)), plt.title(
        "Bilateral Filtering"
    )
    plt.xticks([]), plt.yticks([])
    plt.tight_layout()
    plt.show()
