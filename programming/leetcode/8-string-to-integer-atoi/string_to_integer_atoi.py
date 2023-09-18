# @problem: 8. String to Integer (atoi)
# @file: string_to_integer_atoi.py
# @url: https://leetcode-cn.com/problems/string-to-integer-atoi
# @description:
#
# Implement atoi which converts a string to an integer.
# The function first discards as many whitespace characters as necessary
# until the first non-whitespace character is found. Then, starting from
# this character takes an optional initial plus or minus sign followed
# by as many numerical digits as possible, and interprets them as a
# numerical value.
# The string can contain additional characters after those that form the
# integral number, which are ignored and have no effect on the behavior
# of this function.
# If the first sequence of non-whitespace characters in str is not a
# valid integral number, or if no such sequence exists because either
# str is empty or it contains only whitespace characters, no conversion
# is performed.
# If no valid conversion could be performed, a zero value is returned.
# Note:
#
# Only the space character ' ' is considered a whitespace character.
# Assume we are dealing with an environment that could only store
# integers within the 32-bit signed integer range: [−2^31,  2^31 − 1]. If
# the numerical value is out of the range of representable values,
# INT_MAX (2^31 − 1) or INT_MIN (−2^31) is returned.
#
# Example 1:
#
# Input: str = "42"
# Output: 42
#
# Example 2:
#
# Input: str = "   -42"
# Output: -42
# Explanation: The first non-whitespace character is '-', which is the
# minus sign. Then take as many numerical digits as possible, which gets
# 42.
#
# Example 3:
#
# Input: str = "4193 with words"
# Output: 4193
# Explanation: Conversion stops at digit '3' as the next character is
# not a numerical digit.
#
# Example 4:
#
# Input: str = "words and 987"
# Output: 0
# Explanation: The first non-whitespace character is 'w', which is not a
# numerical digit or a +/- sign. Therefore no valid conversion could be
# performed.
#
# Example 5:
#
# Input: str = "-91283472332"
# Output: -2147483648
# Explanation: The number "-91283472332" is out of the range of a 32-bit
# signed integer. Thefore INT_MIN (−2^31) is returned.
#
# Constraints:
#
# 0 <= s.length <= 200
# s consists of English letters (lower-case and upper-case), digits, '
# ', '+', '-' and '.'.
#
# @author: Du Ang
# @date: Oct 05, 2020


class Solution1:
    def myAtoi(self, s: str) -> int:
        num_list = []
        pos_flag = True
        int_max = 2 ** 31 - 1
        int_min = -(2 ** 31)

        s = s.strip()
        if s.startswith("-"):
            pos_flag = False
            s = s[1:]
        elif s.startswith("+"):
            pos_flag = True
            s = s[1:]
        for ch in s:
            if ch >= "0" and ch <= "9":
                num_list.append(int(ch))
            else:
                break
        res = 0
        for n in num_list:
            res = res * 10 + n

        if pos_flag:
            res = min(res, int_max)
        else:
            res = -res
            res = max(res, int_min)

        return res


class Automaton:
    def __init__(self):
        self.state = "start"
        self.sign = 1
        # the keys represent the current state;
        # the values (list) represent the next state when the input char is
        # [white_space, +/-, 0-9, other].
        self.table = {
            "start": ["start", "signed", "in_number", "end"],
            "signed": ["end", "end", "in_number", "end"],
            "in_number": ["end", "end", "in_number", "end"],
            "end": ["end", "end", "end", "end"],
        }

    def get_next_state(self, c):
        state_list = self.table[self.state]
        if c == " ":
            self.state = state_list[0]
        elif c == "+" or c == "-":
            self.state = state_list[1]
            if self.state != "end":
                if c == "+":
                    self.sign = 1
                else:
                    self.sign = -1
        elif c >= "0" and c <= "9":
            self.state = state_list[2]
        else:
            self.state = state_list[3]

        return self.state


class Solution:
    def myAtoi(self, s: str) -> int:
        automaton = Automaton()
        res = 0
        for ch in s:
            state = automaton.get_next_state(ch)
            if state == "in_number":
                res = res * 10 + int(ch)
            elif state == "end":
                break
        res = automaton.sign * res
        res = min(max(res, -(2 ** 31)), 2 ** 31 - 1)

        return res
