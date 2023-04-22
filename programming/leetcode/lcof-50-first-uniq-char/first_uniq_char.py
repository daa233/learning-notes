# @problem: 剑指 Offer 50. 第一个只出现一次的字符
# @file: first_uniq_char.py
# @url: https://leetcode-cn.com/problems/di-yi-ge-zhi-chu-xian-yi-ci-de-zi-fu-lcof
# @description:
#
# 在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。 s 只包含小写字母。
# 示例 1:
#
# 输入：s = "abaccdeff"
# 输出：'b'
#
# 示例 2:
#
# 输入：s = ""
# 输出：' '
#
# 限制：
# 0 <= s 的长度 <= 50000
#
# @author: Du Ang
# @date: Apr 22, 2023


class Solution:
    def firstUniqChar(self, s: str) -> str:
        table = {}
        for c in s:
            if c in table:
                table[c] += 1
            else:
                table[c] = 1
        for c, count in table.items():
            if count == 1:
                return c
        return " "
