# @problem: 167. Two Sum II - Input Array Is Sorted
# @file: two_sum_ii_input_array_is_sorted.py
# @url: https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted
# @description:
#
# Given a 1-indexed array of integers numbers that is already sorted in
# non-decreasing order, find two numbers such that they add up to a
# specific target number. Let these two numbers be numbers[index1] and
# numbers[index2] where 1 <= index1 < index2 <= numbers.length.
# Return the indices of the two numbers, index1 and index2, added by one
# as an integer array [index1, index2] of length 2.
# The tests are generated such that there is exactly one solution. You
# may not use the same element twice.
# Your solution must use only constant extra space.
# Example 1:
#
# Input: numbers = [2,7,11,15], target = 9
# Output: [1,2]
# Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 =
# 2. We return [1, 2].
#
# Example 2:
#
# Input: numbers = [2,3,4], target = 6
# Output: [1,3]
# Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 =
# 3. We return [1, 3].
#
# Example 3:
#
# Input: numbers = [-1,0], target = -1
# Output: [1,2]
# Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 =
# 2. We return [1, 2].
#
# Constraints:
#
# 2 <= numbers.length <= 3 * 10^4
# -1000 <= numbers[i] <= 1000
# numbers is sorted in non-decreasing order.
# -1000 <= target <= 1000
# The tests are generated such that there is exactly one solution.
#
# @author: Du Ang
# @date: Mar 09, 2022

from typing import List


class Solution:
    """
    双指针法。由于数组是升序排列的，可以设置左右各一个指针，从两边向中间逼近正确结果。
    在循环中，如果两个指针对应的数字之和等于 target，返回两个指针对应的索引；如果之
    和大于 target，右指针左移一位；如果之和小于 target，左指针右移一位。
    时间复杂度：O(n)
    空间复杂度：O(1)
    """

    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        pi = 0
        pj = len(numbers) - 1
        while pi < pj:
            s = numbers[pi] + numbers[pj]
            if s == target:
                return [pi + 1, pj + 1]
            elif s > target:
                pj -= 1
            else:
                pi += 1


class Solution2:
    """
    二分查找（无法通过）。
    可以首先固定第一个数，然后寻找第二个数，第二个数等于目标值减去第一个数的差。
    利用数组的有序性质，可以通过二分查找的方法寻找第二个数。为了避免重复寻找，在
    寻找第二个数时，只在第一个数的右侧寻找。
    时间复杂度：O(nlogn)
    空间复杂度：O(1)
    """

    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        for i, number in enumerate(numbers):
            low = i + 1
            high = len(numbers) - 1
            while low <= high:
                mid = int((low + high) / 2)
                diff = target - number
                if numbers[mid] == diff:
                    return [i + 1, mid + 1]
                elif numbers[mid] > diff:
                    high = mid - 1
                else:
                    low = low + 1
