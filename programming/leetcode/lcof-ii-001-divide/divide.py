# @problem: 剑指 Offer II 001. 整数除法
# @file: divide.py
# @url: https://leetcode-cn.com/problems/xoh6Oh
# @description:
#
# 给定两个整数 a 和 b ，求它们的除法的商 a/b ，要求不得使用乘号 '*'、除号 '/' 以及求余符号 '%' 。
# 注意：
#
# 整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2
# 假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−2^31, 2^31−1]。本题中，如果除法结果溢出，则返回 2^31 − 1
#
# 示例 1：
#
# 输入：a = 15, b = 2
# 输出：7
# 解释：15/2 = truncate(7.5) = 7
#
# 示例 2：
#
# 输入：a = 7, b = -3
# 输出：-2
# 解释：7/-3 = truncate(-2.33333..) = -2
# 示例 3：
#
# 输入：a = 0, b = 1
# 输出：0
# 示例 4：
#
# 输入：a = 1, b = 1
# 输出：1
# 提示:
#
# -2^31 <= a, b <= 2^31 - 1
# b != 0
#
# 注意：本题与主站 29 题相同：https://leetcode-cn.com/problems/divide-two-integers/
#
# @author: Du Ang
# @date: Feb 21, 2022


class Solution1:
    """
    （无法通过解答）
    利用循环计数，不断用a的绝对值减去b的绝对值，直到a<b，返回计数（需要判断正负号）。
    当 a 很大、b 很小时，这种方法耗时巨大，无法通过解答。且此方法未考虑溢出情况。
    时间复杂度：O(n)
    空间复杂度：O(1)
    """

    def divide(self, a: int, b: int) -> int:

        if b == 0:
            return

        if a > 0 and b > 0:
            sign = True
        elif a < 0 and b < 0:
            a = -a
            b = -b
            sign = True
        else:
            if a < 0:
                a = -a
            if b < 0:
                b = -b
            sign = False

        c = 0
        while a >= b:
            a -= b
            c += 1

        if not sign:
            c = -c

        return c


class Solution2:
    """
    先判断a、b 符号，确定输出的sign，然后将 a、b 分别取为负数进行操作，以避免 -2^31 变为正数
    会出现溢出。可以将b扩大为原来的2^k倍（可以用位操作实现，从31开始从高到低遍历），然后用a去减，
    最后的商是1+...+2^k。
    时间复杂度：O(log(n) * sizeof(int)) = O(log(n))
    空间复杂度：O(1)
    """

    def divide(self, a: int, b: int) -> int:
        sign = True

        if b == 0:
            return None
        elif b == -1 and a == -(2 ** 31):
            return 2 ** 31 - 1
        elif b > 0:
            b = -b
            sign = not sign

        if a > 0:
            a = -a
            sign = not sign

        c = 0
        r = a
        for k in range(31, -1, -1):
            tmp = b << k
            if r <= tmp:
                r -= tmp
                c += 2 ** k

        if not sign:
            c = -c

        return c


class Solution:
    """
    基于上面的 Solution2 优化。
    先判断a、b 符号，确定输出的sign，然后将 a、b 分别取为负数进行操作，以避免 -2^31 变为正数
    会出现溢出。可以将b扩大为原来的2^k倍（k从0开始），直到a大于b*(2^k)。
    时间复杂度：O(log(n))
    空间复杂度：O(1)
    """

    def divide(self, a: int, b: int) -> int:
        if a == -(2 ** 31) and b == -1:
            return 2 ** 31 - 1

        sign = True
        if b == 0:
            return None
        elif b > 0:
            b = -b
            sign = not sign
        if a > 0:
            a = -a
            sign = not sign

        r = self._cal(a, b)

        if not sign:
            r = -r

        return r

    def _cal(self, a: int, b: int) -> int:
        c = 0
        r = a

        while r <= b:
            value = b
            quotient = 1
            while r <= value + value:
                value += value
                quotient += quotient
            r -= value
            c += quotient

        return c
