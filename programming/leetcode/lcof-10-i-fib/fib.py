# @problem: 剑指 Offer 10- I. 斐波那契数列
# @file: fib.py
# @url: https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof
# @description:
#
# 写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项（即 F(N)）。斐波那契数列的定义如下：
#
# F(0) = 0,   F(1) = 1
# F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
# 斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。
# 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
# 示例 1：
#
# 输入：n = 2
# 输出：1
#
# 示例 2：
#
# 输入：n = 5
# 输出：5
#
# 提示：
#
# 0 <= n <= 100
#
# @author: Du Ang
# @date: Apr 28, 2023

from typing import List


class Solution:
    def fib(self, n: int) -> int:
        MOD = 1000000007
        a = 0
        b = 1

        if n == 0:
            return a
        elif n == 1:
            return b

        for _ in range(n - 1):
            orig_a = a
            a = b
            b = (orig_a + b) % MOD

        return b


class Solution2:
    def fib(self, n: int) -> int:
        MOD = 1000000007

        def matmul(a: List[List[int]], b: List[List[int]]) -> List[List[int]]:
            ret = [[0] * len(b[0]) for _ in range(len(a[0]))]

            for i in range(len(a)):
                for j in range(len(b[0])):
                    for k in range(len(a[0])):
                        ret[i][j] += a[i][k] * b[k][j]
                    ret[i][j] %= MOD

            return ret

        def quick_power(a: List[List[int]], n: int) -> List[List[int]]:
            ret = [[1, 0], [0, 1]]  # identity matrix for init
            while n > 0:
                # NOTE: 当 n > 0 时每次都会执行，若 n 为奇数，会比 n 为偶数时多执行一次
                # 此处利用位运算来巧妙地完成了 n 为奇数时多执行一次的操作
                if n & 1:
                    ret = matmul(ret, a)
                n >>= 1  # n *= 2, n is even now
                a = matmul(a, a)
            return ret

        if n < 2:
            return n

        res = quick_power([[1, 1], [1, 0]], n - 1)
        return res[0][0]
