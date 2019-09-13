# -*- coding:utf-8 -*-
# 题目描述
# 请实现一个函数，将一个字符串中的每个空格替换成“%20”。
# 例如，当字符串为We Are Happy，则经过替换之后的字符串为We%20Are%20Happy。

# 用 Python 解决这个问题很骚，这题关键还是考察 C++
class Solution:
    # s 源字符串
    def replaceSpace(self, s):
        # write code here
        return s.replace(' ', '%20')


if __name__ == '__main__':
    s = "We Are Happy"
    print(Solution().replaceSpace(s))

