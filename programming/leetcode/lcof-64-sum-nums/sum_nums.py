# @problem: 剑指 Offer 64. 求1+2+…+n
# @file: sum_nums.py
# @url: https://leetcode-cn.com/problems/qiu-12n-lcof
# @description:
#
# 求 1+2+...+n
# ，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。
# 示例 1：
# 输入: n = 3
# 输出: 6
#
# 示例 2：
# 输入: n = 9
# 输出: 45
#
# 限制：
#
# 1 <= n <= 10000
#
# @author: Du Ang
# @date: Jun 28, 2023


class Solution:
    """使用 sum 函数"""

    def sumNums(self, n: int) -> int:
        return sum(range(n + 1))
