# @problem: LCR 163. 找到第 k 位数字
# @file: nth_digit.py
# @url: https://leetcode.cn/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof
# @description:
#
# 某班级学号记录系统发生错乱，原整数学号序列 [0,1,2,3,4,...] 分隔符丢失后变为 01234...
# 的字符序列。请实现一个函数返回该字符序列中的第 k 位数字。
# 示例 1：
#
# 输入：k = 5
# 输出：5
#
# 示例 2：
#
# 输入：k = 12
# 输出：1
# 解释：第 12 位数字在序列 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... 里是 1 ，它是 11
# 的一部分。
# 提示：
#
# 0 <= k < 231
#
# 注意：本题与主站 400 题相同：https://leetcode-cn.com/problems/nth-digit/
#
# @author: Du Ang
# @date: Jan 21, 2024


class Solution:
    """直接遍历（超出时间限制）"""

    def findKthNumber(self, k: int) -> int:
        i = 0
        c = -1
        digits = [0]
        while c < k:
            n = i
            digit_factor = 1
            while n > 0:
                digits.append(n % 10)
                digit_factor *= 10
                n //= 10
            # print(f"i = {i}, digits: {digits}")
            while digits:
                digit = digits.pop(-1)
                c += 1
                if c == k:
                    return digit

            i += 1


if __name__ == "__main__":
    sln = Solution()
    for inp in [5, 10, 12]:
        print(f"k = {inp}, result = {sln.findKthNumber(inp)}")
