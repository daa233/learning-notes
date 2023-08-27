# @problem: 剑指 Offer 14- I. 剪绳子
# @file: cutting_rope.py
# @url: https://leetcode-cn.com/problems/jian-sheng-zi-lcof
# @description:
#
# 给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），每段绳子的长度记为
# k[0],k[1]...k[m-1] 。请问 k[0]*k[1]*...*k[m-1]
# 可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
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
# 2 <= n <= 58
#
# 注意：本题与主站 343 题相同：https://leetcode-cn.com/problems/integer-break/
#
# @author: Du Ang
# @date: Aug 13, 2023

import math


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

    def cuttingRope(self, n: int) -> int:
        self.hash_table = {}
        return self._max_prod(n)


class Solution:
    """数学"""

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
            pow_3 = n // 3
            r = n % 3
            if r == 2:
                prod = math.pow(3, pow_3) * 2
            elif r == 1:
                prod = math.pow(3, pow_3 - 1) * 2 * 2
            else:
                prod = math.pow(3, pow_3)
            return int(prod)


if __name__ == "__main__":
    sln = Solution()
    print(sln.cuttingRope(10))
