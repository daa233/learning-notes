# @problem: 剑指 Offer II 008. 和大于等于 target 的最短子数组
# @file: min_sub_array_len.py
# @url: https://leetcode-cn.com/problems/2VG8Kg
# @description:
#
# 给定一个含有 n 个正整数的数组和一个正整数 target 。
# 找出该数组中满足其和 ≥ target 的长度最小的 连续子数组
# [nums_l, nums_l+1, ..., nums_r-1, nums_r]
# ，并返回其长度。如果不存在符合条件的子数组，返回 0 。
# 示例 1：
#
# 输入：target = 7, nums = [2,3,1,2,4,3]
# 输出：2
# 解释：子数组 [4,3] 是该条件下的长度最小的子数组。
#
# 示例 2：
#
# 输入：target = 4, nums = [1,4,4]
# 输出：1
#
# 示例 3：
#
# 输入：target = 11, nums = [1,1,1,1,1,1,1,1]
# 输出：0
#
# 提示：
#
# 1 <= target <= 10^9
# 1 <= nums.length <= 10^5
# 1 <= nums[i] <= 10^5
#
# 进阶：
#
# 如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个 O(n log(n)) 时间复杂度的解法。
#
# 注意：本题与主站 209 题相同：https://leetcode-cn.com/problems/minimum-size-
# subarray-sum/
#
# @author: Du Ang
# @date: Mar 20, 2022

import sys
from typing import List


class Solution1:
    """双指针法。将左指针放在外循环，实现起来较为复杂。
    时间复杂度：O(n)
    空间复杂度：O(1)
    """

    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        if not nums:
            return 0
        elif len(nums) == 1:
            if nums[0] >= target:
                return 1
            else:
                return 0

        min_len = -1
        left = 0
        right = left + 1
        s = nums[left]
        while left < len(nums):
            if nums[left] >= target:
                min_len = 1
                break

            if right < len(nums):
                if s + nums[right] >= target:
                    if min_len < 0:
                        min_len = right - left + 1
                    else:
                        min_len = min(min_len, right - left + 1)
                    s -= nums[left]
                    left += 1
                    if left == right:
                        right += 1
                else:
                    s += nums[right]
                    right += 1
            else:
                if s >= target:
                    if min_len < 0:
                        min_len = len(nums) - left + 1
                    else:
                        min_len = min(min_len, len(nums) - left + 1)
                    s -= nums[left]
                    left += 1
                else:
                    break

        if min_len < 0:
            return 0
        else:
            return min_len


class Solution:
    """双指针法。将右指针放在外循环，实现起来较为简洁。
    时间复杂度：O(n)
    空间复杂度：O(1)
    """

    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        left = 0
        right = 0
        min_len = sys.maxsize
        s = 0

        while right < len(nums):
            s += nums[right]
            while s >= target and left <= right:
                min_len = min(min_len, right - left + 1)
                if min_len == 1:
                    return min_len
                s -= nums[left]
                left += 1
            right += 1

        if min_len == sys.maxsize:
            min_len = 0

        return min_len


class Solution2:
    """前缀和 + 二分搜索
    时间复杂度：O(nlog(n))
    空间复杂度：O(n)
    """

    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        min_len = sys.maxsize
        prefix_sums = self.getPrefixSum(nums)

        for i in range(len(prefix_sums)):
            if i == 0:
                t = target
            else:
                t = prefix_sums[i - 1] + target
            bound = self.lowerBound(prefix_sums, i, len(prefix_sums), t)
            if bound >= 0:
                min_len = min(min_len, bound - (i - 1))

        if min_len == sys.maxsize:
            min_len = 0

        return min_len

    def getPrefixSum(self, nums: List[int]) -> List[int]:
        prefix_sum_nums = []
        s = 0
        for num in nums:
            s += num
            prefix_sum_nums.append(s)
        return prefix_sum_nums

    def lowerBound(self, nums: List[int], left: int, right: int, target: int) -> int:
        """
        Return the first element in the range [left, right) which greater or
        equal to the target.
        """
        orig_right = right

        while left < right:
            mid = (left + right) >> 1
            if nums[mid] < target:
                left = mid + 1
            else:
                right = mid

        if left >= orig_right or nums[left] < target:
            return -1
        else:
            return left
