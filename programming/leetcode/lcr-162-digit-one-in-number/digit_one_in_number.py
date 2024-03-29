# @problem: LCR 162. 数字 1 的个数
# @file: digit_one_in_number.py
# @url: https://leetcode.cn/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof
# @description:
#
# 给定一个整数 num，计算所有小于等于 num 的非负整数中数字 1 出现的个数。
# 示例 1：
#
# 输入：num = 0
# 输出：0
#
# 示例 2：
#
# 输入：num = 13
# 输出：6
# 提示：
#
# 0 <= num < 109
#
# 注意：本题与主站 233 题相同：https://leetcode-cn.com/problems/number-of-digit-one/
#
# @author: Du Ang
# @date: Jan 13, 2024


class Solution1:
    """数学规律"""

    def factorial(self, n: int) -> int:
        """计算 n 的阶乘 n!"""
        p = 1
        while n > 1:
            p *= n
            n -= 1
        return p

    def c_n_k(self, n: int, k: int) -> int:
        """计算组合数 C_n^k 的值"""
        numerator = self.factorial(n)
        denominator = self.factorial(k) * self.factorial(n - k)
        return numerator // denominator

    def cal_kth_digit_sum(self, k: int) -> int:
        """计算 f(10...0) 的结果，总共 k 个 0，a >= 1"""
        s = 1
        for i in range(1, k + 1):
            s += i * self.c_n_k(k, i) * (9 ** (k - i))
        return s

    def digitOneInNumber(self, num: int) -> int:
        k = 0  # 数字的位数，从第 0 位开始
        s = 0
        one_zeros = 10**k
        while num // one_zeros > 0:
            r = (num // one_zeros) % 10
            # 计算 f(10...0) 的结果
            cur_digit_sum = self.cal_kth_digit_sum(k)
            # 计算 f(rx...x) 的结果
            if r == 0:
                pass
            elif r == 1:
                s += cur_digit_sum  # f(10...0) 部分
                s += num % one_zeros  # f(1x...x) 部分
            else:
                s += one_zeros  # f(1x...x) 部分
                s += r * (cur_digit_sum - 1)  # f(rx...x) 部分, r > 1
            k += 1
            one_zeros = 10**k

        return s


class Solution2:
    """动态规划"""

    def factorial(self, n: int) -> int:
        """计算 n 的阶乘 n!"""
        p = 1
        while n > 1:
            p *= n
            n -= 1
        return p

    def c_n_k(self, n: int, k: int) -> int:
        """计算组合数 C_n^k 的值"""
        numerator = self.factorial(n)
        denominator = self.factorial(k) * self.factorial(n - k)
        return numerator // denominator

    def cal_kth_digit_sum(self, k: int) -> int:
        """计算 f(10...0) 的结果，总共 k 个 0，a >= 1"""
        s = 1
        for i in range(1, k + 1):
            s += i * self.c_n_k(k, i) * (9 ** (k - i))
        return s

    def digitOneInNumber(self, num: int) -> int:
        k = 0  # 数字的位数，从第 0 位开始
        one_zeros = 10**k
        prev_res = 0
        res = 0
        while num // one_zeros > 0:
            r = (num // one_zeros) % 10
            # 计算 f(10...0) 的结果
            cur_digit_sum = self.cal_kth_digit_sum(k)
            res = prev_res
            # 计算 f(rx...x) 的结果
            if r == 0:
                pass
            elif r == 1:
                res += cur_digit_sum  # f(10...0) 部分
                res += num % one_zeros  # f(1x...x) 部分
            else:
                res += one_zeros  # f(1x...x) 部分
                res += r * (cur_digit_sum - 1)  # f(rx...x) 部分, r > 1
            k += 1
            one_zeros = 10**k
            prev_res = res

        return res


class Solution:
    """数学规律"""

    def digitOneInNumber(self, num: int) -> int:
        res = 0
        digit = 1

        high = num // 10
        cur = num % 10
        low = 0
        while high != 0 or cur != 0:
            if cur == 0:
                # 此位出现1的次数只由高位 high 决定
                res += high * digit
            elif cur == 1:
                # 此位出现1的次数由高位 high 和低位 low 决定
                res += high * digit + low + 1
            else:
                res += (high + 1) * digit

            low += cur * digit
            cur = high % 10
            high //= 10
            digit *= 10

        return res


if __name__ == "__main__":
    sln = Solution()
    for num in [0, 1, 10, 11, 13, 20, 100, 1001]:
        print(f"inp: {num}, out: {sln.digitOneInNumber(num)}")
