# @problem: 剑指 Offer 11. 旋转数组的最小数字
# @file: min_array.py
# @url: https://leetcode-cn.com/problems/xuan-zhuan-shu-zu-de-zui-xiao-shu-zi-lcof
# @description:
#
# 把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
# 给你一个可能存在 重复 元素值的数组 numbers ，它原来是一个升序排列的数组，并按上述情形进行了一次旋转。请返回旋转数组的最小元素。例
# 如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一次旋转，该数组的最小值为 1。
# 注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1],
# a[2], ..., a[n-2]] 。
# 示例 1：
#
# 输入：numbers = [3,4,5,1,2]
# 输出：1
#
# 示例 2：
#
# 输入：numbers = [2,2,2,0,1]
# 输出：0
#
# 提示：
#
# n == numbers.length
# 1 <= n <= 5000
# -5000 <= numbers[i] <= 5000
# numbers 原来是一个升序排序的数组，并进行了 1 至 n 次旋转
#
# 注意：本题与主站 154 题相同：https://leetcode-cn.com/problems/find-minimum-in-
# rotated-sorted-array-ii/
#
# @author: Du Ang
# @date: Apr 09, 2023

from typing import List


class Solution:
    def minArray(self, numbers: List[int]) -> int:
        left = 0
        right = len(numbers) - 1

        while left < right:
            mid = left + (right - left) // 2
            if numbers[mid] > numbers[right]:
                left = mid + 1
            elif numbers[mid] < numbers[right]:
                right = mid
            else:
                # 此时 number[mid] == numbers[right]，无法确定最小值在左右哪个区间，
                # 但是可以确定 numbers[mid] 可以替换 numbers[right]，因此通过 right -= 1缩小区间
                right -= 1

        return numbers[left]


if __name__ == "__main__":
    solution = Solution()

    nums = [3, 4, 5, 1, 2]
    out = solution.minArray(nums)
    assert out == 1, f"out {out}"

    nums = [2, 2, 2, 0, 1]
    out = solution.minArray(nums)
    assert out == 0, f"out {out}"

    nums = [0]
    out = solution.minArray(nums)
    assert out == 0, f"out {out}"

    nums = [3, 1]
    out = solution.minArray(nums)
    assert out == 1, f"out {out}"

    nums = [2, 2, 2, 2, 1]
    out = solution.minArray(nums)
    assert out == 1, f"out {out}"
