# @problem: 剑指 Offer 67. 把字符串转换成整数
# @file: str_to_int.py
# @url: https://leetcode-cn.com/problems/ba-zi-fu-chuan-zhuan-huan-cheng-zheng-shu-lcof
# @description:
#
# 写一个函数 StrToInt，实现把字符串转换成整数这个功能。不能使用 atoi 或者其他类似的库函数。
# 首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。
# 当我们寻找到的第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字组合起来，作为该整数的正负号；假如第一个非空字符是数字，则直
# 接将其与之后连续的数字字符组合起来，形成整数。
# 该字符串除了有效的整数部分之后也可能会存在多余的字符，这些字符可以被忽略，它们对于函数不应该造成影响。
# 注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换。
# 在任何情况下，若函数不能进行有效的转换时，请返回 0。
# 说明：
# 假设我们的环境只能存储 32 位大小的有符号整数，那么其数值范围为 [−2^31,  2^31 − 1]。如果数值超过这个范围，请返回
#  INT_MAX (2^31 − 1) 或 INT_MIN (−2^31) 。
# 示例 1:
# 输入: "42"
# 输出: 42
#
# 示例 2:
# 输入: "   -42"
# 输出: -42
# 解释: 第一个非空白字符为 '-', 它是一个负号。
#      我们尽可能将负号与后面所有连续出现的数字组合起来，最后得到 -42 。
#
# 示例 3:
# 输入: "4193 with words"
# 输出: 4193
# 解释: 转换截止于数字 '3' ，因为它的下一个字符不为数字。
#
# 示例 4:
# 输入: "words and 987"
# 输出: 0
# 解释: 第一个非空字符是 'w', 但它不是数字或正、负号。
#      因此无法执行有效的转换。
# 示例 5:
# 输入: "-91283472332"
# 输出: -2147483648
# 解释: 数字 "-91283472332" 超过 32 位有符号整数范围。
#      因此返回 INT_MIN (−2^31) 。
#
# 注意：本题与主站 8 题相同：https://leetcode-cn.com/problems/string-to-integer-
# atoi/
#
# @author: Du Ang
# @date: Sep 17, 2023

from enum import Enum


class State(Enum):
    START_SPACE = 0  # 起始空格
    SIGN = 1  # +/- 符号
    INT = 2  # 整数
    START_NON_INT = 3  # 起始非整数字符
    ANY_CHAR_AFTER_INT = 4  # 整数后任意字符


class Input(Enum):
    SPACE = 0  # 空格
    SIGN = 1  # +/- 符号
    DIGIT = 2  # 0-9 数字
    OTHER = 3  # 小数点


input_key_to_char_dict = {
    Input.SPACE: [" "],
    Input.SIGN: ["+", "-"],
    Input.DIGIT: [str(i) for i in range(10)],
}

INT_MAX = 2147483647
INT_MIN = -2147483648


class Solution:
    """确定有限状态自动机"""

    def strToInt(self, str: str) -> int:

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
                Input.OTHER: State.START_NON_INT,
            },
            State.SIGN: {
                Input.SPACE: State.START_NON_INT,
                Input.SIGN: State.START_NON_INT,
                Input.DIGIT: State.INT,
                Input.OTHER: State.START_NON_INT,
            },
            State.INT: {
                Input.SPACE: State.ANY_CHAR_AFTER_INT,
                Input.SIGN: State.ANY_CHAR_AFTER_INT,
                Input.DIGIT: State.INT,
                Input.OTHER: State.ANY_CHAR_AFTER_INT,
            },
            State.START_NON_INT: {
                Input.SPACE: State.START_NON_INT,
                Input.SIGN: State.START_NON_INT,
                Input.DIGIT: State.START_NON_INT,
                Input.OTHER: State.START_NON_INT,
            },
            State.ANY_CHAR_AFTER_INT: {
                Input.SPACE: State.ANY_CHAR_AFTER_INT,
                Input.SIGN: State.ANY_CHAR_AFTER_INT,
                Input.DIGIT: State.ANY_CHAR_AFTER_INT,
                Input.OTHER: State.ANY_CHAR_AFTER_INT,
            },
        }

        state = State.START_SPACE
        sign = "+"
        total_sum = 0
        for c in str:
            transform = state_transform[state]
            if c not in input_char_to_key_dict:
                input_key = Input.OTHER
            else:
                input_key = input_char_to_key_dict[c]
            state = transform[input_key]
            if state == State.START_SPACE:
                continue
            elif state == State.SIGN:
                sign = c
                continue
            elif state == State.INT:
                d = int(c)
                if sign == "+":
                    if total_sum > INT_MAX / 10:
                        return INT_MAX
                    else:
                        total_sum *= 10
                    if total_sum > INT_MAX - d:
                        return INT_MAX
                    total_sum += int(c)
                else:
                    if total_sum < INT_MIN / 10:
                        return INT_MIN
                    else:
                        total_sum *= 10
                    if total_sum < INT_MIN + d:
                        return INT_MIN
                    total_sum -= int(c)
            elif state == State.ANY_CHAR_AFTER_INT:
                continue
            elif state == State.START_NON_INT:
                return 0

        return total_sum
