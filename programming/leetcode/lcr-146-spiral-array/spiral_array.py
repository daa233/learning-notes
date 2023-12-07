# @problem: LCR 146. 螺旋遍历二维数组
# @file: spiral_array.py
# @url: https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof
# @description:
#
# 给定一个二维数组 array，请返回「螺旋遍历」该数组的结果。
# 螺旋遍历：从左上角开始，按照 向右、向下、向左、向上 的顺序 依次 提取元素，然后再进入内部一层重复相同的步骤，直到提取完所有元素。
# 示例 1：
#
# 输入：array = [[1,2,3],[8,9,4],[7,6,5]]
# 输出：[1,2,3,4,5,6,7,8,9]
#
# 示例 2：
#
# 输入：array  = [[1,2,3,4],[12,13,14,5],[11,16,15,6],[10,9,8,7]]
# 输出：[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
#
# 限制：
#
# 0 <= array.length <= 100
# 0 <= array[i].length <= 100
#
# 注意：本题与主站 54 题相同：https://leetcode-cn.com/problems/spiral-matrix/
#
# @author: Du Ang
# @date: Dec 05, 2023

from typing import List, Tuple


class Solution:

    def spiralArray(self, array: List[List[int]]) -> List[int]:
        if not array:
            return []
        elif not array[0]:
            return []

        min_i, max_i = 0, len(array) - 1
        min_j, max_j = 0, len(array[0]) - 1
        i, j = 0, 0
        di, dj = 0, 1
        result = []
        while min_i <= max_i and min_j <= max_j:
            result.append(array[i][j])
            i += di
            j += dj

            if i < min_i:
                i = min_i
                j += 1
                min_j += 1
                di = 0
                dj = 1
            elif i > max_i:
                i = max_i
                j -= 1
                max_j -= 1
                di = 0
                dj = -1
            elif j < min_j:
                i -= 1
                j = min_j
                max_i -= 1
                di = -1
                dj = 0
            elif j > max_j:
                i += 1
                j = max_j
                min_i += 1
                di = 1
                dj = 0

        return result


if __name__ == "__main__":
    sln = Solution()
    print(sln.spiralArray([[1, 2, 3], [8, 9, 4], [7, 6, 5]]))
