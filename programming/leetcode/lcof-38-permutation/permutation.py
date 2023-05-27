# @problem: 剑指 Offer 38. 字符串的排列
# @file: permutation.py
# @url: https://leetcode-cn.com/problems/zi-fu-chuan-de-pai-lie-lcof
# @description:
#
# 输入一个字符串，打印出该字符串中字符的所有排列。
# 你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。
# 示例:
# 输入：s = "abc"
# 输出：["abc","acb","bac","bca","cab","cba"]
#
# 限制：
# 1 <= s 的长度 <= 8
#
# @author: Du Ang
# @date: May 20, 2023

from typing import List


class Solution1:
    """DFS + Backtracking"""

    def _dfs(self, s: str, depth: int, path: List[str]) -> None:
        if depth == len(s):
            self.res.append("".join(path))
            return

        for char, count in self.visited.items():
            if count > 0:
                # 更改状态变量，准备遍历更深一层
                self.visited[char] = count - 1
                path.append(char)
                # 开始遍历更深一层
                self._dfs(s, depth + 1, path)
                # 从深层节点回溯到浅层节点，并将状态恢复到浅层节点对应的状态
                path.pop(-1)
                self.visited[char] = count

    def permutation(self, s: str) -> List[str]:
        # 统计 s 中每个字符的出现次数
        self.visited = {}
        for char in s:
            if char not in self.visited:
                self.visited[char] = 1
            else:
                self.visited[char] += 1

        self.res = []
        self._dfs(s, 0, [])
        return self.res


class Solution2:
    """递归交换 + 回溯"""

    def _permutation(self, chars: List[str], start: int) -> None:
        if start == len(chars):
            self.res.append("".join(chars))
        else:
            visited = set()
            for i in range(start, len(chars)):
                if chars[i] in visited:
                    # 保证首个数字没有因为相等而被重复选取
                    continue
                else:
                    visited.add(chars[i])
                if i != start and chars[i] == chars[start]:
                    # 保证后面的数字没有因为相等而被重复交换
                    continue
                chars[start], chars[i] = chars[i], chars[start]
                self._permutation(chars, start + 1)
                chars[start], chars[i] = chars[i], chars[start]

    def permutation(self, s: str) -> List[str]:
        self.res = []
        self._permutation([char for char in s], 0)
        return self.res


class Solution3:
    """排序 + 回溯，去重填空"""

    def _backtrack(self, s: str, i: int, perm: List[int]) -> None:
        if i == len(s):
            self.res.append("".join(perm))
        else:
            for j in range(0, len(s)):
                if self.vis[j]:
                    # 已经填写过
                    continue
                elif j > 0 and (not self.vis[j - 1]) and s[j - 1] == s[j]:
                    # 在存在重复的字符时，保证将重复的字符从左往右依次填入空位
                    # 即对于重复的字符，左边如果还没填写，右边就不能填写
                    continue

                self.vis[j] = True
                perm.append(s[j])
                self._backtrack(s, i + 1, perm)
                perm.pop(-1)
                self.vis[j] = False

    def permutation(self, s: str) -> List[str]:
        s = sorted(s)
        self.vis = [False] * len(s)
        self.res = []
        self._backtrack(s, 0, [])
        return self.res


class Solution:
    """循环调用下一个排列"""

    def next_permutation(self, chars: List[str]) -> bool:
        i = len(chars) - 2

        # 从后向前寻找第一个升序对
        while i >= 0 and chars[i] >= chars[i + 1]:
            i -= 1

        if i < 0:
            # 没有找到升序对，当前已经是最大排列，返回 False
            return False

        j = i + 1
        k = len(chars) - 1
        while k >= j:
            # 在 [j, end) 范围从后向前寻找 A[k] > A[i]，并交换它们
            if chars[k] > chars[i]:
                chars[i], chars[k] = chars[k], chars[i]
                break
            k -= 1

        # 当前 [j, end) 范围一定是降序的，调整为升序
        left = j
        right = len(chars) - 1
        while left < right:
            chars[left], chars[right] = chars[right], chars[left]
            left += 1
            right -= 1

        return True

    def permutation(self, s: str) -> List[str]:
        res = []
        chars = sorted([c for c in s])

        while True:
            res.append("".join(chars))
            if not self.next_permutation(chars):
                break

        return res


if __name__ == "__main__":
    sln = Solution()

    s = "abc"
    out = sln.permutation(s)
    print(f"total permuations: {len(out)}\n{out}")

    s = "aab"
    out = sln.permutation(s)
    print(f"total permuations: {len(out)}\n{out}")

    s = "kzfxxx"
    out = sln.permutation(s)
    print(f"total permuations: {len(out)}\n{out}")
