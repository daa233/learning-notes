# @problem: 剑指 Offer 58 - II. 左旋转字符串
# @file: reverse_left_words.py
# @url: https://leetcode-cn.com/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof
# @description:
#
# 字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数实现字符串左旋转操作的功能。比如，输入字符串"abcdefg"
# 和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。
# 示例 1：
# 输入: s = "abcdefg", k = 2
# 输出: "cdefgab"
#
# 示例 2：
# 输入: s = "lrloseumgh", k = 6
# 输出: "umghlrlose"
#
# 限制：
#
# 1 <= k < s.length <= 10000
#
# @author: Du Ang
# @date: Feb 26, 2023
from typing import List


def gcd(a: int, b: int) -> int:
    """利用辗转相除法求最大公约数"""
    while b != 0:
        temp = b
        b = a % b
        a = temp
    return a


class Solution:
    """环状替换，环的总个数为 gcd(n, k)"""

    def reverseLeftWords(self, s: str, k: int) -> str:
        if not s or k % len(s) == 0:
            return s
        else:
            k = k % len(s)

        chars = [c for c in s]

        for i in range(gcd(k, len(s))):
            self.shift(chars, i, k)

        return "".join(chars)

    def shift(self, chars: "List[str]", start_index: int, k: int) -> None:
        cur = start_index
        temp_char = chars[start_index]
        while True:
            j = (cur + k) % len(chars)
            if j == start_index:
                chars[cur] = temp_char
                break
            chars[cur] = chars[j]
            cur = (cur + k) % len(chars)


class Solution2:
    """环状替换，不计算环的个数，使用 count 计算总的元素数目。"""

    def reverseLeftWords(self, s: str, k: int) -> str:
        if not s or k % len(s) == 0:
            return s
        else:
            k = k % len(s)

        chars = [c for c in s]

        self.count = 0
        i = 0
        while self.count < len(s):
            self.shift(chars, i, k)
            i += 1

        return "".join(chars)

    def shift(self, chars: "List[str]", start_index: int, k: int) -> None:
        cur = start_index
        temp_char = chars[start_index]
        while True:
            j = (cur + k) % len(chars)
            if j == start_index:
                chars[cur] = temp_char
                self.count += 1
                break
            chars[cur] = chars[j]
            self.count += 1
            cur = (cur + k) % len(chars)


class Solution3:
    """字符串拼接，将前面的 k 个字符拷贝到字符串末尾"""

    def reverseLeftWords(self, s: str, k: int) -> str:
        if not s or k % len(s) == 0:
            return s

        k = k % len(s)
        return s[k:] + s[:k]


class Solution4:
    """
    三次反转。
    首先将前 k 个字符翻转，再将后面的 n - k 个字符翻转，最后将整个字符串反转，
    得到的字符串即为所求。
    """

    def reverseLeftWords(self, s: str, k: int) -> str:
        chars = [c for c in s]
        self.reverse(chars, 0, k - 1)
        self.reverse(chars, k, len(s) - 1)
        self.reverse(chars, 0, len(s) - 1)
        return "".join(chars)

    def reverse(self, chars: List, left: int, right: int) -> None:
        while left < right:
            chars[left], chars[right] = chars[right], chars[left]
            left += 1
            right -= 1
