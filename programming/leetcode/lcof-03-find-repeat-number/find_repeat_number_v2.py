# @problem: 剑指 Offer 03. 数组中重复的数字（变体）
# @file: find_repeat_number_v2.py
# @url: https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof
# @description:
#
# 找出数组中重复的数字。
#
# 在一个长度为 n+1 的数组 nums 里的所有数字都在 1~n
# 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
# 示例 1：
# 输入：
# [2, 3, 1, 2, 5, 3]
# 输出：2 或 3
#
# 限制：
# 2 <= n <= 100000
#
# @author: Du Ang
# @date: Jan 17, 2021

from typing import List


class Solution:
    """
    类似于二分查找，取m属于1到n，统计数组中处于 [1, m] 区间的元素个数 count，
    若 count 大于 m，则重复数字位于该区间；否则，则重复数字位于 [m+1, n] 区间。
    继续在缩小后的区间内搜索，当区间范围只包含一个数字时，返回该数字。

    时间复杂度：O(nlog(n))
    空间复杂度：O(1)
    """

    def findRepeatNumber(self, nums: List[int]) -> int:
        a = 0
        b = len(nums) - 1
        while a < b:
            m = a + int((b - a) / 2)
            count = self.countRange(nums, a, m)
            print("count ", a, m, count)
            if count > (m - a + 1):
                b = m
            else:
                a = m + 1
        return a

    def countRange(self, nums: List[int], a: int, b: int) -> int:
        count = 0
        for num in nums:
            if num >= a and num <= b:
                count += 1
        return count
