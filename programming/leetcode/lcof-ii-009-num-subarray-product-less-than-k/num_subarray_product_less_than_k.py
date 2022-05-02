# @problem: 剑指 Offer II 009. 乘积小于 K 的子数组
# @file: num_subarray_product_less_thak_k.py
# @url: https://leetcode-cn.com/problems/ZVAVXX
# @description:
#
# 给定一个正整数数组 nums和整数 k ，请找出该数组内乘积小于 k 的连续的子数组的个数。
# 示例 1:
#
# 输入: nums = [10,5,2,6], k = 100
# 输出: 8
# 解释: 8 个乘积小于 100 的子数组分别为: [10], [5], [2], [6], [10,5], [5,2], [2,6],
# [5,2,6]。
# 需要注意的是 [10,5,2] 并不是乘积小于100的子数组。
#
# 示例 2:
#
# 输入: nums = [1,2,3], k = 0
# 输出: 0
# 提示:
#
# 1 <= nums.length <= 3 * 10^4
# 1 <= nums[i] <= 1000
# 0 <= k <= 106
#
# 注意：本题与主站 713 题相同：https://leetcode-cn.com/problems/subarray-product-
# less-than-k/
#
# @author: Du Ang
# @date: Apr 16, 2022

from typing import List, Tuple


class Solution1:
    """暴力解法，直接双重循环求所有子集的积。并通过记录 max_prod 进行简单的优化。
    在第一层循环跑完一次时，记录全局最大的积 max_prod，若 max_prod < k，则直接返回所有连续
    子数组子集数目 n*(n+1)/2。
    时间复杂度：O(n^2)
    空间复杂度：O(1)
    """

    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        count = 0
        max_prod = -1

        for i in range(len(nums)):
            prod = 1
            for j in range(i, len(nums)):
                prod = prod * nums[j]

                if i == 0 and j == len(nums) - 1:
                    max_prod = prod

                if prod < k:
                    count += 1
                else:
                    break

            if max_prod != -1 and max_prod < k:
                # max product is less than k, return the num of all subarray
                return (len(nums) * (len(nums) + 1)) // 2

        return count


class Solution2:
    """双指针法。当一个子数组的积小于 k 时，则该子数组的所有子数组积都是小于 k 的，此时可以直
    接计算出该子数组满足条件的子集数目 n*(n+1)/2。但是，当指针移动到下一个子数组时，计算的子集
    数目可能会和上一个子数组有交集，交集的这部分子集数目重复计数了，需要减掉重复的数目。
    时间复杂度：O(n)
    空间复杂度：O(n)（可以优化到 O(1)）
    """

    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        left = 0
        right = 0
        prod = 1

        count_list = []

        while left < len(nums):
            if prod < k:
                prod *= nums[right]
                if prod >= k:
                    count_list.append((left, right - 1))
                right += 1
                if right == len(nums) and prod < k:
                    count_list.append((left, right - 1))
                    break
            else:
                prod = prod // nums[left]
                left += 1
                if right == len(nums) and prod < k:
                    count_list.append((left, right - 1))
                    break

        return self.calc_count_list(count_list)

    def calc_count_list(self, count_list: List[Tuple[int]]) -> int:
        res = 0
        prev = None

        for current in count_list:

            if prev is None:
                prev = current
                res += self.get_subarray_num(prev[0], prev[1])
            else:
                if current[0] > prev[0] and current[0] <= prev[1]:
                    res += self.get_subarray_num(current[0], current[1])
                    res -= self.get_subarray_num(current[0], prev[1])
                    prev = (prev[0], current[1])
                elif current[0] > prev[1]:
                    res += self.get_subarray_num(current[0], current[1])
                    prev = current

        return res

    def get_subarray_num(self, start: int, end: int) -> int:
        n = end - start + 1
        return n * (n + 1) // 2


class Solution:
    """双指针法。和上面的双指针法类似，但是计算子集的数目方式不同。
    遍历所有子集（对应 left 起始、right 终止），每个子集对应的数目是 right - left + 1。
    时间复杂度：O(n)
    空间复杂度：O(1)
    """

    def numSubarrayProductLessThanK(self, nums: List[int], k: int) -> int:
        left = 0
        right = 0
        prod = 1
        count = 0
        for right in range(len(nums)):
            prod *= nums[right]
            while left <= right and prod >= k:
                prod = prod // nums[left]
                left += 1
            if left <= right:
                count += right - left + 1
        return count


if __name__ == "__main__":
    nums = [10, 5, 2, 6]
    k = 100
    result = Solution().numSubarrayProductLessThanK(nums=nums, k=k)
    print(result)
