# @problem: 34. Find First and Last Position of Element in Sorted Array
# @file: find_first_and_last_position_of_element_in_sorted_array.py
# @url: https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array
# @description:
#
# Given an array of integers nums sorted in non-decreasing order, find
# the starting and ending position of a given target value.
# If target is not found in the array, return [-1, -1].
# You must write an algorithm with O(log n) runtime complexity.
# Example 1:
# Input: nums = [5,7,7,8,8,10], target = 8
# Output: [3,4]
# Example 2:
# Input: nums = [5,7,7,8,8,10], target = 6
# Output: [-1,-1]
# Example 3:
# Input: nums = [], target = 0
# Output: [-1,-1]
#
# Constraints:
#
# 0 <= nums.length <= 10^5
# -10^9 <= nums[i] <= 10^9
# nums is a non-decreasing array.
# -10^9 <= target <= 10^9
#
# @author: Du Ang
# @date: Apr 08, 2023

from typing import List


def binary_search(a: List, target, left: int = 0, right: int = None, leftmost: bool = True) -> int:
    """
    If `leftmost = True`, the return value i is such that all e in a[:i] have e < x,
    and all e in a[i:] have e >= x.
    If `leftmost = False`, the return value i is such that all e in a[:i] have e <= x,
    and all e in a[i:] have e > x.
    """

    def condition(value, target, leftmost: bool = True) -> bool:
        if leftmost:
            return value >= target
        else:
            return value > target

    if left < 0:
        raise ValueError("left must be non-negative instead of {}".format(left))
    if right is None:
        right = len(a)

    while left < right:
        mid = left + (right - left) // 2
        if condition(a[mid], target, leftmost):
            right = mid
        else:
            left = mid + 1
    return left


class Solution:
    def searchRange(self, nums: List[int], target: int) -> List[int]:
        left_bound = binary_search(nums, target, leftmost=True)
        if left_bound != len(nums) and nums[left_bound] == target:
            right_bound = binary_search(nums, target, leftmost=False)
            return [left_bound, right_bound - 1]
        else:
            return [-1, -1]
