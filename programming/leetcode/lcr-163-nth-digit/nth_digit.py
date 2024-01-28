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


class Solution1:
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


class Solution2:
    """数学规律"""

    def findKthNumber(self, k: int) -> int:
        if k == 0:
            return 0

        i = -1  # 数字的位数
        s = 0  # 数字累积位数
        c = 0  # 数字累积位数

        # 定位到 s_i <= k < s_{i+1}
        # 赋值 c = s_i
        while s < k:
            i += 1
            c = s
            if i == 0:
                s = 0
            else:
                s += 9 * (10 ** (i - 1)) * i

        base = 10 ** (i - 1) - 1

        digits_offset_from_base = k - c
        if digits_offset_from_base % i == 0:
            # 第 k 位数字属于数 num
            num = base + digits_offset_from_base // i
            # 相对于 num 起始高位的偏移量 j
            j = i - 1  # 第 j 位对应 num 的最后一位
        else:
            # 第 k 位数字属于数 num
            num = base + digits_offset_from_base // i + 1
            # 相对于 num 起始高位的偏移量 j，对应 num 的第 j 位，从 0 开始数
            j = digits_offset_from_base - digits_offset_from_base // i * i - 1

        # 求 num 的从高位开始数，第 j 位数字
        digit_factor = 1
        n = num
        digits = []
        while n > 0:
            digits.append(n % 10)
            digit_factor *= 10
            n //= 10
        jc = -1
        while digits:
            digit = digits.pop(-1)
            jc += 1
            if jc == j:
                return digit


class Solution:
    """数学规律（优化）"""

    def findKthNumber(self, k: int) -> int:
        if k == 0:
            return 0

        i = 0  # 数字的位数
        c = 0  # 数字累积位数
        start = 1  # i 位数的起始数字
        offset = k  # 位的偏移量

        # 1. 确定所求数字是 i 位数，i 位数的起始数字为 start
        # 定位到 s_i <= k < s_{i+1}
        # 使用 `k -= c` 的写法在其他语言中可以防止 i32 溢出
        while k > c:
            i += 1
            offset -= c
            start = 10 ** (i - 1)
            c = 9 * start * i

        # 2. 确定所求数位所在的数字
        num = start + (offset - 1) // i

        # 3. 确定所求数位在 num 的哪一数位
        j = (offset - 1) % i

        # 求 num 的从高位开始数，第 j 位数字
        res = int(str(num)[j])

        return res


if __name__ == "__main__":
    sln = Solution()
    for inp in [0, 5, 10, 12]:
        print(f"k = {inp}, result = {sln.findKthNumber(inp)}")
