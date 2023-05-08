# @problem: 3. Longest Substring Without Repeating Characters
# @file: longest_substring_without_repeating_characters.py
# @url: https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
# @description:
#
# Given a string s, find the length of the longest substring without
# repeating characters.
# Example 1:
#
# Input: s = "abcabcbb"
# Output: 3
# Explanation: The answer is "abc", with the length of 3.
#
# Example 2:
#
# Input: s = "bbbbb"
# Output: 1
# Explanation: The answer is "b", with the length of 1.
#
# Example 3:
#
# Input: s = "pwwkew"
# Output: 3
# Explanation: The answer is "wke", with the length of 3.
# Notice that the answer must be a substring, "pwke" is a subsequence
# and not a substring.
#
# Constraints:
#
# 0 <= s.length <= 5 * 10^4
# s consists of English letters, digits, symbols and spaces.
#
# @author: Du Ang
# @date: May 07, 2023


class Solution1:
    """滑动窗口"""

    def lengthOfLongestSubstring(self, s: str) -> int:
        window = []
        max_count = 0
        for c in s:
            if c not in window:
                window.append(c)
                if len(window) > max_count:
                    max_count = len(window)
            else:
                window.append(c)
                repeat_index = window.index(c)
                while repeat_index >= 0:
                    window.pop(0)
                    repeat_index -= 1
        return max_count


class Solution:
    """滑动窗口 + 哈希表 + 双指针"""

    def lengthOfLongestSubstring(self, s: str) -> int:
        hash_table = {}
        max_count = 0
        left = 0
        right = 0
        while right < len(s):
            ch = s[right]
            if ch in hash_table:
                # ch in hash_table
                index = hash_table[ch]
                if index >= left and index <= right:
                    # ch not in the sliding window, add it to the sliding window
                    hash_table[ch] = right
                    # update the sliding window range to [index+1, right]
                    left = index + 1
                    right += 1  # step to next char
                    continue

            # ch not in hash_table, or ch in hash_table but not in sliding window
            hash_table[ch] = right
            count = right - left + 1
            if count > max_count:
                max_count = count

            right += 1  # step to next char

        return max_count


class Solution2:
    """动态规划"""

    def lengthOfLongestSubstring(self, s: str) -> int:
        hash_table = {}
        cur_len = 0
        max_len = 0

        for i, ch in enumerate(s):
            if ch not in hash_table:
                # f(i) = f(i-1) + 1
                cur_len += 1
            else:
                # ch is already in the hash_table
                prev_index = hash_table[ch]
                if i - prev_index > cur_len:
                    # previous ch not in the f(i-1)'s substring, f(i) = f(i-1) + 1
                    cur_len += 1
                else:
                    # previous ch in the f(i-1)'s substring, f(i) = d
                    cur_len = i - prev_index

            # update the ch's index in hash_table
            hash_table[ch] = i
            if cur_len > max_len:
                max_len = cur_len

        return max_len


def check_result(inp: str, expected: int) -> None:
    out = sln.lengthOfLongestSubstring(inp)
    assert out == expected, f"inp {inp}, out {out} not equal {expected}"


if __name__ == "__main__":
    sln = Solution2()

    check_result("aab", 2)
    check_result("abcabcbb", 3)
