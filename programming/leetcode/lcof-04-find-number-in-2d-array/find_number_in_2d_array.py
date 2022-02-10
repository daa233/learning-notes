# @problem: 剑指 Offer 04. 二维数组中的查找
# @file: search_a_2d_matrix.py
# @url: https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof
# @description:
#
# 在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个高效的函数，输入这样的一
# 个二维数组和一个整数，判断数组中是否含有该整数。
# 示例:
# 现有矩阵 matrix 如下：
#
# [
#   [1,   4,  7, 11, 15],
#   [2,   5,  8, 12, 19],
#   [3,   6,  9, 16, 22],
#   [10, 13, 14, 17, 24],
#   [18, 21, 23, 26, 30]
# ]
#
# 给定 target = 5，返回 true。
# 给定 target = 20，返回 false。
# 限制：
# 0 <= n <= 1000
# 0 <= m <= 1000
# 注意：本题与主站 240 题相同：https://leetcode-cn.com/problems/search-a-2d-matrix-
# ii/
#
# @author: Du Ang
# @date: Feb 10, 2022

from typing import List


class Solution1:
    """
    直接顺序遍历
    时间复杂度：O(nm)
    空间复杂度：O(1)
    """

    def findNumberIn2DArray(self, matrix: List[List[int]], target: int) -> bool:
        if not matrix:
            return False

        for i in range(len(matrix)):
            for j in range(len(matrix[0])):
                if matrix[i][j] == target:
                    return True

        return False


class Solution2:
    """
    分别扫描首行、首列、尾行、尾列，缩小遍历的区域，直至找到 target 或不满足条件。
    时间复杂度：O(n+m)
    空间复杂度：O(1)
    """

    def findNumberIn2DArray(self, matrix: List[List[int]], target: int) -> bool:
        if not matrix:
            return False

        top = 0
        left = 0
        right = len(matrix[0])
        bottom = len(matrix)
        while top < bottom and left < right:
            i = top
            for j in range(left, right):
                if matrix[i][j] == target:
                    return True
                elif matrix[i][j] > target:
                    right = j
                    break
            j = left
            for i in range(top, bottom):
                if matrix[i][j] == target:
                    return True
                elif matrix[i][j] > target:
                    bottom = i
                    break
            for j in range(left, right):
                if matrix[i][j] == target:
                    return True
                elif matrix[i][j] > target:
                    left = j
                    break
            j = right - 1
            for i in range(top, bottom):
                if matrix[i][j] == target:
                    return True
                elif matrix[i][j] > target:
                    top = i
                    break
            if matrix[top][left] > target or matrix[bottom - 1][right - 1] < target:
                return False

        return False


class Solution:
    """
    通过分析寻找规律，从数组右上角开始搜索，
    * 如果右上角元素等于 target，则返回 true，
    * 如果如果右上角元素大于 target，则剔除该列，继续遍历剩余部分，
    * 如果右上角元素小于 target，则剔除该行，继续遍历剩余部分，
    * 如果剩余部分为空，则返回 false。
    """

    def findNumberIn2DArray(self, matrix: List[List[int]], target: int) -> bool:
        if not matrix:
            return False

        i = 0
        j = len(matrix[0]) - 1
        while j >= 0 and i < len(matrix):
            if matrix[i][j] == target:
                return True
            elif matrix[i][j] > target:
                j -= 1
                continue
            elif matrix[i][j] < target:
                i += 1
                continue

        return False
