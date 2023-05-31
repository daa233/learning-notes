# @problem: 剑指 Offer 61. 扑克牌中的顺子
# @file: is_straight.py
# @url: https://leetcode-cn.com/problems/bu-ke-pai-zhong-de-shun-zi-lcof
# @description:
#
# 从若干副扑克牌中随机抽 5
# 张牌，判断是不是一个顺子，即这5张牌是不是连续的。2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王为 0
# ，可以看成任意数字。A 不能视为 14。
# 示例 1:
#
# 输入: [1,2,3,4,5]
# 输出: True
# 示例 2:
#
# 输入: [0,0,1,2,5]
# 输出: True
# 限制：
# 数组长度为 5
# 数组的数取值为 [0, 13] .
#
# @author: Du Ang
# @date: May 30, 2023

from typing import List


class Solution1:
    def isStraight(self, nums: List[int]) -> bool:
        s = set()
        zeros_count = 0
        min_num = 14
        max_num = -1
        for num in nums:
            if num == 0:
                zeros_count += 1
            else:
                if num in s:
                    return False
                s.add(num)
                if num < min_num:
                    min_num = num
                if num > max_num:
                    max_num = num

        if max_num - min_num <= 4:
            return True
        else:
            return False


class Solution:
    def isStraight(self, nums: List[int]) -> bool:
        nums.sort()
        non_zero_index = 0
        for i in range(len(nums)):
            if nums[i] == 0:
                non_zero_index += 1
                continue
            if i > 0 and nums[i] == nums[i - 1]:
                return False

        if non_zero_index >= len(nums):
            return True
        elif nums[len(nums) - 1] - nums[non_zero_index] <= 4:
            return True
        else:
            return False


def check_result(sln: Solution, nums: List[int], expected: bool) -> None:
    out = sln.isStraight(nums)
    assert out == expected, f"nums: [{nums}], out {out} not equal {expected}"


if __name__ == "__main__":
    sln = Solution()

    nums = [1, 2, 3, 4, 5]
    check_result(sln, nums, True)

    nums = [0, 0, 1, 2, 5]
    check_result(sln, nums, True)

    nums = [0, 0, 0, 0, 0]
    check_result(sln, nums, True)

    nums = [1, 1, 3, 4, 5]
    check_result(sln, nums, False)

    nums = [2, 1, 3, 4, 6]
    check_result(sln, nums, False)
