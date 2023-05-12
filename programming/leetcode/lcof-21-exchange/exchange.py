# @problem: 剑指 Offer 21. 调整数组顺序使奇数位于偶数前面
# @file: exchange.py
# @url: https://leetcode-cn.com/problems/diao-zheng-shu-zu-shun-xu-shi-qi-shu-wei-yu-ou-shu-qian-mian-lcof
# @description:
#
# 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数在数组的前半部分，所有偶数在数组的后半部分。
# 示例：
#
# 输入：nums = [1,2,3,4]
# 输出：[1,3,2,4]
# 注：[3,1,2,4] 也是正确的答案之一。
# 提示：
#
# 0 <= nums.length <= 50000
# 0 <= nums[i] <= 10000
#
# @author: Du Ang
# @date: May 11, 2023

from typing import List


class Solution:
    def exchange(self, nums: List[int]) -> List[int]:
        left = 0
        right = len(nums) - 1
        while left < right:
            if nums[left] % 2 == 0 and nums[right] % 2 == 1:
                nums[left], nums[right] = nums[right], nums[left]
            if nums[left] % 2 == 1:
                left += 1
            if nums[right] % 2 == 0:
                right -= 1
        return nums
