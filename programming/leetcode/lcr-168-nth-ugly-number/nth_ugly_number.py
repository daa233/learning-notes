# @problem: LCR 168. 丑数
# @file: nth_ugly_number.py
# @url: https://leetcode-cn.com/problems/chou-shu-lcof
# @description:
#
# 给你一个整数 n ，请你找出并返回第 n 个 丑数 。
# 说明：丑数是只包含质因数 2、3 和/或 5 的正整数；1 是丑数。
# 示例 1：
#
# 输入: n = 10
# 输出: 12
# 解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
# 提示：
#
# 1 <= n <= 1690
#
# 注意：本题与主站 264 题相同：https://leetcode-cn.com/problems/ugly-number-ii/
#
# @author: Du Ang
# @date: Dec 21, 2023


class Solution1:
    """暴力法（超出时间限制）"""

    def is_ugly_number(self, num: int) -> bool:
        factor = num
        while factor > 0:
            if factor % 5 == 0:
                factor = factor // 5
            elif factor % 3 == 0:
                factor = factor // 3
            elif factor % 2 == 0:
                factor = factor // 2
            elif factor == 1:
                return True
            else:
                return False

        return True

    def nthUglyNumber(self, n: int) -> int:
        count = 1
        num = 1
        while count < n:
            num += 1
            if self.is_ugly_number(num):
                count += 1
            else:
                continue
        return num


class Solution2:
    """哈希表缓存历史结果（超出时间限制）"""

    def is_ugly_number(self, num: int) -> bool:
        if num in self.hash_table:
            return self.hash_table[num]
        else:
            if num % 5 == 0:
                res = self.is_ugly_number(num // 5)
            elif num % 3 == 0:
                res = self.is_ugly_number(num // 3)
            elif num % 2 == 0:
                res = self.is_ugly_number(num // 2)
            else:
                res = False
            self.hash_table[num] = res
            return res

    def nthUglyNumber(self, n: int) -> int:
        count = 1
        num = 1
        self.hash_table = {1: True}
        while count < n:
            num += 1
            if self.is_ugly_number(num):
                count += 1
            else:
                continue
        return num


import heapq


class Solution3:
    """最小堆"""

    def nthUglyNumber(self, n: int) -> int:
        data = [1]
        data_set = set()  # 使用哈希集合防止重复添加元素到堆中

        # 构建堆
        heapq.heapify(data)

        count = 0
        nth_num = 0
        while count < n:
            # 让最小数出堆，从而保证按从小到大的顺序来获得丑数
            min_num = heapq.heappop(data)
            count += 1
            nth_num = min_num
            # 将最小数 2、3、5 的倍数入堆
            candidates = [min_num * 2, min_num * 3, min_num * 5]
            for c in candidates:
                if c not in data_set:
                    heapq.heappush(data, c)
                    data_set.add(c)

        return nth_num


class Solution:
    """动态规划"""

    def nthUglyNumber(self, n: int) -> int:
        dp = [1]
        a = 0  # 用于乘2
        b = 0  # 用于乘3
        c = 0  # 用于乘5

        while len(dp) < n:
            m2 = dp[a] * 2
            m3 = dp[b] * 3
            m5 = dp[c] * 5
            min_num = min(m2, m3, m5)

            dp.append(min_num)

            # NOTE: 为了避免重复，这里a、b、c 要独立更新
            if min_num == m2:
                a += 1
            if min_num == m3:
                b += 1
            if min_num == m5:
                c += 1

        return dp[-1]


if __name__ == "__main__":
    sln = Solution()
    print(sln.nthUglyNumber(10))
