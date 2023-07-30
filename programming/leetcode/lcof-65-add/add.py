# @problem: 剑指 Offer 65. 不用加减乘除做加法
# @file: add.py
# @url: https://leetcode-cn.com/problems/bu-yong-jia-jian-cheng-chu-zuo-jia-fa-lcof
# @description:
#
# 写一个函数，求两个整数之和，要求在函数体内不得使用 “+”、“-”、“*”、“/” 四则运算符号。
# 示例:
# 输入: a = 1, b = 1
# 输出: 2
# 提示：
#
# a, b 均可能是负数或 0
# 结果不会溢出 32 位整数
#
# @author: Du Ang
# @date: Jul 23, 2023


class Solution1:
    def add(self, a: int, b: int) -> int:
        MASK1 = 4294967296  # 2^32
        MASK2 = 2147483648  # 2^31
        MASK3 = 2147483647  # 2^31-1

        a %= MASK1
        b %= MASK1
        while b != 0:
            carry = ((a & b) << 1) % MASK1
            a = (a ^ b) % MASK1
            b = carry
        if a & MASK2:  # 负数
            return ~(((a ^ MASK2) ^ MASK3))
        else:  # 正数
            return a


class Solution:
    def add(self, a: int, b: int) -> int:
        MASK1 = 0xFFFFFFFF  # 2^32-1
        MASK2 = 0x7FFFFFFF  # 2^31-1

        a &= MASK1
        b &= MASK1
        while b != 0:
            carry = ((a & b) << 1) & MASK1
            a = a ^ b
            b = carry
        if a <= MASK2:  # 正数
            return a
        else:  # 负数
            # 将 a 的二进制数补码的高于 32位的所有位由 0 变成 1，
            # 则 a 表示的数会变成对应的负数
            return ~(a ^ MASK1)
