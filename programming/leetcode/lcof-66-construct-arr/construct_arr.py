# @problem: 剑指 Offer 66. 构建乘积数组
# @file: construct_arr.py
# @url: https://leetcode-cn.com/problems/gou-jian-cheng-ji-shu-zu-lcof
# @description:
#
# 给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，其中 B[i] 的值是数组 A 中除了下标 i
# 以外的元素的积, 即 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。
# 示例:
#
# 输入: [1,2,3,4,5]
# 输出: [120,60,40,30,24]
# 提示：
#
# 所有元素乘积之和不会溢出 32 位整数
# a.length <= 100000
#
# @author: Du Ang
# @date: Aug 08, 2023

from typing import List


class Solution1:
    """暴力法（超出时间限制）"""

    def constructArr(self, a: List[int]) -> List[int]:
        b = []
        for i in range(len(a)):
            prod = 1
            for j in range(len(a)):
                if j == i:
                    continue
                prod *= a[j]
            b.append(prod)
        return b


class Solution2:
    """构造左右乘积数组"""

    def constructArr(self, a: List[int]) -> List[int]:
        if not a:
            return []

        # c[i] 为 i 左侧所有元素的乘积
        # 对于索引为 0 的元素，左侧没有元素，所以 c[0] = 1
        c = [0] * len(a)
        c[0] = 1
        for i in range(1, len(a)):
            c[i] = c[i - 1] * a[i - 1]
        # d[i] 为 i 右侧所有元素的乘积
        # 对于索引为 len(a)-1 的元素，左侧没有元素，所以 d[len(a)-1] = 1
        d = [0] * len(a)
        d[len(a) - 1] = 1
        for i in range(len(a) - 2, -1, -1):
            d[i] = d[i + 1] * a[i + 1]
        # 对于索引 i，除 a[i] 之外其余各元素的乘积就是左侧所有元素乘以右侧所有元素的乘积
        b = []
        for i in range(len(a)):
            b.append(c[i] * d[i])
        return b


class Solution:
    """
    构造左右乘积数组，优化空间复杂度至 O(1)
    先遍历所有元素，在 answer 中先构造左侧数组乘积；
    再遍历所有元素，将右侧数组乘积使用一个变量 d 存储，然后不断更新 d 和 answer；
    最后将 answer 作为输出数组
    """

    def constructArr(self, a: List[int]) -> List[int]:
        if not a:
            return []
        # 使用 answer 构造左侧数组乘积
        answer = [0] * len(a)
        answer[0] = 1
        for i in range(1, len(a)):
            answer[i] = answer[i - 1] * a[i - 1]
        print(answer)
        # 使用 d 构造右侧数组乘积，并更新 answer 和 d
        d = 1
        for i in range(len(a)):
            answer[len(a) - 1 - i] *= d
            d *= a[len(a) - 1 - i]

        return answer


if __name__ == "__main__":
    a = [1, 2, 3, 4, 5]
    sln = Solution()
    print(sln.constructArr(a))
