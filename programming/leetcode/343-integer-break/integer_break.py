# @problem: 343. Integer Break
# @file: integer_break.py
# @url: https://leetcode-cn.com/problems/integer-break
# @description:
#
# Given an integer n, break it into the sum of k positive integers,
# where k >= 2, and maximize the product of those integers.
# Return the maximum product you can get.
# Example 1:
#
# Input: n = 2
# Output: 1
# Explanation: 2 = 1 + 1, 1 × 1 = 1.
#
# Example 2:
#
# Input: n = 10
# Output: 36
# Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
#
# Constraints:
#
# 2 <= n <= 58
#
# @author: Du Ang
# @date: Sep 02, 2023


class Solution1:
    """动态规划 - 记忆表法"""

    def _max_prod(self, n: int) -> int:
        if n in self.hash_table:
            return self.hash_table[n]

        if n == 1:
            res = 1
        elif n == 2:
            res = 1
        elif n == 3:
            res = 2
        else:
            _max = 0
            for i in range(1, n // 2 + 1):
                tmp = max(
                    i * self._max_prod(n - i),
                    i * (n - i),
                )
                if tmp > _max:
                    _max = tmp
            res = _max

        if n not in self.hash_table:
            self.hash_table[n] = res

        return res

    def integerBreak(self, n: int) -> int:
        self.hash_table = {}
        return self._max_prod(n)


class Solution:
    """数学"""

    def integerBreak(self, n: int) -> int:
        if n <= 3:
            # 至少要切为2段，所以当 n <= 3 时，切分为 n-1 和 1 两段
            return n - 1
        elif n == 4:
            # 当 n = 4 时，切分为 2 和 2 两段，乘积为 4
            return 4
        else:
            # 当 n > 5 时，
            # 1. 最优：尽可能切分为 3 的 片段
            # 2. 次优：2。若最后一段绳子长度为 2，则保留，不再拆为 1+1。
            # 3. 最差：1。若最后一段绳子长度为 1；则应把一份 3+1 替换为 2+2，
            #    因为 2x2 > 3x1。
            a = n // 3
            r = n % 3
            if r == 2:
                prod = (3 ** a) * 2
            elif r == 1:
                prod = (3 ** (a - 1)) * 2 * 2
            else:
                prod = 3 ** a
            return prod


class Solution2:
    """
    贪心算法
    1. 尽可能分解出长度为 3 的小段
    2. 当剩余长度小于等于 4 时，不再分割
    """

    def integerBreak(self, n: int) -> int:
        if n == 4:
            return 4
        elif n < 4:
            return n - 1
        else:
            prod = 1
            while n > 4:
                prod = prod * 3
                n = n - 3
            prod = prod * n
            return prod
