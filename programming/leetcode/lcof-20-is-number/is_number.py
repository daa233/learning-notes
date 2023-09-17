# @problem: 剑指 Offer 20. 表示数值的字符串
# @file: is_number.py
# @url: https://leetcode-cn.com/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof
# @description:
#
# 请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
# 数值（按顺序）可以分成以下几个部分：
#
# 若干空格
# 一个 小数 或者 整数
# （可选）一个 'e' 或 'E' ，后面跟着一个 整数
# 若干空格
#
# 小数（按顺序）可以分成以下几个部分：
#
# （可选）一个符号字符（'+' 或 '-'）
# 下述格式之一：
# 至少一位数字，后面跟着一个点 '.'
# 至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
# 一个点 '.' ，后面跟着至少一位数字
#
# 整数（按顺序）可以分成以下几个部分：
#
# （可选）一个符号字符（'+' 或 '-'）
# 至少一位数字
#
# 部分数值列举如下：
#
# ["+100", "5e2", "-123", "3.1416", "-1E-16", "0123"]
#
# 部分非数值列举如下：
#
# ["12e", "1a3.14", "1.2.3", "+-5", "12e+5.4"]
#
# 示例 1：
#
# 输入：s = "0"
# 输出：true
#
# 示例 2：
#
# 输入：s = "e"
# 输出：false
#
# 示例 3：
#
# 输入：s = "."
# 输出：false
# 示例 4：
#
# 输入：s = "    .1  "
# 输出：true
#
# 提示：
#
# 1 <= s.length <= 20
# s 仅含英文字母（大写和小写），数字（0-9），加号 '+' ，减号 '-' ，空格 ' ' 或者点 '.' 。
#
# @author: Du Ang
# @date: Sep 02, 2023

from typing import Tuple

NUMBERS = [str(i) for i in range(10)]


class Solution1:
    def is_integer(self, s: str) -> bool:
        """判断一个字符串是否为整数。默认首尾无空格"""
        if not s:
            return False
        if s.startswith("+") or s.startswith("-"):
            s = s[1:]
        if not s:
            return False
        for c in s:
            if c not in NUMBERS:
                return False
        return True

    def is_decimal(self, s: str) -> bool:
        """判断一个字符串是否为小数。默认首尾无空格"""
        if not s or "." not in s:
            return False

        if s.startswith("+") or s.startswith("-"):
            s = s[1:]

        # 考虑可能包含多个小数点的情况
        try:
            pre, post = s.split(".")
        except:
            return False

        if post.startswith("+") or post.startswith("-"):
            # post 部分不可以包含 "+" 或 "-"
            return False

        if not pre:
            # 小数点前无内容
            # 3. 一个小数点，后面跟着至少一位数字
            return self.is_integer(post)
        elif self.is_integer(pre):
            # 小数点前至少一位数字
            if not post:
                # 1. 至少一位数字，后面跟着一个小数点
                return True
            else:
                # 2. 至少一位数字，后面跟着一个小数点，后面再跟着至少一位数字
                return self.is_integer(post)
        else:
            return False

    def find_e_in_string(self, s: str) -> Tuple[str, int]:
        """判断字符串中是否包含 e 或 E"""
        for i, c in enumerate(s):
            if c == "e" or c == "E":
                return c, i
        return None, -1

    def isNumber(self, s: str) -> bool:
        """判断字符串是否为数值"""
        # 去除首尾空格
        s = s.strip()

        # 判断是否包含 "e/E"
        e, i = self.find_e_in_string(s)
        if e:
            # 若包含 e/E，将其把字符串分为前后两部分，
            # 前部分需要为一个小数或整数，后部分需要为一个整数
            pre, post = s[:i], s[i + 1 :]
            pre_is_valid = self.is_decimal(pre) or self.is_integer(pre)
            post_is_valid = self.is_integer(post)
            return pre_is_valid and post_is_valid
        else:
            # 若不包含 e/E，判断字符串是否为小数或整数
            return self.is_integer(s) or self.is_decimal(s)


from enum import Enum


class State(Enum):
    START_SPACE = 0  # 起始空格
    SIGN = 1  # +/- 符号
    INT = 2  # 整数
    DOT_WITH_LEFT_INT = 3  # 小数点（左有整数）
    DOT_WO_LEFT_INT = 4  # 小数点（左无整数）
    DECIMAL = 5  # 小数部分
    E = 6  # e/E
    POWER_SIGN = 7  # 指数部分 +/- 符号
    POWER = 8  # 指数部分
    END_SPACE = 9  # 末尾空格


class Input(Enum):
    SPACE = 0  # 空格
    SIGN = 1  # +/- 符号
    DIGIT = 2  # 0-9 数字
    DOT = 3  # 小数点
    E = 4  # 指数符号 e/E


class Solution:
    """确定有限状态自动机"""

    def isNumber(self, s: str) -> bool:
        """判断字符串是否为数值"""

        input_key_to_char_dict = {
            Input.SPACE: [" "],
            Input.SIGN: ["+", "-"],
            Input.DIGIT: [str(i) for i in range(10)],
            Input.DOT: ["."],
            Input.E: ["e", "E"],
        }

        input_char_to_key_dict = {}
        for k, values in input_key_to_char_dict.items():
            for v in values:
                if v not in input_char_to_key_dict:
                    input_char_to_key_dict[v] = k

        state_transform = {
            State.START_SPACE: {
                Input.SPACE: State.START_SPACE,
                Input.SIGN: State.SIGN,
                Input.DIGIT: State.INT,
                Input.DOT: State.DOT_WO_LEFT_INT,
            },
            State.SIGN: {
                Input.DIGIT: State.INT,
                Input.DOT: State.DOT_WO_LEFT_INT,
            },
            State.INT: {
                Input.SPACE: State.END_SPACE,
                Input.DIGIT: State.INT,
                Input.DOT: State.DOT_WITH_LEFT_INT,
                Input.E: State.E,
            },
            State.DOT_WITH_LEFT_INT: {
                Input.SPACE: State.END_SPACE,
                Input.DIGIT: State.DECIMAL,
                Input.E: State.E,
            },
            State.DOT_WO_LEFT_INT: {
                Input.DIGIT: State.DECIMAL,
            },
            State.DECIMAL: {
                Input.SPACE: State.END_SPACE,
                Input.DIGIT: State.DECIMAL,
                Input.E: State.E,
            },
            State.E: {
                Input.SIGN: State.POWER_SIGN,
                Input.DIGIT: State.POWER,
            },
            State.POWER_SIGN: {
                Input.DIGIT: State.POWER,
            },
            State.POWER: {
                Input.SPACE: State.END_SPACE,
                Input.DIGIT: State.POWER,
            },
            State.END_SPACE: {
                Input.SPACE: State.END_SPACE,
            },
        }

        state = State.START_SPACE
        for c in s:
            transform = state_transform[state]
            if c not in input_char_to_key_dict:
                return False
            input_key = input_char_to_key_dict[c]
            if input_key in transform:
                state = transform[input_key]
            else:
                return False

        if state in [
            State.INT,
            State.DOT_WITH_LEFT_INT,
            State.DECIMAL,
            State.POWER,
            State.END_SPACE,
        ]:
            return True
        else:
            return False
