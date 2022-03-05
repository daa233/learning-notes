# @problem: 剑指 Offer II 003. 前 n 个数字二进制中 1 的个数
# @file: count_bits.py
# @url: https://leetcode-cn.com/problems/w3tCBm
# @description:
#
# 给定一个非负整数 n ，请计算 0 到 n 之间的每个数字的二进制表示中 1 的个数，并输出一个数组。
# 示例 1:
#
# 输入: n = 2
# 输出: [0,1,1]
# 解释:
# 0 --> 0
# 1 --> 1
# 2 --> 10
#
# 示例 2:
#
# 输入: n = 5
# 输出: [0,1,1,2,1,2]
# 解释:
# 0 --> 0
# 1 --> 1
# 2 --> 10
# 3 --> 11
# 4 --> 100
# 5 --> 101
#
# 说明 :
#
# 0 <= n <= 10^5
#
# 进阶:
#
# 给出时间复杂度为 O(n*sizeof(integer)) 的解答非常容易。但你可以在线性时间 O(n) 内用一趟扫描做到吗？
# 要求算法的空间复杂度为 O(n) 。
# 你能进一步完善解法吗？要求在C++或任何其他语言中不使用任何内置函数（如 C++
# 中的 __builtin_popcount ）来执行此操作。
#
# 注意：本题与主站 338 题相同：https://leetcode-cn.com/problems/counting-bits/
#
# @author: Du Ang
# @date: Feb 27, 2022

from typing import List


class Solution1:
    """
    依次将每个数字转换为二进制数（或通过移位获取每个数字的所有二进制位），并统计1的个数。
    时间复杂度：O(n*sizeof(int))
    空间复杂度：O(1)
    """

    def countBits(self, n: int) -> List[int]:
        result = []
        for i in range(n + 1):
            count = self._countBitsHelper(i)
            result.append(count)
        return result

    def _countBitsHelper(self, n: int, nbits: int = 32) -> int:
        count = 0
        for i in range(nbits):
            bit = (n >> i) & 1
            if bit:
                count += 1
        return count


class Solution2:
    """
    找规律。当 n = 2^k 时，其二进制数字1的个数后半部分等于前半部分数组重复一遍，并且每个元素值加1。
    设 F(n) 为题目要求输出的数组，则：
      - F(0) = 0
      - F(1) = [0, 1]
      - F(2^k) = F(2^(k-1)) + [i+1 for i in F(2^(k-1))], k ≥ 1
    时间复杂度：O(n)
    空间复杂度：O(n)
    """

    def countBits(self, n: int) -> List[int]:
        if n <= 0:
            self._mem = [0]
            return self._mem
        elif n == 1:
            self._mem = [0, 1]
            return self._mem
        else:
            self._mem = [0, 1]
            k = 1
            while n >= 2 ** k:
                tmp = self._mem
                if n < 2 ** (k + 1):
                    tmp = tmp[: (n - 2 ** k) + 1]
                self._mem += [i + 1 for i in tmp]
                k += 1
            return self._mem


class Solution3:
    """
    通过每次计算“i & (i - 1)”将整数 i 最右边的 1 变成 0，统计 1 的个数。
    时间复杂度：O(n*k)，k为二进制形式中1的个数
    空间复杂度：O(1)
    """

    def countBits(self, n: int) -> List[int]:
        result = []

        for i in range(n + 1):
            if i == 0:
                result.append(0)
            else:
                j = i
                count = 0
                while j > 0:
                    j = j & (j - 1)
                    count += 1
                result.append(count)

        return result


class Solution4:
    """
    通过每次计算“i & (i - 1)”将整数 i 最右边的 1 变成 0，整数 i 的二进制形式
    中1的个数比“i & (i - 1)” 的二进制形式中1的个数多1。
    时间复杂度：O(n)
    空间复杂度：O(1)
    """

    def countBits(self, n: int) -> List[int]:
        result = []

        for i in range(n + 1):
            if i == 0:
                result.append(0)
            else:
                result.append(result[i & (i - 1)] + 1)

        return result


class Solution:
    """
    根据“i/2”计算i的二进制形式中1的个数。如果正整数 i 是一个偶数，那么i相当于
    将”i/2”左移一位的结果，因此偶数i和“i/2”的二进制形式中1的个数是相同的。如
    果i是奇数，那么i相当于将“i/2”左移一位之后再将最右边一位设为1的结果，因此奇
    数i的二进制形式中1的个数比“i/2”的1的个数多1。
    时间复杂度：O(n)
    空间复杂度：O(1)
    """

    def countBits(self, n: int) -> List[int]:
        result = []

        for i in range(n + 1):
            if i == 0:
                result.append(0)
            else:
                j = int(i / 2)
                if i % 2 == 0:
                    result.append(result[j])
                else:
                    result.append(result[j] + 1)

        return result


if __name__ == "__main__":
    n = 5
    print(Solution().countBits(n))
