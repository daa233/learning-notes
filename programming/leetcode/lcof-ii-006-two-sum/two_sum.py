# @problem: 剑指 Offer II 006. 排序数组中两个数字之和
# @file: two_sum.py
# @url: https://leetcode-cn.com/problems/kLl5u1
# @description:
#
# 给定一个已按照 升序排列  的整数数组 numbers ，请你从数组中找出两个数满足相加之和等于目标数 target 。
# 函数应该以长度为 2 的整数数组的形式返回这两个数的下标值。numbers 的下标 从 0 开始计数 ，所以答案数组应当满足 0 <=
# answer[0] < answer[1] < numbers.length 。
# 假设数组中存在且只存在一对符合条件的数字，同时一个数字不能使用两次。
# 示例 1：
#
# 输入：numbers = [1,2,4,6,10], target = 8
# 输出：[1,3]
# 解释：2 与 6 之和等于目标数 8 。因此 index1 = 1, index2 = 3 。
#
# 示例 2：
#
# 输入：numbers = [2,3,4], target = 6
# 输出：[0,2]
#
# 示例 3：
#
# 输入：numbers = [-1,0], target = -1
# 输出：[0,1]
#
# 提示：
#
# 2 <= numbers.length <= 3 * 10^4
# -1000 <= numbers[i] <= 1000
# numbers 按 递增顺序 排列
# -1000 <= target <= 1000
# 仅存在一个有效答案
#
# 注意：本题与主站 167 题相似（下标起点不同）：https://leetcode-cn.com/problems/two-sum-ii-
# input-array-is-sorted/
#
# @author: Du Ang
# @date: Mar 08, 2022

from typing import List


class Solution1:
    """
    使用哈希表 S，从头到尾遍历数组，不断将 target 与遍历的数字之差以及遍历数字的位置
    放入 S 中，当数组中的数字与哈希表 S 存在重叠时，说明找到了结果。
    """

    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        d = dict()
        for i, num in enumerate(numbers):
            if num in d:
                return [d[num], i]
            else:
                diff = target - num
                d[diff] = i


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
                return [pi, pj]
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
                    return [i, mid]
                elif numbers[mid] > diff:
                    high = mid - 1
                else:
                    low = low + 1
