# @problem: 剑指 Offer 58 - I. 翻转单词顺序
# @file: reverse_words.py
# @url: https://leetcode-cn.com/problems/fan-zhuan-dan-ci-shun-xu-lcof
# @description:
#
# 输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。为简单起见，标点符号和普通字母一样处理。例如输入字符串"I am a
# student. "，则输出"student. a am I"。
# 示例 1：
# 输入: "the sky is blue"
# 输出: "blue is sky the"
#
# 示例 2：
# 输入: "  hello world!  "
# 输出: "world! hello"
# 解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
#
# 示例 3：
# 输入: "a good   example"
# 输出: "example good a"
# 解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
#
# 说明：
#
# 无空格字符构成一个单词。
# 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
# 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
#
# 注意：本题与主站 151 题相同：https://leetcode-cn.com/problems/reverse-words-in-a-
# string/
# 注意：此题对比原题有改动
#
# @author: Du Ang
# @date: May 13, 2023

from typing import List


class Solution1:
    """split + reverse + join"""

    def reverseWords(self, s: str) -> str:
        words = s.split(" ")
        reverse_words = [word for word in words[::-1] if word]
        return " ".join(reverse_words)


class Solution2:
    """遍历调换"""

    def trim_extra_spaces(self, chars: List[str]) -> List[str]:
        i = 0
        start = 0
        end = -1
        while i < len(chars):
            while i < len(chars) and chars[i] == " ":
                i += 1
            while i < len(chars) and chars[i] != " ":
                chars[start] = chars[i]
                end = start
                start += 1
                i += 1
            # skip the split space
            if i < len(chars):
                chars[start] = chars[i]
                start += 1
                i += 1

        chars = chars[: end + 1]

        return chars

    def reverse(self, chars: List[str], left: int, right: int) -> None:
        if len(chars) == 0:
            return None

        assert left >= 0 and right <= len(chars) - 1 and left <= right
        while left < right:
            chars[left], chars[right] = chars[right], chars[left]
            left += 1
            right -= 1

    def reverse_each_word(self, chars: List[str]) -> None:
        left = 0
        right = 0
        while right < len(chars):
            while right < len(chars) and chars[right] != " ":
                right += 1
            self.reverse(chars, left, right - 1)
            # move to the next word
            left = right + 1
            right = left

    def reverseWords(self, s: str) -> str:
        chars = [c for c in s]

        # trim the extra spaces
        chars = self.trim_extra_spaces(chars)

        # reverse the whole string
        self.reverse(chars, 0, len(chars) - 1)

        # reverse each word
        self.reverse_each_word(chars)

        return "".join(chars)


class Solution:
    """遍历调换 + 优化时间"""

    def reverse(self, chars: List[str], left: int, right: int) -> None:
        if len(chars) == 0:
            return None

        assert left >= 0 and right <= len(chars) - 1 and left <= right
        while left < right:
            chars[left], chars[right] = chars[right], chars[left]
            left += 1
            right -= 1

    def reverse_each_word(self, chars: List[str]) -> List[str]:
        """翻转每个字符串，同时考虑空格的情况"""
        index = 0
        start = 0
        while start < len(chars):
            if chars[start] != " ":
                if index != 0:
                    # 填一个空白字符然后将 index 移动到下一个单词的开头位置
                    chars[index] = " "
                    index += 1

                # 循环遍历至单词的末尾
                end = start
                while end < len(chars) and chars[end] != " ":
                    chars[index] = chars[end]
                    index += 1
                    end += 1

                # 翻转整个单词
                self.reverse(chars, index - (end - start), index - 1)

                # 更新 start，然后去寻找下一个单词
                start = end + 1
            else:
                start += 1

        # 去除无用的尾巴
        chars = chars[:index]

        return chars

    def reverseWords(self, s: str) -> str:
        chars = [c for c in s]

        # reverse the whole string
        self.reverse(chars, 0, len(chars) - 1)

        # reverse each word and consider the spaces
        chars = self.reverse_each_word(chars)

        return "".join(chars)


class Solution:
    """使用栈"""

    def reverseWords(self, s: str) -> str:
        stack = []
        words = []
        for c in s[::-1]:
            if c == " " and stack:
                word = []
                while stack:
                    word.append(stack.pop(-1))
                words.append("".join(word))
            elif c == " " and not stack:
                continue
            else:
                stack.append(c)

        if stack:
            word = []
            while stack:
                word.append(stack.pop(-1))
            words.append("".join(word))

        return " ".join(words)


if __name__ == "__main__":
    sln = Solution()
    print(sln.reverseWords("  hello world!  "))
    print(sln.reverseWords("    "))
    print(sln.reverseWords("the sky is blue"))
