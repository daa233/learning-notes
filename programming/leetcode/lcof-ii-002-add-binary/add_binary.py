# @problem: 剑指 Offer II 002. 二进制加法
# @file: add_binary.py
# @url: https://leetcode-cn.com/problems/JFETK5
# @description:
#
# 给定两个 01 字符串 a 和 b ，请计算它们的和，并以二进制字符串的形式输出。
# 输入为 非空 字符串且只包含数字 1 和 0。
# 示例 1:
#
# 输入: a = "11", b = "10"
# 输出: "101"
# 示例 2:
#
# 输入: a = "1010", b = "1011"
# 输出: "10101"
# 提示：
#
# 每个字符串仅由字符 '0' 或 '1' 组成。
# 1 <= a.length, b.length <= 10^4
# 字符串如果不是 "0" ，就都不含前导零。
#
# 注意：本题与主站 67 题相同：https://leetcode-cn.com/problems/add-binary/
#
# @author: Du Ang
# @date: Feb 26, 2022


class Solution1:
    """
    直接使用 Python 内置算法。转换为十进制数相加，再转换为二进制数字符串。
    """

    def addBinary(self, a: str, b: str) -> str:
        return bin(int(a, 2) + int(b, 2))[2:]


class Solution:
    """
    实现一个二进制加法器，低位对齐，从低到高依次相加，考虑进位。类似于“归并排序”。
    时间复杂度：O(n)，n = max{|a|, |b|}
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
    时间复杂度：O(|a|+|b|+X⋅max(|a|, |b|))，字符串转化成数字需要的时间代价为
        O(|a| + |b|)，计算的时间代价为 O(max{|a|, |b|})，X 为位运算所需的时间，
        因为这里用到了高精度计算，所以位运算的时间不一定为 O(1)。
    空间复杂度：这里使用了 x 和 y 来保存 a 和 b 的整数形式，如果用 Python 实现，
        这里用到了 Python 的高精度功能，实际的空间代价是 O(|a| + |b|)。
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
