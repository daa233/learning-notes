# @problem: 67. Add Binary
# @file: add_binary.py
# @url: https://leetcode-cn.com/problems/add-binary
# @description:
#
# Given two binary strings a and b, return their sum as a binary string.
# Example 1:
# Input: a = "11", b = "1"
# Output: "100"
# Example 2:
# Input: a = "1010", b = "1011"
# Output: "10101"
#
# Constraints:
#
# 1 <= a.length, b.length <= 104
# a and b consist only of '0' or '1' characters.
# Each string does not contain leading zeros except for the zero itself.
#
# @author: Du Ang
# @date: Feb 27, 2022


class Solution1:
    """
    直接使用 Python 内置算法。转换为十进制数相加，再转换为二进制数字符串。
    """

    def addBinary(self, a: str, b: str) -> str:
        return bin(int(a, 2) + int(b, 2))[2:]


class Solution:
    """
    实现一个二进制加法器，低位对齐，从低到高依次相加，考虑进位。类似于“归并排序”。
    时间复杂度：O(sizeof(a) + sizeof(b)) = O(n)
    空间复杂度：O(1)，除了答案要占用的空间，额外占用空间是常数级的。
    """

    def addBinary(self, a: str, b: str) -> str:
        if not a or not b:
            return None

        pa = len(a) - 1
        pb = len(b) - 1

        result = []
        c = 0
        while pa >= 0 or pb >= 0:
            if pa < 0:
                va = 0
            else:
                va = int(a[pa])
                pa -= 1
            if pb < 0:
                vb = 0
            else:
                vb = int(b[pb])
                pb -= 1

            s = va + vb + c
            c = 0
            if s >= 2:
                s = s % 2
                c += 1

            result.insert(0, s)

        if c > 0:
            result.insert(0, c)

        result = "".join([str(i) for i in result])

        return result


class Solution2:
    """
    如果不允许使用加减乘除，则可以使用位运算替代上述运算中的一些加减乘除的操作。
        - 把 a 和 b 转换成整型数字 x 和 y，在接下来的过程中，x 保存结果，y 保存进位。
        - 当进位不为 0 时
            - 计算当前 x 和 y 的无进位相加结果：answer = x ^ y （异或）
            - 计算当前 x 和 y 的进位：carry = (x & y) << 1
            - 完成本次循环，更新 x = answer，y = carry
        - 返回 x 的二进制形式
    时间复杂度：
    空间复杂度：
    """

    def addBinary(self, a: str, b: str) -> str:
        if not a or not b:
            return None

        x = int(a, 2)
        y = int(b, 2)

        while y > 0:
            answer = x ^ y  # XOR
            carry = (x & y) << 1
            x = answer
            y = carry

        result = bin(x)[2:]

        return result
