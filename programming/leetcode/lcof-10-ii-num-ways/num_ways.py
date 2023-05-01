# @problem: 剑指 Offer 10- II. 青蛙跳台阶问题
# @file: num_ways.py
# @url: https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof
# @description:
#
# 一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。
# 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
# 示例 1：
# 输入：n = 2
# 输出：2
#
# 示例 2：
# 输入：n = 7
# 输出：21
#
# 示例 3：
# 输入：n = 0
# 输出：1
# 提示：
#
# 0 <= n <= 100
#
# 注意：本题与主站 70 题相同：https://leetcode-cn.com/problems/climbing-stairs/
#
# @author: Du Ang
# @date: May 01, 2023


class Solution:
    def numWays(self, n: int) -> int:
        MOD = 1000000007
        a = 1
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
