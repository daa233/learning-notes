# @problem: 剑指 Offer 05. 替换空格
# @file: replace_space.py
# @url: https://leetcode-cn.com/problems/ti-huan-kong-ge-lcof
# @description:
#
# 请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
# 示例 1：
# 输入：s = "We are happy."
# 输出："We%20are%20happy."
# 限制：
# 0 <= s 的长度 <= 10000
#
# @author: Du Ang
# @date: Feb 10, 2022


class Solution1:
    """
    直接在 Python 中调用 `str.replace` 方法
    时间复杂度：O(n)
    空间复杂度：O(n)
    """

    def replaceSpace(self, s: str) -> str:
        return s.replace(" ", "%20")


class Solution:
    """
    不用 Python 内置函数，自己实现。遍历 s，计算空格数目，计算替换后的目标字符串长度，
    然后按字符拷贝。需要注意，Python 中字符串不支持单个字符赋值。
    时间复杂度：O(n)
    空间复杂度：O(n)
    """

    def replaceSpace(self, s: str) -> str:
        _old = " "
        _new = "%20"

        dst_list = []
        for c in s:
            if c == _old:
                dst_list.append(_new)
            else:
                dst_list.append(c)

        return "".join(dst_list)
