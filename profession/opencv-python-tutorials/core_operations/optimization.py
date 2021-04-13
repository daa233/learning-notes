import cv2
import time
from IPython import embed


img1 = cv2.imread(cv2.samples.findFile("messi5.jpg"))

e1 = cv2.getTickCount()
for i in range(5, 49, 2):
    res = cv2.medianBlur(img1.copy(), i)
e2 = cv2.getTickCount()

t1 = time.time()
for i in range(5, 49, 2):
    res = cv2.medianBlur(img1.copy(), i)
t2 = time.time()


te = (e2 - e1) / cv2.getTickFrequency()
t = t2 - t1
print("time (cv2) = {}".format(te))
print("time (time) = {}".format(t))

cv2.imshow("img1", res)
cv2.waitKey(0)
cv2.destroyAllWindows()

img = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)

embed()

# In [1]: x = 5

# In [2]: %timeit y = x ** 2
# 214 ns ± 3.07 ns per loop (mean ± std. dev. of 7 runs, 1000000 loops each)

# In [3]: %timeit y = x * x
# 39.6 ns ± 0.356 ns per loop (mean ± std. dev. of 7 runs, 10000000 loops each)

# In [4]: import numpy as np

# In [5]: z = np.uint8([5])

# In [6]: %timeit y = z * z
# 434 ns ± 3.91 ns per loop (mean ± std. dev. of 7 runs, 1000000 loops each)

# In [7]: %timeit y = np.square(z)
# 456 ns ± 3.97 ns per loop (mean ± std. dev. of 7 runs, 1000000 loops each)

# In [8]: %timeit z = cv2.countNonZero(img)
# 17.6 µs ± 873 ns per loop (mean ± std. dev. of 7 runs, 100000 loops each)

# In [9]: %timeit z = np.count_nonzero(img)
# 300 µs ± 2.05 µs per loop (mean ± std. dev. of 7 runs, 1000 loops each)

# Additional Resources
# - [Python Optimization Techniques](http://wiki.python.org/moin/PythonSpeed/PerformanceTips)
# - Scipy Lecture Notes - [Advanced Numpy](http://scipy-lectures.github.io/advanced/advanced_numpy/index.html#advanced-numpy)
# - [Timing and Profiling in IPython](http://pynash.org/2013/03/06/timing-and-profiling/)
