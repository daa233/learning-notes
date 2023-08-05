# @problem: 剑指 Offer 56 - II. 数组中数字出现的次数 II
# @file: single_numbers.py
# @url: https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-ii-lcof
# @description:
#
# 在一个数组 nums 中除一个数字只出现一次之外，其他数字都出现了三次。请找出那个只出现一次的数字。
# 示例 1：
# 输入：nums = [3,4,3,3]
# 输出：4
#
# 示例 2：
# 输入：nums = [9,1,7,9,7,9,7]
# 输出：1
# 限制：
#
# 1 <= nums.length <= 10000
# 1 <= nums[i] < 2^31
#
# @author: Du Ang
# @date: Aug 04, 2023

from typing import List


class Solution:
    """每一位求和取余"""

    def singleNumber(self, nums: List[int]) -> int:
        k = 32
        s = [0] * k
        for num in nums:
            for i in range(k):
                s[i] += (num >> i) & 1
        r = [i % 3 for i in s]
        res = 0

        # 求和将二进制转为整数
        # for i, a in enumerate(r):
        #     res += a * (2 ** i)

        # 通过位运算将二进制转为整数
        for i in range(k):
            res = res << 1
            # 恢复第 i 位对应的值
            res |= r[k - 1 - i]

        return res


class Solution:
    """有限状态自动机"""

    def singleNumber(self, nums: List[int]) -> int:
        one = 0
        two = 0
        for num in nums:
            one = one ^ num & ~two
            two = two ^ num & ~one
        return one
