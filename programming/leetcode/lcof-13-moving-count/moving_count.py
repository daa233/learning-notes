# @problem: 剑指 Offer 13. 机器人的运动范围
# @file: moving_count.py
# @url: https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof
# @description:
#
# 地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、
# 右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35,
# 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？
# 示例 1：
# 输入：m = 2, n = 3, k = 1
# 输出：3
#
# 示例 2：
# 输入：m = 3, n = 1, k = 0
# 输出：1
#
# 提示：
#
# 1 <= n,m <= 100
# 0 <= k <= 20
#
# @author: Du Ang
# @date: May 16, 2023


def get_digits_sum(n: int) -> int:
    """计算一个数字的各个数位之和"""

    s = 0
    while n > 0:
        s += n % 10
        n = n // 10
    return s


class Solution1:
    """深度优先搜索"""

    def _dfs(self, i: int, j: int) -> int:
        if self.visited[i][j]:
            return 0

        count = 0
        if get_digits_sum(i) + get_digits_sum(j) <= self.k:
            self.visited[i][j] = 1
            count += 1
        else:
            return 0

        directions = [(-1, 0), (0, -1), (0, 1), (1, 0)]
        for direction in directions:
            offset_i, offset_j = direction
            new_i, new_j = i + offset_i, j + offset_j
            if 0 <= new_i < self.m and 0 <= new_j < self.n:
                count += self._dfs(new_i, new_j)

        return count

    def movingCount(self, m: int, n: int, k: int) -> int:
        self.m = m
        self.n = n
        self.k = k
        self.visited = [[0] * n for _ in range(m)]

        count = self._dfs(0, 0)

        return count


class Solution2:
    """广度优先搜索"""

    def movingCount(self, m: int, n: int, k: int) -> int:
        self.m = m
        self.n = n
        self.k = k
        self.visited = [[0] * n for _ in range(m)]
        count = 0

        q = [(0, 0)]
        while q:
            i, j = q.pop(0)

            if self.visited[i][j]:
                continue

            if get_digits_sum(i) + get_digits_sum(j) <= self.k:
                self.visited[i][j] = 1
                count += 1

                directions = [(-1, 0), (0, -1), (0, 1), (1, 0)]
                for direction in directions:
                    offset_i, offset_j = direction
                    new_i, new_j = i + offset_i, j + offset_j
                    if 0 <= new_i < self.m and 0 <= new_j < self.n:
                        q.append((new_i, new_j))

        return count


class Solution3:
    """动态规划：记忆表法"""

    def _check(self, i, j) -> int:
        if self.dp[i][j] != -1:
            return self.dp[i][j]

        if i == 0 and j == 0:
            if get_digits_sum(i) + get_digits_sum(j) <= self.k:
                self.count += 1
                self.dp[i][j] = 1
                return 1
        else:
            left_res, top_res = 0, 0
            if j - 1 >= 0:
                left_res = self._check(i, j - 1)
            if i - 1 >= 0:
                top_res = self._check(i - 1, j)

            if left_res or top_res:
                if get_digits_sum(i) + get_digits_sum(j) <= self.k:
                    self.dp[i][j] = 1
                    self.count += 1
                    return 1

        self.dp[i][j] = 0

        return 0

    def movingCount(self, m: int, n: int, k: int) -> int:
        self.m = m
        self.n = n
        self.k = k
        self.dp = [[-1] * n for _ in range(m)]
        self.count = 0

        self._check(m - 1, n - 1)

        return self.count


class Solution:
    """动态规划：表格法"""

    def _check(self, i: int, j: int) -> None:
        if get_digits_sum(i) + get_digits_sum(j) <= self.k:
            self.visited.add((i, j))
            self.count += 1

    def movingCount(self, m: int, n: int, k: int) -> int:
        self.visited = set()
        self.count = 0
        self.k = k

        for i in range(m):
            for j in range(n):
                if i == 0 and j == 0:
                    self._check(i, j)
                elif (i - 1, j) in self.visited or (i, j - 1) in self.visited:
                    self._check(i, j)

        return self.count


def check_result(sln: Solution, m: int, n: int, k: int, expected: int) -> None:
    out = sln.movingCount(m, n, k)
    assert out == expected, f"m: {m}, n: {n}, k: {k}, out {out} not equal {expected}"


if __name__ == "__main__":
    sln = Solution()

    check_result(sln, m=2, n=3, k=1, expected=3)
    check_result(sln, m=3, n=1, k=0, expected=1)
    check_result(sln, m=1, n=1, k=1, expected=1)
    check_result(sln, m=1, n=1, k=-1, expected=0)
