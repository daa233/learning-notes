# -*- coding:utf-8 -*-
# 题目描述
# 在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排
# 序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数
# 组和一个整数，判断数组中是否含有该整数。


# 从右上角开始查找，先检查搜索范围内每一行的最后一个元素
# 如果相等就返回 True；
# 如果小于 target，检查下一行；
# 如果大于 target，缩小搜索范围，将前面的行和当前遍历所在列从搜索范围内排除。
class Solution:
    # array 二维列表
    def Find(self, target, array):
        # write code here
        n = len(array)
        m = len(array[0])
        i, j = 0, m - 1
        while i < n and j >= 0:
            if array[i][j] == target:
                return True
            elif array[i][j] < target:
                i += 1
            else:
                j -= 1
        return False


# 暴力，遍历每一个元素
class Solution1:
    # array 二维列表
    def Find(self, target, array):
        # write code here
        for i in range(len(array)):
            for j in range(len(array[0])):
                if array[i][j] == target:
                    return True
        return False


if __name__ == '__main__':
    array = [[1, 3, 5, 8], [2, 4, 6, 9], [3, 8, 10, 11]]
    target = 6
    print(Solution().Find(target, array))
    array = [[1,2,8,9],[2,4,9,12],[4,7,10,13],[6,8,11,15]]
    target = 1
    print(Solution().Find(target, array))