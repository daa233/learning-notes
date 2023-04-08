# @problem: 剑指 Offer 53 - I. 在排序数组中查找数字 I
# @file: search.py
# @url: https://leetcode-cn.com/problems/zai-pai-xu-shu-zu-zhong-cha-zhao-shu-zi-lcof
# @description:
#
# 统计一个数字在排序数组中出现的次数。
# 示例 1:
#
# 输入: nums = [5,7,7,8,8,10], target = 8
# 输出: 2
# 示例 2:
#
# 输入: nums = [5,7,7,8,8,10], target = 6
# 输出: 0
# 提示：
#
# 0 <= nums.length <= 10^5
# -10^9 <= nums[i] <= 10^9
# nums 是一个非递减数组
# -10^9 <= target <= 10^9
#
# 注意：本题与主站 34 题相同（仅返回值不同）：https://leetcode-cn.com/problems/find-first-
# and-last-position-of-element-in-sorted-array/
#
# @author: Du Ang
# @date: Mar 19, 2023

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
    def search(self, nums: List[int], target: int) -> int:
        i = binary_search(nums, target, leftmost=True)
        if i != len(nums) and nums[i] == target:
            left_bound = i
            right_bound = binary_search(nums, target, leftmost=False)
            return right_bound - left_bound
        else:
            return 0


if __name__ == "__main__":
    nums = [5, 7, 7, 8, 8, 10]
    target = 8
    expected = 2
    solution = Solution()
    out = solution.search(nums, target)
    assert out == expected, "Output {} not equal the expected {}".format(out, expected)
