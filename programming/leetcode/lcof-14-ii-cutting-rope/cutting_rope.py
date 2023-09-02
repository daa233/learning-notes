# @problem: 剑指 Offer 14- II. 剪绳子 II
# @file: cutting_rope.py
# @url: https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof
# @description:
#
# 给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为
# k[0],k[1]...k[m - 1] 。请问 k[0]*k[1]*...*k[m - 1]
# 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
# 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
# 示例 1：
# 输入: 2
# 输出: 1
# 解释: 2 = 1 + 1, 1 × 1 = 1
# 示例 2:
# 输入: 10
# 输出: 36
# 解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36
# 提示：
#
# 2 <= n <= 1000
#
# 注意：本题与主站 343 题相同：https://leetcode-cn.com/problems/integer-break/
#
# @author: Du Ang
# @date: Aug 27, 2023


MAX_INT = 1000000007


class Solution1:
    """
    数学，在 14 - I 的基础上最后增加一步求余操作。
    因为 Python 中变量取值范围由系统内存大小决定（无限大），所以不用考虑大数越界问题。
    """

    def quick_power(self, a: int, n: int):
        """快速幂"""
        ret = 1
        while n > 0:
            if n & 1:  # n > 0 时每次都会执行，若 n 为奇数，会比 n 为偶数时多执行一次
                ret *= a
            n = n >> 1
            a = a ** 2
        return ret

    def cuttingRope(self, n: int) -> int:
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
                prod = self.quick_power(3, a) * 2
            elif r == 1:
                prod = self.quick_power(3, a - 1) * 2 * 2
            else:
                prod = self.quick_power(3, a)
            return prod % MAX_INT


class Solution2:
    """
    贪心算法，加上考虑大数越界
    1. 尽可能分解出长度为 3 的小段
    2. 当剩余长度小于等于 4 时，不再分割
    """

    def cuttingRope(self, n: int) -> int:
        if n == 4:
            return 4
        elif n < 4:
            return n - 1
        else:
            prod = 1
            while n > 4:
                prod = prod * 3 % MAX_INT
                n = n - 3
            prod = prod * n % MAX_INT
            return prod


class Solution3:
    """
    大数求余（循环求余）
    """

    def loop_power_remainder(self, x: int, a: int, p: int) -> int:
        """
        循环求余
        x^a \bmod p = ((x^{a-1} \bmod p) (x \bmod p)) \bmod p
        """
        ret = 1
        for _ in range(a):
            ret = ret * x % p
        return ret

    def cuttingRope(self, n: int) -> int:
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
                prod = self.loop_power_remainder(3, a, MAX_INT) * 2 % MAX_INT
            elif r == 1:
                prod = self.loop_power_remainder(3, a - 1, MAX_INT) * 2 * 2 % MAX_INT
            else:
                prod = self.loop_power_remainder(3, a, MAX_INT)
            return prod


class Solution:
    """
    大数求余（快速幂求余）
    """

    def quick_power_remainder(self, x: int, a: int, p: int) -> int:
        """
        快速幂求余
        x^a \bmod p = ((x^{a-1} \bmod p) (x \bmod p)) \bmod p
        """
        ret = 1
        while a > 0:
            if a & 1:  # n > 0 时每次都会执行，若 n 为奇数，会比 n 为偶数时多执行一次
                ret = ret * x % p
            a = a >> 1
            x = x ** 2 % p
        return ret

    def cuttingRope(self, n: int) -> int:
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
                prod = self.quick_power_remainder(3, a, MAX_INT) * 2 % MAX_INT
            elif r == 1:
                prod = self.quick_power_remainder(3, a - 1, MAX_INT) * 2 * 2 % MAX_INT
            else:
                prod = self.quick_power_remainder(3, a, MAX_INT)
            return prod
