# @problem: 70. Climbing Stairs
# @file: climbing_stairs.py
# @url: https://leetcode-cn.com/problems/climbing-stairs
# @description:
#
# You are climbing a staircase. It takes n steps to reach the top.
# Each time you can either climb 1 or 2 steps. In how many distinct ways
# can you climb to the top?
# Example 1:
#
# Input: n = 2
# Output: 2
# Explanation: There are two ways to climb to the top.
# 1. 1 step + 1 step
# 2. 2 steps
#
# Example 2:
#
# Input: n = 3
# Output: 3
# Explanation: There are three ways to climb to the top.
# 1. 1 step + 1 step + 1 step
# 2. 1 step + 2 steps
# 3. 2 steps + 1 step
#
# Constraints:
#
# 1 <= n <= 45
#
# @author: Du Ang
# @date: May 01, 2023


class Solution:
    def climbStairs(self, n: int) -> int:
        a = 1
        b = 1

        if n == 0:
            return a
        elif n == 1:
            return b

        for _ in range(n - 1):
            orig_a = a
            a = b
            b = orig_a + b

        return b
