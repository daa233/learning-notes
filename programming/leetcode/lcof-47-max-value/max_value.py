# @problem: 剑指 Offer 47. 礼物的最大价值
# @file: max_value.py
# @url: https://leetcode-cn.com/problems/li-wu-de-zui-da-jie-zhi-lcof
# @description:
#
# 在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者
# 向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？
# 示例 1:
# 输入:
# [
#   [1,3,1],
#   [1,5,1],
#   [4,2,1]
# ]
# 输出: 12
# 解释: 路径 1→3→5→2→1 可以拿到最多价值的礼物
# 提示：
#
# 0 < grid.length <= 200
# 0 < grid[0].length <= 200
#
# @author: Du Ang
# @date: May 05, 2023

from typing import List


class Solution1:
    """动态规划，记忆表法"""

    def _get(self, grid: List[List[int]], i: int, j: int) -> int:
        m = len(grid)
        n = len(grid[0])

        if i < 0 or i >= m:
            return 0
        if j < 0 or j >= n:
            return 0

        if self.dp[i][j] != -1:
            return self.dp[i][j]

        value = grid[i][j] + max(self._get(grid, i - 1, j), self._get(grid, i, j - 1))
        self.dp[i][j] = value

        return value

    def maxValue(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])
        self.dp = [[-1] * n for _ in range(m)]

        return self._get(grid, m - 1, n - 1)


class Solution:
    """动态规划，表格法"""

    def maxValue(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])
        dp = [[0] * n for _ in range(m)]

        for i in range(m):
            for j in range(n):
                if i > 0:
                    dp[i][j] = max(dp[i][j], dp[i - 1][j])
                if j > 0:
                    dp[i][j] = max(dp[i][j], dp[i][j - 1])
                dp[i][j] += grid[i][j]

        return dp[m - 1][n - 1]
