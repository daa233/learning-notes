# @problem: 509. Fibonacci Number
# @file: fibonacci_number.py
# @url: https://leetcode-cn.com/problems/fibonacci-number
# @description: 
# 
# The Fibonacci numbers, commonly denoted F(n) form a sequence, called
# the Fibonacci sequence, such that each number is the sum of the two
# preceding ones, starting from 0 and 1. That is,
# F(0) = 0,   F(1) = 1
# F(N) = F(N - 1) + F(N - 2), for N > 1.
# 
# Given N, calculate F(N).
# Example 1:
# Input: 2
# Output: 1
# Explanation: F(2) = F(1) + F(0) = 1 + 0 = 1.
# 
# Example 2:
# Input: 3
# Output: 2
# Explanation: F(3) = F(2) + F(1) = 1 + 1 = 2.
# 
# Example 3:
# Input: 4
# Output: 3
# Explanation: F(4) = F(3) + F(2) = 2 + 1 = 3.
# 
# Note:
# 0 ≤ N ≤ 30.
# 
# @author: Du Ang
# @date: Sep 15, 2019

from typing import List


# DP, O(n)
class Solution:
    def fib(self, N: int) -> int:
        if N <=1 :
            return N
        f0 = 0
        f1 = 1
        for i in range(2, N+1):
            f2 = f1 + f0
            f0 = f1
            f1 = f2
        return f2


# Math equation, O(logn)
# [[f(n), f(n-1)], [f(n-1), f(n-2)]] = [[1, 1], [1, 0]]^(n-1)
class Solution2:
    def fib(self, N: int) -> int:
        if N <= 1:
            return N
        res = [[1, 1], [1, 0]]
        for i in range(N-2):
            res = self.matmul_one(res)
        return res[0][0]

    def matmul_one(self, res: List) -> List:
        # optimized according to [[1, 1], [1, 0]]
        res[1][0] = res[0][0]
        res[1][1] = res[0][1]
        temp = res[0][0]
        res[0][0] = res[0][0] + res[0][1]
        res[0][1] = temp
        return res


# Recursion, slow, O(2^n)
class Solution1:
    def fib(self, N: int) -> int:
        if N <= 1:
            return N
        else:
            return self.fib(N-1) + self.fib(N-2)



