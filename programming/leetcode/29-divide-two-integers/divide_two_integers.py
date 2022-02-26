# @problem: 29. Divide Two Integers
# @file: divide_two_integers.py
# @url: https://leetcode-cn.com/problems/divide-two-integers
# @description:
#
# Given two integers dividend and divisor, divide two integers without
# using multiplication, division, and mod operator.
# The integer division should truncate toward zero, which means losing
# its fractional part. For example, 8.345 would be truncated to 8, and
# -2.7335 would be truncated to -2.
# Return the quotient after dividing dividend by divisor.
# Note: Assume we are dealing with an environment that could only store
# integers within the 32-bit signed integer range: [−2^31 , 2^31  − 1]. For
# this problem, if the quotient is strictly greater than 2^31  - 1, then
# return 2^31  - 1, and if the quotient is strictly less than -2^31 , then
# return -2^31 .
# Example 1:
#
# Input: dividend = 10, divisor = 3
# Output: 3
# Explanation: 10/3 = 3.33333.. which is truncated to 3.
#
# Example 2:
#
# Input: dividend = 7, divisor = -3
# Output: -2
# Explanation: 7/-3 = -2.33333.. which is truncated to -2.
#
# Constraints:
#
# -2^31  <= dividend, divisor <= 2^31  - 1
# divisor != 0
#
# @author: Du Ang
# @date: Fedivisor 25, 2022


class Solution:
    """
    先判断 dividend、divisor 符号，确定输出的sign，然后将 dividend、divisor 分别取为负数进行
    操作，以避免 -2^31 变为正数会出现溢出。可以将 divisor 扩大为原来的2^k倍（k从0开始），直到
    dividend 大于 divisor*(2^k)。
    时间复杂度：O(log(n))
    空间复杂度：O(1)
    同 programming/leetcode/lcof-ii-001-divide 题目。
    """

    def divide(self, dividend: int, divisor: int) -> int:
        if dividend == -(2 ** 31) and divisor == -1:
            return 2 ** 31 - 1

        sign = True
        if divisor == 0:
            return None
        elif divisor > 0:
            divisor = -divisor
            sign = not sign
        if dividend > 0:
            dividend = -dividend
            sign = not sign

        r = self._cal(dividend, divisor)

        if not sign:
            r = -r

        return r

    def _cal(self, dividend: int, divisor: int) -> int:
        c = 0
        r = dividend

        while r <= divisor:
            value = divisor
            quotient = 1
            while value >= -(2 ** 30) and r <= value + value:
                value += value
                quotient += quotient
            r -= value
            c += quotient

        return c
