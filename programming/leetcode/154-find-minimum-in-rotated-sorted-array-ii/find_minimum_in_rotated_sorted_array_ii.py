# @problem: 154. Find Minimum in Rotated Sorted Array II
# @file: find_minimum_in_rotated_sorted_array_ii.py
# @url: https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii
# @description:
#
# Suppose an array of length n sorted in ascending order is rotated
# between 1 and n times. For example, the array nums = [0,1,4,4,5,6,7]
# might become:
#
# [4,5,6,7,0,1,4] if it was rotated 4 times.
# [0,1,4,4,5,6,7] if it was rotated 7 times.
#
# Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time
# results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
# Given the sorted rotated array nums that may contain duplicates,
# return the minimum element of this array.
# You must decrease the overall operation steps as much as possible.
# Example 1:
# Input: nums = [1,3,5]
# Output: 1
# Example 2:
# Input: nums = [2,2,2,0,1]
# Output: 0
#
# Constraints:
#
# n == nums.length
# 1 <= n <= 5000
# -5000 <= nums[i] <= 5000
# nums is sorted and rotated between 1 and n times.
#
# Follow up: This problem is similar to Find Minimum in Rotated Sorted
# Array, but nums may contain duplicates. Would this affect the runtime
# complexity? How and why?
#
# @author: Du Ang
# @date: Apr 16, 2023

from typing import List


class Solution:
    def findMin(self, nums: List[int]) -> int:
        left = 0
        right = len(nums) - 1

        while left < right:
            mid = left + (right - left) // 2
            if nums[mid] > nums[right]:
                left = mid + 1
            elif nums[mid] < nums[right]:
                right = mid
            else:
                # 此时 number[mid] == nums[right]，无法确定最小值在左右哪个区间，
                # 但是可以确定 nums[mid] 可以替换 nums[right]，因此通过 right -= 1缩小区间
                right -= 1

        return nums[left]
