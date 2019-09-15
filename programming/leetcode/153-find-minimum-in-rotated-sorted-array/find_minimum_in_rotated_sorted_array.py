# @problem: 153. Find Minimum in Rotated Sorted Array
# @file: find_minimum_in_rotated_sorted_array.py
# @url: https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array
# @description: 
# 
# Suppose an array sorted in ascending order is rotated at some pivot
# unknown to you beforehand.
# (i.e.,  [0,1,2,4,5,6,7] might become  [4,5,6,7,0,1,2]).
# Find the minimum element.
# You may assume no duplicate exists in the array.
# Example 1:
# Input: [3,4,5,1,2]
# Output: 1
# 
# Example 2:
# Input: [4,5,6,7,0,1,2]
# Output: 0
# 
# @author: Du Ang
# @date: Sep 15, 2019

from typing import List

# If there are not repeating elements:
# (1) l-->--m---->r, the min lies in the left of nums[mid]
#   (including nums[mid]) so let right = mid
# (2) l----m-->-->r, the min lies in the right of nums[mid]
#   (not including nums[mid]) so let left = mid + 1
# If there are repeating elements (not this problem):
#   search one by one or shrink the search range one by one (right = right - 1)
class Solution:
    def findMin(self, nums: List[int]) -> int:
        left = 0
        right = len(nums) - 1

        # no rotation
        if nums[left] < nums[right]:
            return nums[left]

        while left < right:
            mid = (left + right) // 2
            if nums[mid] < nums[right]:
                # l-->--m-->r
                right = mid
            elif nums[mid] > nums[right]:
                # l--m-->-->r
                left = mid + 1  # +1 since nums[mid] can't be the min
            else:
                # nums[mid] == nums[right], shrink the search range
                right = right - 1
        return nums[left]



