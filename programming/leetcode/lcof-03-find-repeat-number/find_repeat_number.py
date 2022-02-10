# @problem: 剑指 Offer 03. 数组中重复的数字
# @file: find_repeat_number.py
# @url: https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof
# @description:
#
# 找出数组中重复的数字。
#
# 在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1
# 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
# 示例 1：
# 输入：
# [2, 3, 1, 0, 2, 5, 3]
# 输出：2 或 3
#
# 限制：
# 2 <= n <= 100000
#
# @author: Du Ang
# @date: Jan 17, 2021

from typing import List


class Solution1:
    """
    对数组中所有元素排序，遍历所有元素，从有序的数组中找到重复的数字。

    时间复杂度：O(nlog(n))
    空间复杂度：O(1)（不新开辟数组，若新开辟数组则为 O(n)）
    """

    def findRepeatNumber(self, nums: List[int]) -> int:
        nums.sort()
        for i in range(1, len(nums)):
            last = nums[i - 1]
            if nums[i] == last:
                return last


class Solution2:
    """
    哈希表解法，用 一个集合（`HashSet`）存储已经遍历过的数字，当新遇到的数字
    已经在集合中时，则为重复的数字，返回它。

    时间复杂度：O(n)
    空间复杂度：O(n)
    """

    def findRepeatNumber(self, nums: List[int]) -> int:
        found_nums = set()
        for num in nums:
            if num in found_nums:
                return num
            else:
                found_nums.add(num)


class Solution:
    """
    注意到数值的范围在0到n-1，如果允许修改输入，则可以将输入数组作为一个 `HashSet` 处理。
    从前往后依次将元素的值作为 `HashSet` 的 key，将元素交换到对应的位置。
    - 遍历数组 nums，判断 nums[i] 是否和 i 相等
    - 若相等，则 i 加1，继续遍历；否则，判断 nums[i] 和 nums[nums[i]] 是否相等，若相等，
      则返回重复元素 nums[i]，否则交换二者，继续判断
    - 若i达到数组长度，退出遍历

    时间复杂度：O(n)
        - 遍历数组一遍 O(n)，`HashSet` 添加元素复杂度 O(1)，总复杂度 O(n)。
    空间复杂度：O(n)
        - 最快情况时所有元素都将存储到集合，空间复杂度 O(n)。
    """

    def findRepeatNumber(self, nums: List[int]) -> int:
        i = 0
        while i < len(nums):
            if i == nums[i]:
                i += 1
            elif nums[i] == nums[nums[i]]:
                break
            else:
                temp = nums[i]
                nums[i] = nums[nums[i]]
                nums[temp] = temp
        return nums[i]
