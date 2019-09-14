# -*- coding:utf-8 -*-
# 题目描述
# 一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。
# 求该青蛙跳上一个n级的台阶总共有多少种跳法。

# 思路1：通过递推公式推导
# f(0) = f(1) = 1
# f(2) = f(1) + f(0) = 2
# ...
# f(n) = f(n-1) + f(n-2) + ... + f(1) + f(0) = 2 * f(n-1)
# 思路2：
# （1）走到第 n-1 个台阶有 f(n-1) 种走法，从第 n-1 个台阶走到第 n 个台阶要再
# 走1步，这样有 f(n-1) 种走法；
# （2）走到第 n-1 个台阶之前，也可以不走第 n-1 个台阶，直接走到第 n 个台阶，这
# 样又有 f(n-1) 种走法。
# 综合起来，f(n) = f(n-1) + f(n-1) = 2 * f(n) 种走法。
class Solution:
    def jumpFloorII(self, number):
        # write code here
        if number <= 1:
            return number
        f = 1
        for i in range(2, number+1):
            f = f * 2
        return f
