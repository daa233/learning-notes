# -*- coding:utf-8 -*-
# 题目描述
# 大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项
# （从0开始，第0项为0，n<=39）。

from time import time


# 实用解法，O(n)
class Solution:
    def Fibonacci(self, n):
        # write code here
        if n <= 1:
            return n
        f0 = 0
        f1 = 1
        for i in range(2, n+1):
            f2 = f1 + f0
            f0 = f1
            f1 = f2
        return f2


# 利用数学公式，时间常数较大，不够实用，O(logn)
# [[f(n), f(n-1)], [f(n-1), f(n-2)]] = [[1, 1], [1, 0]]^(n-1)
class Solution2:
    def Fibonacci(self, n):
        # write code here
        if n <= 1:
            return n
        res = [[1, 1], [1, 0]]
        for i in range(n-2):
            res = self.matmul_one(res)
        return res[0][0]

    def matmul_one(self, res):
        # optimized according to [[1, 1], [1, 0]]
        res[1][0] = res[0][0]
        res[1][1] = res[0][1]
        temp = res[0][0]
        res[0][0] = res[0][0] + res[0][1]
        res[0][1] = temp
        return res


# 递归，效率较低，O(2^n)
class Solution1:
    def Fibonacci(self, n):
        # write code here
        if n <= 1:
            return n
        else:
            return self.Fibonacci(n-1) + self.Fibonacci(n-2)


if __name__ == "__main__":
    n = 32
    t = time()
    print("recursion: {} (time used: {:.4f}s)".format(
        Solution1().Fibonacci(n), time()-t))
    t = time()
    print("math formula: {} (time used: {:.4f}s)".format(
        Solution2().Fibonacci(n), time()-t))
    t = time()
    print("iteration: {} (time used: {:.4f}s)".format(
        Solution().Fibonacci(n), time()-t))
    