# @problem: 剑指 Offer 42. 连续子数组的最大和
# @file: max_sub_array.py
# @url: https://leetcode-cn.com/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof
# @description:
#
# 输入一个整型数组，数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。
# 要求时间复杂度为O(n)。
# 示例1:
# 输入: nums = [-2,1,-3,4,-1,2,1,-5,4]
# 输出: 6
# 解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
# 提示：
#
# 1 <= arr.length <= 10^5
# -100 <= arr[i] <= 100
#
# 注意：本题与主站 53 题相同：https://leetcode-cn.com/problems/maximum-subarray/
#
# @author: Du Ang
# @date: May 01, 2023

import sys
from typing import List


class Solution1:
    """动态规划"""

    def maxSubArray(self, nums: List[int]) -> int:
        if not nums:
            return 0

        # 使用 dp 表示截止到 i 位置的所有子数组的和的最大值
        dp = [0] * len(nums)
        dp[0] = nums[0]
        for i, num in enumerate(nums[1:], start=1):
            dp[i] = max((dp[i - 1] + num), num)

        return max(dp)


class Solution:
    """动态规划，优化存储"""

    def maxSubArray(self, nums: List[int]) -> int:
        if not nums:
            return 0

        # 使用 cur_sum 表示截止到 i 位置的所有子数组的和的最大值
        cur_sum = nums[0]
        max_sum = nums[0]
        for num in nums[1:]:
            if cur_sum < 0:
                # 此前的子数组累加和为负值，可直接抛弃，否则会让新的子数组累积和更小
                cur_sum = num
            else:
                cur_sum += num
            if cur_sum > max_sum:
                max_sum = cur_sum

        return max_sum


class Solution2:
    """分治法"""

    def maxSubArray(self, nums: List[int]) -> int:
        if not nums:
            return 0
        return self._maxSubArraySum(nums, 0, len(nums) - 1)

    def _maxCrossSum(self, nums: List[int], left: int, mid: int, right: int) -> int:
        """求在 [left, right] 区间，且必须包含 nums[mid] 的子数组对应的最大和"""

        # the max sum for subarray in range [left, mid], which ends with mid index
        left_sum = -sys.maxsize
        s = 0
        for i in range(mid, left - 1, -1):
            s += nums[i]
            if s > left_sum:
                left_sum = s

        # the max sum for subarray in range [mid+1, right], which starts with mid index
        right_sum = -sys.maxsize
        s = 0
        for i in range(mid + 1, right + 1, 1):
            s += nums[i]
            if s > right_sum:
                right_sum = s

        return max(left_sum + right_sum, left_sum, right_sum)

    def _maxSubArraySum(self, nums: List[int], left: int, right: int) -> int:
        """
        求在 [left, right] 区间子数组对应的最大和，包含三种情况：
            a. 子数组最大和出现在 [left, mid] 区间
            b. 子数组最大和出现在 [mid+1, right] 区间
            c. 子数组最大和出现在 [left, right] 区间，且包含 nums[mid]
        最终结果，[left, right] 区间子数组对应的最大和则是三种情况中和最大的情况。
        """

        assert left <= right

        if left == right:
            return nums[left]

        mid = left + (right - left) // 2
        return max(
            self._maxSubArraySum(nums, left, mid),
            self._maxSubArraySum(nums, mid + 1, right),
            self._maxCrossSum(nums, left, mid, right),
        )


class Node:
    """用来表示一个区间对应的信息"""

    def __init__(
        self,
        max_sum: int,
        max_prefix_sum: int,
        max_suffix_sum: int,
        total_sum: int,
    ) -> None:
        self.max_sum = max_sum  # 子数组最大和
        self.max_prefix_sum = max_prefix_sum  # 左端点开始的子数组最大前缀和
        self.max_suffix_sum = max_suffix_sum  # 右端点结束的子数组最大后缀和
        self.total_sum = total_sum  # 整个区间的所有元素和


class Solution3:
    """分治法，优化为 O(n) 时间复杂度"""

    def merge(self, left: Node, right: Node) -> Node:
        max_sum = max(
            left.max_sum,
            right.max_sum,
            left.max_suffix_sum + right.max_prefix_sum,
        )
        max_prefix_sum = max(
            left.max_prefix_sum,
            left.total_sum + right.max_prefix_sum,
        )
        max_suffix_sum = max(right.max_suffix_sum, left.max_suffix_sum + right.total_sum)
        total_sum = left.total_sum + right.total_sum
        return Node(
            max_sum=max_sum,
            max_prefix_sum=max_prefix_sum,
            max_suffix_sum=max_suffix_sum,
            total_sum=total_sum,
        )

    def get(self, nums: List[int], left: int, right: int) -> Node:
        assert left <= right

        if left == right:
            return Node(
                max_sum=nums[left],
                max_prefix_sum=nums[left],
                max_suffix_sum=nums[left],
                total_sum=nums[left],
            )
        else:
            mid = left + (right - left) // 2
            return self.merge(
                self.get(nums, left, mid),
                self.get(nums, mid + 1, right),
            )

    def maxSubArray(self, nums: List[int]) -> int:
        if not nums:
            return 0
        return self.get(nums, 0, len(nums) - 1).max_sum
