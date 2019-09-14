# -*- coding:utf-8 -*-
# 题目描述
# 我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2*1的小矩形无重叠
# 地覆盖一个2*n的大矩形，总共有多少种方法？

# 第一块砖有两种摆放方式
# （1）横着摆：剩下 f(n-2) 种摆法
# （2）竖着摆：剩下 f(n-1) 种摆法
class Solution:
    def rectCover(self, number):
        # write code here
        if number <= 1:
            return number
        f0 = 1
        f1 = 1
        for i in range(2, number+1):
            f2 = f1 + f0
            f0 = f1
            f1 = f2
        return f2
