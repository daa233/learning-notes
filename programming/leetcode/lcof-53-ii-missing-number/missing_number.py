# @problem: 剑指 Offer 53 - II. 0～n-1中缺失的数字
# @file: missing_number.py
# @url: https://leetcode-cn.com/problems/que-shi-de-shu-zi-lcof
# @description:
#
# 一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。在范围0～n-1内的n个数字中有且只有一个数字不在
# 该数组中，请找出这个数字。
# 示例 1:
# 输入: [0,1,3]
# 输出: 2
#
# 示例 2:
# 输入: [0,1,2,3,4,5,6,7,9]
# 输出: 8
# 限制：
# 1 <= 数组长度 <= 10000
#
# @author: Du Ang
# @date: Apr 08, 2023

from typing import List


class Solution:
    def missingNumber(self, nums: List[int]) -> int:
        def condition(nums: List[int], mid: int):
            if nums[mid] > mid:
                return True
            else:
                return False

        left = 0
        right = len(nums)
        while left < right:
            mid = left + (right - left) // 2
            if condition(nums, mid):
                right = mid
            else:
                left = mid + 1

        return left


class Solution2:
    def missingNumber(self, nums: List[int]) -> int:
        result = 0
        for n in nums:
            result = result ^ n
        for n in range(len(nums) + 1):
            result = result ^ n
        return result


if __name__ == "__main__":
    solution = Solution()

    nums = [0, 1, 3]
    out = solution.missingNumber(nums)
    assert out == 2, f"out {out}"

    nums = [0, 1, 2, 3, 4, 5, 6, 7, 9]
    out = solution.missingNumber(nums)
    assert out == 8, f"out {out}"

    nums = [0]
    out = solution.missingNumber(nums)
    assert out == 1, f"out {out}"
