# @problem: 剑指 Offer 56 - I. 数组中数字出现的次数
# @file: single_numbers.py
# @url: https://leetcode-cn.com/problems/shu-zu-zhong-shu-zi-chu-xian-de-ci-shu-lcof
# @description:
#
# 一个整型数组 nums
# 里除两个数字之外，其他数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。
# 示例 1：
# 输入：nums = [4,1,4,6]
# 输出：[1,6] 或 [6,1]
#
# 示例 2：
# 输入：nums = [1,2,10,4,1,4,3,3]
# 输出：[2,10] 或 [10,2]
# 限制：
#
# 2 <= nums.length <= 10000
#
# @author: Du Ang
# @date: Jul 30, 2023

from typing import List


class Solution1:
    """哈希表，不满足空间复杂度需求"""

    def singleNumbers(self, nums: List[int]) -> List[int]:
        hash_set = set()
        for num in nums:
            if num in hash_set:
                hash_set.remove(num)
            else:
                hash_set.add(num)
        return list(hash_set)


class Solution:
    """位运算，分组异或"""

    def singleNumbers(self, nums: List[int]) -> List[int]:
        s = 0
        for num in nums:
            s = s ^ num
        i = 0
        while (s >> i) & 1 == 0:
            i += 1
        a_xor_res = 0
        b_xor_res = 0
        for num in nums:
            if (num >> i) & 1:
                a_xor_res = a_xor_res ^ num
            else:
                b_xor_res = b_xor_res ^ num
        return [a_xor_res, b_xor_res]
