# @problem: 42. Trapping Rain Water
# @file: trapping_rain_water.py
# @url: https://leetcode.cn/problems/trapping-rain-water
# @description:
#
# Given n non-negative integers representing an elevation map where the
# width of each bar is 1, compute how much water it can trap after
# raining.
# Example 1:
#
# Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
# Output: 6
# Explanation: The above elevation map (black section) is represented by
# array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water
# (blue section) are being trapped.
#
# Example 2:
#
# Input: height = [4,2,0,3,2,5]
# Output: 9
#
# Constraints:
#
# n == height.length
# 1 <= n <= 2 * 104
# 0 <= height[i] <= 105
#
# @author: Du Ang
# @date: Feb 02, 2025
from typing import List


class Solution1:
    """
    动态规划（两次扫描）
    每个位置能容纳的最大水量应该等于 min(left_max, right_max) - height[i]
    时间复杂度: O(n)
    空间复杂度: O(n)
    """

    def trap(self, height: List[int]) -> int:
        left_max = []
        right_max = []
        lm = 0
        rm = 0
        for i in range(len(height)):
            if height[i] > lm:
                lm = height[i]
            if height[len(height) - i - 1] > rm:
                rm = height[len(height) - i - 1]
            left_max.append(lm)
            right_max.insert(0, rm)
        s = 0
        for i, (lm, rm) in enumerate(zip(left_max, right_max)):
            if min(lm, rm) > height[i]:
                s += min(lm, rm) - height[i]

        return s


class Solution:
    """
    双指针法
    每个位置能容纳的最大水量应该等于 min(left_max, right_max) - height[i]
    左右指针交替移动，哪一侧能依据局部条件求得 min 值，哪一侧计算、移动。
    时间复杂度: O(n)
    空间复杂度: O(1)
    """

    def trap(self, height: List[int]) -> int:
        left = 0
        right = len(height) - 1
        left_max = height[left]
        right_max = height[right]
        s = 0
        while left < right:
            if height[left] > left_max:
                left_max = height[left]
            if height[right] > right_max:
                right_max = height[right]
            if left_max < right_max:
                s += left_max - height[left]
                left += 1
            else:
                s += right_max - height[right]
                right -= 1

        return s


if __name__ == "__main__":
    sol = Solution()
    height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
    print(sol.trap(height))
