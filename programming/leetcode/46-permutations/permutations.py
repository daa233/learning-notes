# @problem: 46. Permutations
# @file: permutations.py
# @url: https://leetcode-cn.com/problems/permutations
# @description:
#
# Given an array nums of distinct integers, return all the possible
# permutations. You can return the answer in any order.
# Example 1:
# Input: nums = [1,2,3]
# Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
# Example 2:
# Input: nums = [0,1]
# Output: [[0,1],[1,0]]
# Example 3:
# Input: nums = [1]
# Output: [[1]]
#
# Constraints:
#
# 1 <= nums.length <= 6
# -10 <= nums[i] <= 10
# All the integers of nums are unique.
#
# @author: Du Ang
# @date: May 20, 2023

from typing import List


class Solution1:
    """DFS + Backtracking"""

    def _dfs(self, nums: List[int], depth: int, path: List[int]) -> None:
        if depth == len(nums):
            self.res.append(path[:])
            return

        for i, num in enumerate(nums):
            if not self.visited[i]:
                # 更改状态变量，准备遍历更深一层
                self.visited[i] = True
                path.append(num)
                # 开始遍历更深一层
                self._dfs(nums, depth + 1, path)
                # 从深层节点回溯到浅层节点，并将状态恢复到浅层节点对应的状态
                path.pop(-1)
                self.visited[i] = False

    def permute(self, nums: List[int]) -> List[List[int]]:
        self.visited = [False for _ in range(len(nums))]
        self.res = []
        self._dfs(nums, 0, [])
        return self.res


class Solution:
    """递归交换 + 回溯"""

    def _permute(self, nums: List[int], start: int) -> None:
        if start == len(nums):
            self.res.append(nums[:])
        else:
            for i in range(start, len(nums)):
                nums[start], nums[i] = nums[i], nums[start]
                self._permute(nums, start + 1)
                nums[start], nums[i] = nums[i], nums[start]

    def permute(self, nums: List[int]) -> List[List[int]]:
        self.res = []
        self._permute(nums, 0)
        return self.res


if __name__ == "__main__":
    sln = Solution()

    nums = [1, 2, 3]
    out = sln.permute(nums)
    print(f"total permuations: {len(out)}\n{out}")
