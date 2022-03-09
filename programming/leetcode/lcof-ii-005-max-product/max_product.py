# @problem: 剑指 Offer II 005. 单词长度的最大乘积
# @file: max_product.py
# @url: https://leetcode-cn.com/problems/aseY1I
# @description:
#
# 给定一个字符串数组 words，请计算当两个字符串 words[i] 和 words[j]
# 不包含相同字符时，它们长度的乘积的最大值。假设字符串中只包含英语的小写字母。如果没有不包含相同字符的一对字符串，返回 0。
# 示例 1:
#
# 输入: words = ["abcw","baz","foo","bar","fxyz","abcdef"]
# 输出: 16
# 解释: 这两个单词为 "abcw", "fxyz"。它们不包含相同字符，且长度的乘积最大。
# 示例 2:
#
# 输入: words = ["a","ab","abc","d","cd","bcd","abcd"]
# 输出: 4
# 解释: 这两个单词为 "ab", "cd"。
# 示例 3:
#
# 输入: words = ["a","aa","aaa","aaaa"]
# 输出: 0
# 解释: 不存在这样的两个单词。
#
# 提示：
#
# 2 <= words.length <= 1000
# 1 <= words[i].length <= 1000
# words[i] 仅包含小写字母
#
# 注意：本题与主站 318 题相同：https://leetcode-cn.com/problems/maximum-product-of-
# word-lengths/
#
# @author: Du Ang
# @date: Mar 08, 2022

from typing import List, Tuple


class Solution1:
    """
    暴力遍历，依次计算 words 中两两之间的长度积。
    时间复杂度：O(n^2*max{words[i].length})
    空间复杂度：O(n^2*max{words[i].length})
    """

    def maxProduct(self, words: List[str]) -> int:
        max_product = 0
        for i in range(len(words)):
            for j in range(i, len(words)):
                max_product = max(self._product(words[i], words[j]), max_product)

        return max_product

    def _product(self, wi: str, wj: str) -> int:
        wi_set = set(wi)
        wj_set = set(wj)
        if wi_set.intersection(wj_set):
            return 0
        else:
            return len(wi) * len(wj)


class Solution2:
    """
    先将每个单词都转为 set，并记录原始长度，再暴力遍历，依次计算 words 中两两之间的长度积。
    时间复杂度：O(L + n^2)，L 为 words 所有单词长度之和
    空间复杂度：O(n)
    """

    def maxProduct(self, words: List[str]) -> int:
        words_set = [(set(word), len(word)) for word in words]
        max_product = 0
        for i in range(len(words_set)):
            for j in range(i, len(words_set)):
                max_product = max(self._product(words_set[i], words_set[j]), max_product)

        return max_product

    def _product(self, wi: Tuple[set, int], wj: Tuple[set, int]) -> int:
        wi_set, wi_len = wi[0], wi[1]
        wj_set, wj_len = wj[0], wj[1]
        if wi_set.intersection(wj_set):
            return 0
        else:
            return wi_len * wj_len


class Solution3:
    """
    先将每个单词都转为整数，并记录原始长度，再暴力遍历，使用位运算来辅助计算 words
    中两两之间的长度积，如果两个单词不含有共同字母，则它们对应整数的位与结果应该为0。
    时间复杂度：O(L+n^2），L 为 words 所有单词长度之和
    空间复杂度：O(n)
    """

    def maxProduct(self, words: List[str]) -> int:
        words_set = [(self._word2int(word), len(word)) for word in words]
        max_product = 0
        for i in range(len(words_set)):
            for j in range(i, len(words_set)):
                max_product = max(self._product(words_set[i], words_set[j]), max_product)
        return max_product

    def _word2int(self, word: str) -> int:
        result = 0
        for char in word:
            result |= 1 << (ord(char) - 97)
        return result

    def _product(self, wi: Tuple[int, int], wj: Tuple[int, int]) -> int:
        if wi[0] & wj[0] == 0:
            # no overlap
            return wi[1] * wj[1]
        else:
            # have overlap
            return 0


class Solution:
    """
    基于方法3，考虑如果数组 words 中存在由相同的字母组成的不同单词，则会造成不必要的重复
    计算，可以通过哈希表记录每个整数对应的最大单词长度来优化。
    时间复杂度：O(L+n^2)，L 为 words 所有单词长度之和
    空间复杂度：O(n)
    """

    def maxProduct(self, words: List[str]) -> int:
        words_dict = dict()
        for word in words:
            mask = self._word2int(word)
            if mask in words_dict:
                words_dict[mask] = max(len(word), words_dict[mask])
            else:
                words_dict[mask] = len(word)

        max_product = 0
        for wi, wi_len in words_dict.items():
            for wj, wj_len in words_dict.items():
                if wi & wj == 0:
                    max_product = max(wi_len * wj_len, max_product)

        return max_product

    def _word2int(self, word: str) -> int:
        result = 0
        for char in word:
            result |= 1 << (ord(char) - 97)
        return result
