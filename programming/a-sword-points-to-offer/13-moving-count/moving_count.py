# -*- coding:utf-8 -*-
# 题目描述
# 地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，
# 右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大于k的格子。
# 例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7=18。但是，它不
# 能进入方格（35,38），因为3+5+3+8=19。请问该机器人能够达到多少个格子？

class Solution:
    def movingCount(self, threshold, rows, cols):
        # write code here
        visited = [[0 for j in range(cols)] for i in range(rows)]
        self.count = 0
        self.move_check(threshold, rows, cols, visited, 0, 0)
        return self.count

    def move_check(self, threshold, rows, cols, visited, i, j):
        if visited[i][j] == 0 and self.check_sum(i, j, threshold):
            # can be visited
            visited[i][j] = 1   # set to already visited
            self.count += 1
            if i - 1 > 0:
                self.move_check(threshold, rows, cols, visited, i-1, j)
            if j - 1 > 0:
                self.move_check(threshold, rows, cols, visited, i, j-1)
            if i + 1 < rows:
                self.move_check(threshold, rows, cols, visited, i+1, j)
            if j + 1 < cols:
                self.move_check(threshold, rows, cols, visited, i, j+1)
            return
        else:
            # can't be visited
            visited[i][j] = 1
            return

    def check_sum(self, i, j, threshold):
        if self.digits_sum(i) + self.digits_sum(j) > threshold:
            return False
        else:
            return True

    def digits_sum(self, n):
        s = 0
        while n > 0:
            s += n % 10
            n //= 10
        return s


if __name__ == "__main__":
    threshold = 10
    rows = 10
    cols = 10
    print(Solution().movingCount(threshold, rows, cols))