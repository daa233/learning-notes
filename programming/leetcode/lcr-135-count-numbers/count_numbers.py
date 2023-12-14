# @problem: LCR 135. 报数
# @file: count_numbers.py
# @url: https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof
# @description:
#
# 实现一个十进制数字报数程序，请按照数字从小到大的顺序返回一个整数数列，该数列从数字 1 开始，到最大的正整数 cnt 位数字结束。
# 示例 1:
#
# 输入：cnt = 2
# 输出：[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
# 26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,4
# 9,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72
# ,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,
# 96,97,98,99]
#
# @author: Du Ang
# @date: Dec 11, 2023

from typing import List


class Solution1:
    """直接生成，不考虑大数越界"""

    def countNumbers(self, cnt: int) -> List[int]:
        return [i for i in range(1, 10**cnt)]


class Solution2:
    """考虑大数越界"""

    def countNumbers(self, cnt: int) -> List[int]:
        result = []

        def dfs(i: int):
            if i == cnt:  # 已固定所有数位，终止
                # 找到第一个不是 0 的数字位
                non_zero_index = None
                for index in range(len(nums)):
                    if nums[index] != "0":
                        non_zero_index = index
                        break
                if non_zero_index is not None:
                    # 将数字转换为 int 存储，并去掉开头的0
                    result.append(int("".join(nums[non_zero_index:])))
                return
            for j in range(10):
                nums[i] = str(j)  # 固定第i位为数字j
                dfs(i + 1)  # 开始固定第i+1位

        nums = ["0"] * cnt
        dfs(0)

        return result


from typing import Optional


class Solution:
    """考虑大数越界，优化去掉开头0的方法"""

    def countNumbers(self, cnt: int) -> List[int]:
        result = []

        def dfs(i: int, start: Optional[int] = None):
            if i == cnt:  # 已固定所有数位，终止
                if start is not None:
                    # 将数字转换为 int 存储，并去掉开头的0
                    result.append(int("".join(nums[start:])))
                return

            for j in range(10):
                if j != 0:
                    if start is None:
                        vi = i  # 还没有最高有效位，当前第i位就是最高有效位
                    else:
                        # 沿用原来的最高有效位
                        vi = start
                else:
                    vi = start  # 沿用原来的最高有效位
                nums[i] = str(j)  # 固定第i位为数字j
                dfs(i + 1, vi)  # 开始固定第i+1位

        nums = ["0"] * cnt
        dfs(0)

        return result


if __name__ == "__main__":
    sln = Solution()
    result = sln.countNumbers(2)
    print(result)
