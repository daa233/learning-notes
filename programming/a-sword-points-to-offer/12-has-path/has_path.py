# -*- coding:utf-8 -*-
# 题目描述
# 请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。
# 路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下
# 移动一个格子。如果一条路径经过了矩阵中的某一个格子，则该路径不能再进入该格子。
# 例如 [[a b c e],
#      [s f c s],
#      [a d e e]] 矩阵中包含一条字符串"bcced"的路径，但是矩阵中不包含"abcb"
# 路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进
# 入该格子。

# 输入 matrix 是一个一维的 char 型字符数组
class Solution:
    def hasPath(self, matrix, rows, cols, path):
        # write code here
        if not matrix:
            return False
        flags = [True for i in matrix]
        for i in range(rows):
            for j in range(cols):
                if self.check(matrix, flags, rows, cols, path, i, j, 0):
                    return True
        return False

    def check(self, matrix, flags, rows, cols, path, i, j, p):
        if flags[i*cols+j] and matrix[i*cols+j] == path[p]:
            # 字符串已经遍历完了
            if p == len(path) - 1:
                return True
            # 字符串还没有遍历完
            flags[i*cols+j] = False
            res1, res2, res3, res4 = False, False, False, False
            if i > 0 and flags[(i-1)*cols+j]:
                res1 = self.check(matrix, flags, rows, cols, path, i-1, j, p+1)
            if j > 0 and flags[i*cols+(j-1)]:
                res2 = self.check(matrix, flags, rows, cols, path, i, j-1, p+1)
            if i < rows - 1 and flags[(i+1)*cols+j]:
                res3 = self.check(matrix, flags, rows, cols, path, i+1, j, p+1)
            if j < cols - 1 and flags[i*cols+(j+1)]:
                res4 = self.check(matrix, flags, rows, cols, path, i, j+1, p+1)
            # 回溯到原来的状态
            flags[i*cols+j] = True
            return res1 or res2 or res3 or res4
        else:
            return False


if __name__ == "__main__":
    matrix = "ABCEHJIGSFCSLOPQADEEMNOEADIDEJFMVCEIFGGS"
    rows = 5
    cols = 8
    path = "SGGFIECVAASABCEHJIGQEM"
    print(Solution().hasPath(matrix, rows, cols, path))
    