# @problem: 剑指 Offer 57. 和为s的两个数字
# @file: two_sum.py
# @url: https://leetcode-cn.com/problems/he-wei-sde-liang-ge-shu-zi-lcof
# @description: 
#
# 输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。如果有多对数字的和等于s，则输出任意一对即可。
# 示例 1：
# 输入：nums = [2,7,11,15], target = 9
# 输出：[2,7] 或者 [7,2]
#
# 示例 2：
# 输入：nums = [10,26,30,31,47,60], target = 40
# 输出：[10,30] 或者 [30,10]
#
# 限制：
#
# 1 <= nums.length <= 10^5
# 1 <= nums[i] <= 10^6
#
# @author: Du Ang
# @date: May 12, 2023

from typing import List


class Solution1:
    """哈希表"""
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        hash_table = set()
        for num in nums:
            diff = target - num
            if diff in hash_table:
                return [num, diff]
            else:
                hash_table.add(num)
        return []


class Solution:
    """二分查找"""

    def binary_search(self, nums: List[int], target: int, left: int, right: int) -> int:
        if left < 0 or right > len(nums) or left >= right:
            return None

        if nums[left] > target or nums[right - 1] < target:
            return None

        while left < right:
            mid = left + (right - left) // 2
            if nums[mid] < target:
                left = mid + 1
            else:
                right = mid
        
        if left >= 0 and left < len(nums) and nums[left] == target:
            return left

    def twoSum(self, nums: List[int], target: int) -> List[int]:
        for i, num in enumerate(nums):
            found = self.binary_search(nums, target - num, 0, i)
            if not found:
                found = self.binary_search(nums, target - num, i+1, len(nums))
            if found:
                return [num, nums[found]]
        return []


class Solution:
    """双指针法"""

    def twoSum(self, nums: List[int], target: int) -> List[int]:
        left, right = 0, len(nums) - 1
        while left < right:
            s = nums[left] + nums[right]
            if s > target:
                right -= 1
            elif s < target:
                left += 1
            else:
                return [nums[left], nums[right]]
        return []
