# @problem: 剑指 Offer 46. 把数字翻译成字符串
# @file: translate_num.py
# @url: https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof
# @description:
#
# 给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成
# “z”。一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。
# 示例 1:
# 输入: 12258
# 输出: 5
# 解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"
# 提示：
#
# 0 <= num < 2^31
#
# @author: Du Ang
# @date: May 05, 2023

from typing import List


def convert_num_to_digits(num: int) -> List[int]:
    if num == 0:
        return [0]
    digits = []
    while num > 0:
        digits.insert(0, num % 10)
        num = num // 10
    return digits


class Solution1:
    """动态规划，记忆表法"""

    def count(self, digits: List[int], i: int) -> int:
        if self.dp[i] != 0:
            return self.dp[i]

        if i <= 0:
            # 仅1个数字，有1种翻译方法
            v = 1
        else:
            # 新增一个字母时，默认不增加翻译方法种数
            v = self.count(digits, i - 1)
            # 如果新增的字母和前一个字母能够连成新的字母，
            # 增加 self.count(digits, i-2) 种方法
            ch = digits[i - 1] * 10 + digits[i]
            if ch >= 10 and ch <= 25:
                v += self.count(digits, i - 2)

        self.dp[i] = v

        return v

    def translateNum(self, num: int) -> int:
        digits = convert_num_to_digits(num)
        self.dp = [0] * len(digits)

        return self.count(digits, len(digits) - 1)


class Solution:
    """动态规划，表格法"""

    def translateNum(self, num: int) -> int:
        digits = convert_num_to_digits(num)

        cur_count = 0
        prev1_count = 0
        prev2_count = 0
        for i in range(len(digits)):
            if i == 0:
                cur_count = 1
            else:
                cur_count = prev1_count
                # 如果新增的字母和前一个字母能够连成新的字母，增加 dp[i-2] 种方法
                ch = digits[i - 1] * 10 + digits[i]
                if ch >= 10 and ch <= 25:
                    if i == 1:
                        cur_count += 1
                    else:
                        cur_count += prev2_count

            prev2_count = prev1_count
            prev1_count = cur_count

        return cur_count


if __name__ == "__main__":
    sln = Solution()

    out = sln.translateNum(12)
    expected = 2
    assert out == expected, f"out {out} not equal {expected}"

    out = sln.translateNum(122)
    expected = 3
    assert out == expected, f"out {out} not equal {expected}"

    out = sln.translateNum(1225)
    expected = 5
    assert out == expected, f"out {out} not equal {expected}"

    out = sln.translateNum(12258)
    expected = 5
    assert out == expected, f"out {out} not equal {expected}"

    out = sln.translateNum(25)
    expected = 2
    assert out == expected, f"out {out} not equal {expected}"

    out = sln.translateNum(506)
    expected = 1
    assert out == expected, f"out {out} not equal {expected}"

    out = sln.translateNum(220)
    expected = 3
    assert out == expected, f"out {out} not equal {expected}"
