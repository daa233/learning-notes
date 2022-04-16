# @problem: 209. Minimum Size Subarray Sum
# @file: minimum_size_subarray_sum.py
# @url: https://leetcode-cn.com/problems/minimum-size-subarray-sum
# @description:
#
# Given an array of positive integers nums and a positive integer
# target, return the minimal length of a contiguous subarray [nums_l,
# nums_l+1, ..., nums_r-1, nums_r] of which the sum is greater than or
# equal to target. If there is no such subarray, return 0 instead.
# Example 1:
#
# Input: target = 7, nums = [2,3,1,2,4,3]
# Output: 2
# Explanation: The subarray [4,3] has the minimal length under the
# problem constraint.
#
# Example 2:
#
# Input: target = 4, nums = [1,4,4]
# Output: 1
#
# Example 3:
#
# Input: target = 11, nums = [1,1,1,1,1,1,1,1]
# Output: 0
#
# Constraints:
#
# 1 <= target <= 10^9
# 1 <= nums.length <= 10^5
# 1 <= nums[i] <= 10^5
#
# Follow up: If you have figured out the O(n) solution, try coding
# another solution of which the time complexity is O(n log(n)).
#
# @author: Du Ang
# @date: Apr 16, 2022
import sys
from typing import List


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
