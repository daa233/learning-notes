# @problem: 剑指 Offer 12. 矩阵中的路径
# @file: exist.py
# @url: https://leetcode-cn.com/problems/ju-zhen-zhong-de-lu-jing-lcof
# @description:
#
# 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回
# false 。
# 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用
# 。
# 例如，在下面的 3×4 的矩阵中包含单词 "ABCCED"（单词中的字母已标出）。
#
# 示例 1：
#
# 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]],
# word = "ABCCED"
# 输出：true
#
# 示例 2：
#
# 输入：board = [["a","b"],["c","d"]], word = "abcd"
# 输出：false
#
# 提示：
#
# m == board.length
# n = board[i].length
# 1 <= m, n <= 6
# 1 <= word.length <= 15
# board 和 word 仅由大小写英文字母组成
#
# 注意：本题与主站 79 题相同：https://leetcode-cn.com/problems/word-search/
#
# @author: Du Ang
# @date: May 15, 2023
from typing import List


class Solution:
    """回溯"""

    def _backtrack(self, board: List[List[str]], i, j, word: str, mask: List[List[bool]]) -> bool:
        if mask[i][j]:
            return False

        m, n = len(board), len(board[0])
        if board[i][j] == word[0]:
            tail_word = word[1:]
            if not tail_word:
                return True

            mask[i][j] = True
            directions = [(-1, 0), (0, -1), (0, 1), (1, 0)]
            for direction in directions:
                offset_i, offset_j = direction
                new_i, new_j = i + offset_i, j + offset_j
                if 0 <= new_i < m and 0 <= new_j < n:
                    res = self._backtrack(board, new_i, new_j, tail_word, mask)
                    if res:
                        return True
            mask[i][j] = False

        return False

    def _get_match_word(self, board: List[List[str]], word: str) -> bool:
        """
        遍历 board，分别匹配单词的首字母和末尾字母，选择匹配个数少的以减少运行时间。
        根据匹配情况，返回原 word 或翻转后的 word。
        """
        if len(word) == 1:
            return word

        head_match = 0
        tail_match = 0
        for i in range(len(board)):
            for j in range(len(board[0])):
                if board[i][j] == word[0]:
                    head_match += 1
                else:
                    tail_match += 1

        if head_match > tail_match:
            return word[::-1]
        else:
            return word

    def exist(self, board: List[List[str]], word: str) -> bool:
        word = self._get_match_word(board, word)
        mask = [[False] * len(board[0]) for _ in range(len(board))]
        for i in range(len(board)):
            for j in range(len(board[0])):
                res = self._backtrack(board, i, j, word, mask)
                if res:
                    return True
        return False


def check_result(sln: Solution, board: str, word: str, expected: int) -> None:
    out = sln.exist(board, word)
    board_str = "\n".join([" ".join(i) for i in board])
    assert out == expected, (
        f"board: \n{board_str}\nword: {word} \n" + f"out {out} not equal {expected}"
    )


if __name__ == "__main__":
    sln = Solution()

    check_result(
        sln,
        board=[
            ["A", "B", "C", "E"],
            ["S", "F", "C", "S"],
            ["A", "D", "E", "E"],
        ],
        word="ABCCED",
        expected=True,
    )
    check_result(
        sln,
        board=[
            ["a", "b"],
            ["c", "d"],
        ],
        word="ABCCED",
        expected=False,
    )
    check_result(
        sln,
        board=[
            ["A", "B", "C", "E"],
            ["S", "F", "C", "S"],
            ["A", "D", "E", "E"],
        ],
        word="ABCB",
        expected=False,
    )
    check_result(
        sln,
        board=[
            ["A"],
        ],
        word="A",
        expected=True,
    )
