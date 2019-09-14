# -*- coding:utf-8 -*-
# 题目描述
# 一只青蛙一次可以跳上1级台阶，也可以跳上2级。
# 求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。

# 第一次有两种选择：
# （1）跳1阶：还有 f(n-1) 种跳法
# （2）跳2阶：还有 f(n-2) 种跳法
class Solution:
    def jumpFloor(self, number):
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
