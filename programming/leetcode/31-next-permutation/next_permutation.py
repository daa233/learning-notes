# @problem: 31. Next Permutation
# @file: next_permutation.py
# @url: https://leetcode-cn.com/problems/next-permutation
# @description:
#
# A permutation of an array of integers is an arrangement of its members
# into a sequence or linear order.
#
# For example, for arr = [1,2,3], the following are all the permutations
# of arr: [1,2,3], [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1].
#
# The next permutation of an array of integers is the next
# lexicographically greater permutation of its integer. More formally,
# if all the permutations of the array are sorted in one container
# according to their lexicographical order, then the next permutation of
# that array is the permutation that follows it in the sorted container.
# If such arrangement is not possible, the array must be rearranged as
# the lowest possible order (i.e., sorted in ascending order).
#
# For example, the next permutation of arr = [1,2,3] is [1,3,2].
# Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
# While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1]
# does not have a lexicographical larger rearrangement.
#
# Given an array of integers nums, find the next permutation of nums.
# The replacement must be in place and use only constant extra memory.
# Example 1:
#
# Input: nums = [1,2,3]
# Output: [1,3,2]
#
# Example 2:
#
# Input: nums = [3,2,1]
# Output: [1,2,3]
#
# Example 3:
#
# Input: nums = [1,1,5]
# Output: [1,5,1]
#
# Constraints:
#
# 1 <= nums.length <= 100
# 0 <= nums[i] <= 100
#
# @author: Du Ang
# @date: May 21, 2023
from typing import List


class Solution:
    def nextPermutation(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """

        # 从后向前寻找第一个升序对
        i = len(nums) - 2
        while i >= 0 and nums[i] >= nums[i + 1]:
            i -= 1

        if i >= 0:  # 注意 python 中 i < 0 时也可以索引
            j = i + 1  # (i, j) 为寻找到的升序对
            k = len(nums) - 1
            # 从后向前寻找 A[k] > A[i]
            while k >= j and nums[i] >= nums[k]:
                k -= 1
            # 交换 A[i] 和 A[k]
            nums[i], nums[k] = nums[k], nums[i]
        else:
            j = 0

        # 此时 [j, end) 范围一定是降序排列的，对其逆序
        left, right = j, len(nums) - 1
        while left < right:
            nums[left], nums[right] = nums[right], nums[left]
            left += 1
            right -= 1


if __name__ == "__main__":
    sln = Solution()
    nums = [1, 2, 3]
    sln.nextPermutation(nums)
    print(nums)
    nums = [3, 2, 1]
    sln.nextPermutation(nums)
    print(nums)
