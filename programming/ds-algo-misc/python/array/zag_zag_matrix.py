# Print matrix in zag-zag fashion
# https://www.geeksforgeeks.org/print-matrix-zag-zag-fashion/
# Input:
# 1 2 3
# 4 5 6
# 7 8 9
# Output: 
# 1 2 4 7 5 3 6 8 9

def get_step(n, m, i, j, flag):
    if flag:
        # from bottom-left to top-right
        if i > 0 and j < m - 1:
            return i-1, j+1, flag
        elif i == 0 and j < m - 1:
            return i, j+1, not flag
        else:
            return i+1, j, not flag
    else:
        # from top-right to bottom-left
        if i < n - 1 and j > 0:
            return i+1, j-1, flag
        elif i < n - 1 and j == 0:
            return i+1, j, not flag
        else:
            return i, j+1, not flag

def zag_zag_matrix(array):
    n = len(array)
    m = len(array[0])
    i, j = 0, 0
    flag = True
    res = [array[0][0]]
    while True:
        i, j, flag = get_step(n, m, i, j, flag)
        if i > n - 1 or j > m - 1:
            break
        res.append(array[i][j])
    return res

# test
def test_zag_zag_matrix():
    array = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    print(zag_zag_matrix(array))

    import numpy as np
    print(zag_zag_matrix(np.arange(24).reshape(4, 6)))

test_zag_zag_matrix()

# 变式：蛇形打印矩阵
# 输入n，m（正整数）分别表示矩阵的行数和列数，输出如下形式的矩阵：
# [[ 0,  2,  3,  9, 10],
#  [ 1,  4,  8, 11, 16],
#  [ 5,  7, 12, 15, 17],
#  [ 6, 13, 14, 18, 19]]
def zag_zag_matrix_v2(n, m):
    res = [[-1 for j in range(m)] for i in range(n)]
    i, j = 0, 0
    flag = False
    count = 0
    res[0][0] = count
    while True:
        i, j, flag = get_step(n, m, i, j, flag)
        count += 1
        if i > n - 1 or j > m - 1:
            break
        res[i][j] = count
    return res

def test_print(res):
    for line in res:
        print(line)

def test_zag_zag_matrix_v2():
    res = zag_zag_matrix_v2(4, 5)
    test_print(res)
    res = zag_zag_matrix_v2(1, 5)
    test_print(res)
    res = zag_zag_matrix_v2(3, 1)
    test_print(res)

test_zag_zag_matrix_v2()
