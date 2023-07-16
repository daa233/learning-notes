# @problem: 剑指 Offer 16. 数值的整数次方
# @file: my_pow.py
# @url: https://leetcode-cn.com/problems/shu-zhi-de-zheng-shu-ci-fang-lcof
# @description:
#
# 实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，x^n）。不得使用库函数，同时不需要考虑大数问题。
# 示例 1：
#
# 输入：x = 2.00000, n = 10
# 输出：1024.00000
#
# 示例 2：
#
# 输入：x = 2.10000, n = 3
# 输出：9.26100
# 示例 3：
#
# 输入：x = 2.00000, n = -2
# 输出：0.25000
# 解释：2-2 = 1/22 = 1/4 = 0.25
# 提示：
#
# -100.0 < x < 100.0
# -2^31 <= n <= 2^31-1
# n 是一个整数
# 要么 x 不为零，要么 n > 0 。
# -10^4 <= x^n <= 10^4
#
# 注意：本题与主站 50 题相同：https://leetcode-cn.com/problems/powx-n/
#
# @author: Du Ang
# @date: Jul 16, 2023


class Solution1:
    """循环相乘（超出时间限制）"""

    def myPow(self, x: float, n: int) -> float:
        res = 1
        if n >= 0:
            sign = 1
        else:
            sign = -1
            n = -n

        for _ in range(n):
            res *= x

        if sign == -1:
            res = 1.0 / res

        return res


class Solution2:
    """快速幂迭代法"""

    def myPow(self, x: float, n: int) -> float:
        if n >= 0:
            sign = 1
        else:
            sign = -1
            n = -n

        if n == 0:
            return 1

        res = 1
        base = x
        while n > 0:
            if n % 2 == 1:
                # 当 n 为大于 1 的奇数时，需要多乘一次 base
                res = res * base
            base = base * base
            n = n // 2

        if sign == -1:
            res = 1.0 / res

        return res


class Solution:
    """快速幂递归法"""

    def myPow(self, x: float, n: int) -> float:
        if n == 0:
            return 1
        elif n == 1:
            return x
        elif n == -1:
            return 1.0 / x

        half = self.myPow(x, n // 2)
        if n % 2 == 0:
            res = half * half
        else:
            res = x * half * half

        return res
