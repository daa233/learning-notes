# @problem: 剑指 Offer 39. 数组中出现次数超过一半的数字
# @file: majority_element.py
# @url: https://leetcode-cn.com/problems/shu-zu-zhong-chu-xian-ci-shu-chao-guo-yi-ban-de-shu-zi-lcof
# @description:
#
# 数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
# 你可以假设数组是非空的，并且给定的数组总是存在多数元素。
# 示例 1:
# 输入: [1, 2, 3, 2, 2, 2, 5, 4, 2]
# 输出: 2
# 限制：
# 1 <= 数组长度 <= 50000
# 注意：本题与主站 169 题相同：https://leetcode-cn.com/problems/majority-element/
#
# @author: Du Ang
# @date: Aug 06, 2023

import random
from typing import List


class Solution1:
    """遍历统计"""

    def majorityElement(self, nums: List[int]) -> int:
        counter = {}
        for num in nums:
            if num in counter:
                counter[num] += 1
            else:
                counter[num] = 1
        max_count = 0
        res = None
        for num, count in counter.items():
            if count > max_count:
                max_count = count
                res = num

        return res


class Solution2:
    """排序统计"""

    def majorityElement(self, nums: List[int]) -> int:
        nums.sort()

        max_count = 0
        res = None

        prev_num = None
        for num in nums:
            if num == prev_num:
                count += 1
            else:
                prev_num = num
                count = 1
            if count > max_count:
                max_count = count
                res = num

        return res


class Solution3:
    """快速选择"""

    def _partition(self, nums: List[int], left: int, right: int) -> int:
        """
        对 [left, right] 区间内的 nums 进行排序，最终返回 pivot 索引。
        所有位于 pivot 左边的数字都比 nums[pivot] 小，所有位于 pivot 右边
        的数字都比 nums[pivot] 大。
        """
        pivot = random.randint(left, right)
        nums[left], nums[pivot] = nums[pivot], nums[left]
        pivot = left
        index = left + 1
        for i in range(left + 1, right + 1):
            if nums[i] < nums[pivot]:
                nums[i], nums[index] = nums[index], nums[i]
                index += 1
        index -= 1
        nums[index], nums[pivot] = nums[pivot], nums[index]

        return index

    def _quick_selection(self, nums: List[int], left: int, right: int, k: int) -> int:
        if left <= right:
            pivot = self._partition(nums, left, right)
            if pivot == k:
                return nums[pivot]
            elif pivot > k:
                return self._quick_selection(nums, left, pivot, k)
            else:
                return self._quick_selection(nums, pivot + 1, right, k)

    def majorityElement(self, nums: List[int]) -> int:
        return self._quick_selection(nums, 0, len(nums) - 1, len(nums) // 2)


class Solution:
    """Boyer-Moore 投票算法"""

    def majorityElement(self, nums: List[int]) -> int:
        candidate = None
        count = 0
        for num in nums:
            if num == candidate:
                count += 1
            elif num != candidate:
                if count == 0:
                    candidate = num
                    count = 1
                else:
                    count -= 1
        return candidate
