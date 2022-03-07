# @problem: 剑指 Offer II 004. 只出现一次的数字
# @file: single_number.py
# @url: https://leetcode-cn.com/problems/WGki4K
# @description:
#
# 给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。
# 示例 1：
#
# 输入：nums = [2,2,3,2]
# 输出：3
#
# 示例 2：
#
# 输入：nums = [0,1,0,1,0,1,100]
# 输出：100
#
# 提示：
#
# 1 <= nums.length <= 3 * 10^4
# -2^31 <= nums[i] <= 2^31 - 1
# nums 中，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次
#
# 进阶：你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？
# 注意：本题与主站 137 题相同：https://leetcode-cn.com/problems/single-number-ii/
#
# @author: Du Ang
# @date: Mar 03, 2022
from typing import List


class Solution1:
    """
    哈希表记录。
    时间复杂度：O(n)
    空间复杂度：O(n)
    """

    def singleNumber(self, nums: List[int]) -> int:
        self.mem = dict()

        for num in nums:
            if num in self.mem:
                self.mem[num] += 1
            else:
                self.mem[num] = 1

        for num, count in self.mem.items():
            if count == 1:
                return num


class Solution2:
    """
    将数组所有同一位置的数位相加。因为除目标数字外，其他所有数字都出现三次，则答案的
    第 i 个二进制位就是数组中所有元素的第 i 个二进制数位之和除以3的余数。
    时间复杂度：O(nlogC)，其中 n 是数组的长度，C 是元素的数据范围
    空间复杂度：O(sizeof(int))
    """

    def singleNumber(self, nums: List[int]) -> int:
        NUM_BITS = 32
        self.mem = [0] * NUM_BITS

        for num in nums:
            for i in range(NUM_BITS):
                v = (num >> i) & 1
                self.mem[NUM_BITS - 1 - i] += v

        target_num_bits = [i % 3 for i in self.mem]

        if target_num_bits[0] == 0:
            # target number is positive
            target = int("".join([str(i) for i in target_num_bits]), 2)
        else:
            # target number is negative
            target = -(2 ** 31 - int("".join([str(i) for i in target_num_bits[1:]]), 2))

        return target


class Solution3:
    """
    将数组所有同一位置的数位相加。因为除目标数字外，其他所有数字都出现三次，则答案的
    第 i 个二进制位就是数组中所有元素的第 i 个二进制数位之和除以3的余数。
    细节：注意如果数字在程序语言中是以补码的形式存储的，则需要对二进制的最高位进行特殊判断。
    时间复杂度：O(nlogC)，其中 n 是数组的长度，C 是元素的数据范围
    空间复杂度：O(1)
    """

    def singleNumber(self, nums: List[int]) -> int:
        NUM_BITS = 32
        result = 0

        for i in range(NUM_BITS):
            s = 0
            for num in nums:
                s += (num >> i) & 1
            s = s % 3
            if i == (NUM_BITS - 1):
                result += -s * (2 ** i)
            else:
                result += s * (2 ** i)

        return result


class Solution4:
    """
    数字电路设计。可以利用整数的位运算来替代每个数位的单独操作，这时需要设计一个
    数字电路来完成操作。假设我们用 state 来存储所有整数一个数位加和后模3的状态
    值，并且遍历所有的整数集合，逐个整数的更新 state 的值。单个数位 state 的状态
    值可能为 {0, 1, 2}，有3 种，而一个整数的一个数位只能表示 {0, 1} 两个状态值，
    所以至少需要两个整数才能表示 state。因此我们用两个整数 a、b 表示 state，则
    state 的状态值可能为 {00, 01, 10}。对于每个新遍历的整数数位 xi，其值可能为
    {0, 1}，输出可能为 {00, 01, 10} 中的一个，可根据输入输出设计电路。
    同时更新 ai、bi：
    ai = ai' bi xi + ai bi' xi'
    bi = ai' bi' xi + ai' bi xi' = ai' (bi ^ xi)
    时间复杂度：O(n)
    空间复杂度：O(1)
    """

    def singleNumber(self, nums: List[int]) -> int:
        a, b = 0, 0

        for num in nums:
            temp_a = (~a & b & num) | (a & ~b & ~num)
            # b = (~a & ~b & num) | (~a & b & ~num)
            b = ~a & (b ^ num)
            a = temp_a

        return b


class Solution:
    """
    数字电路设计优化。将“同时更新”更改为“分别更新”，由于 b 更新比较简单，可以先更新 b，
    再基于更新后的 b 值更新 a 值。
    先更新 bi，再更新 ai：
    bi = ai' bi' xi + ai' bi xi' = ai' (bi ^ xi)
    ai = ai' bi' xi + ai bi' xi' = bi' (ai ^ xi)
    时间复杂度：O(n)
    空间复杂度：O(1)
    """

    def singleNumber(self, nums: List[int]) -> int:
        a, b = 0, 0

        for num in nums:
            b = ~a & (b ^ num)
            a = ~b & (a ^ num)

        return b
