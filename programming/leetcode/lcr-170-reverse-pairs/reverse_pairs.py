# @problem: LCR 170. 交易逆序对的总数
# @file: reverse_pairs.py
# @url: https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof
# @description:
#
# 在股票交易中，如果前一天的股价高于后一天的股价，则可以认为存在一个「交易逆序对」。请设计一个程序，输入一段时间内的股票交易记录
# record，返回其中存在的「交易逆序对」总数。
# 示例 1:
#
# 输入：record = [9, 7, 5, 4, 6]
# 输出：8
# 解释：交易中的逆序对为 (9, 7), (9, 5), (9, 4), (9, 6), (7, 5), (7, 4), (7, 6),
# (5, 4)。
#
# 限制：
# 0 <= record.length <= 50000
#
# @author: Du Ang
# @date: Dec 18, 2023

from typing import List


class Solution1:
    """暴力法（超出时间限制）"""

    def reversePairs(self, record: List[int]) -> int:
        if len(record) <= 1:
            return 0

        count = 0
        for i in range(len(record)):
            for j in range(i + 1, len(record)):
                if record[i] > record[j]:
                    count += 1

        return count


import heapq


class Solution2:
    """最大堆（超出时间限制）"""

    def reversePairs(self, record: List[int]) -> int:
        right_less_count = []
        data = []
        heapq.heapify(data)

        for num in record[::-1]:
            if not data:
                # heapq 默认是最小堆，添加数字的相反数来当作最大堆使用
                heapq.heappush(data, -num)
                right_less_count.append(0)
            else:
                if num > -data[0]:
                    right_less_count.insert(0, len(data))
                else:
                    pop_data = []
                    while data and num <= -data[0]:
                        pop_data.append(heapq.heappop(data))
                    right_less_count.insert(0, len(data))
                    # 恢复右边数字构造的最大堆
                    for pop_num in pop_data:
                        heapq.heappush(data, pop_num)

                heapq.heappush(data, -num)

        return sum(right_less_count)


class Solution:
    """归并排序"""

    def merge(self, nums: List[int], left: int, mid: int, right: int):
        """合并 [left, mid] 和 [mid+1, right]，并计算、返回逆序对数目"""
        tmp_nums = [0] * (right - left + 1)
        i = left
        j = mid + 1
        reorder = 0
        count = 0
        # 同时关注两个区间，进行合并
        while i <= mid and j <= right:
            if nums[i] > nums[j]:
                tmp_nums[count] = nums[j]
                # 当左区间某个数字大于右区间时，左区间从 [i, mid] 内所有数字
                # 都与 j 位置数字构成了逆序对
                reorder += mid - i + 1
                j += 1
            else:
                tmp_nums[count] = nums[i]
                i += 1
            count += 1

        # 一半区间已经全部处理完了，处理另一半区间剩余的所有数字
        while i <= mid:
            tmp_nums[count] = nums[i]
            i += 1
            count += 1
        while j <= right:
            tmp_nums[count] = nums[j]
            j += 1
            count += 1

        # 将归并排序后的结果存储到 nums
        nums[left : right + 1] = tmp_nums[:]

        return reorder

    def merge_sort(self, nums: List[int], left: int, right: int) -> int:
        """归并排序并返回逆序对数目"""
        if left >= right:
            # 终止条件，数组中元素仅有一个
            return 0
        mid = (left + right) // 2  # 计算切分的中点
        res_left = self.merge_sort(nums, left, mid)  # 对 [left, mid] 执行归并排序
        res_right = self.merge_sort(nums, mid + 1, right)  # 对 [mid+1, right] 执行归并排序
        # 合并 [left, mid], [mid+1, right] 两个区间
        res_merge = self.merge(nums, left, mid, right)
        return res_left + res_right + res_merge

    def reversePairs(self, record: List[int]) -> int:
        return self.merge_sort(record, 0, len(record) - 1)


if __name__ == "__main__":
    sln = Solution()
    record = [9, 7, 5, 4, 6]
    print(sln.reversePairs(record))
    record = [7, 5, 6, 4]
    print(sln.reversePairs(record))
