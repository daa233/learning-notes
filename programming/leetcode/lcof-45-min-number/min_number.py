# @problem: 剑指 Offer 45. 把数组排成最小的数
# @file: min_number.py
# @url: https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof
# @description:
#
# 输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。
# 示例 1:
# 输入: [10,2]
# 输出: "102"
# 示例 2:
# 输入: [3,30,34,5,9]
# 输出: "3033459"
# 提示:
#
# 0 < nums.length <= 100
#
# 说明:
#
# 输出结果可能非常大，所以你需要返回一个字符串而不是整数
# 拼接起来的数字可能会有前导 0，最后结果不需要去掉前导 0
#
# @author: Du Ang
# @date: May 18, 2023

from typing import List
from functools import cmp_to_key


def compare(num_a: int, num_b: int) -> int:
    """Compare the the concatenate nums by string comparison"""
    a = str(num_a)
    b = str(num_b)
    if a + b < b + a:
        return -1
    elif a + b == b + a:
        return 0
    else:
        return 1


class Solution1:
    def minNumber(self, nums: List[int]) -> str:
        nums = sorted(nums, key=cmp_to_key(compare))
        return "".join([str(num) for num in nums])


def quick_sort(nums: List[int]) -> None:
    def _partition(nums: List[int], left: int, right: int) -> int:
        pivot = left
        index = left + 1
        for i in range(index, right + 1):
            if compare(nums[i], nums[pivot]) == -1:
                nums[i], nums[index] = nums[index], nums[i]
                index += 1
        index -= 1
        nums[pivot], nums[index] = nums[index], nums[pivot]
        return index

    def _quick_sort(nums: List[int], left: int, right: int) -> None:
        if left < right:
            pivot = _partition(nums, left, right)
            _quick_sort(nums, left, pivot - 1)
            _quick_sort(nums, pivot + 1, right)

    _quick_sort(nums, 0, len(nums) - 1)


class Solution:
    def minNumber(self, nums: List[int]) -> str:
        quick_sort(nums)
        return "".join([str(num) for num in nums])


def check_result(inp: List[int], expected: str) -> None:
    out = sln.minNumber(inp)
    assert out == expected, f"inp {inp}, out {out} not equal {expected}"


if __name__ == "__main__":
    sln = Solution()

    nums = [10, 2]
    check_result(nums, "102")

    nums = [3, 30, 34, 5, 9]
    check_result(nums, "3033459")

    nums = [1, 1, 1]
    check_result(nums, "111")

    nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
    check_result(nums, "0123456789")

    nums = [0] * 100
    check_result(nums, "0" * 100)
