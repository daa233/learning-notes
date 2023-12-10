# @problem: LCR 183. 望远镜中最高的海拔
# @file: max_altitude.py
# @url: https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof
# @description:
#
# 科技馆内有一台虚拟观景望远镜，它可以用来观测特定纬度地区的地形情况。该纬度的海拔数据记于数组 heights ，其中 heights[i]
# 表示对应位置的海拔高度。请找出并返回望远镜视野范围 limit 内，可以观测到的最高海拔值。
# 示例 1：
#
# 输入：heights = [14,2,27,-5,28,13,39], limit = 3
# 输出：[27,27,28,28,39]
# 解释：
#   滑动窗口的位置                最大值
# ---------------               -----
# [14 2 27] -5 28 13 39          27
# 14 [2 27 -5] 28 13 39          27
# 14 2 [27 -5 28] 13 39          28
# 14 2 27 [-5 28 13] 39          28
# 14 2 27 -5 [28 13 39]          39
# 提示：
# 你可以假设输入总是有效的，在输入数组不为空的情况下：
#
# 1 <= limit <= heights.length
# -10000 <= heights[i] <= 10000
#
# 注意：本题与主站 239 题相同：https://leetcode-cn.com/problems/sliding-window-
# maximum/
#
# @author: Du Ang
# @date: Dec 09, 2023

import heapq
from typing import List


class Solution1:
    """
    暴力法，两层循环。
    外层循环遍历数组中所有元素，内层循环寻找滑动窗口内的最大值
    """

    def _find_max_in_window(self, window: List[int]) -> int:
        max_value = window[0]
        for item in window[1:]:
            if item > max_value:
                max_value = item
        return max_value

    def maxAltitude(self, heights: List[int], limit: int) -> List[int]:
        window = []
        result = []
        for height in heights:
            window.append(height)
            if len(window) < limit:
                continue
            else:
                max_value = self._find_max_in_window(window)
                result.append(max_value)
                if len(window) >= limit:
                    # 当前 window 长度已满足 limit，清空一个为下一个进来做准备
                    window.pop(0)
        return result


class MaxPQ:
    def __init__(self) -> None:
        self._size = 0
        self.data = [0]

    def _less(self, i: int, j: int) -> bool:
        """比较方法"""
        if self.data[i][0] < self.data[j][0]:
            return True
        elif self.data[i][0] > self.data[j][0]:
            return False
        else:
            return self.data[i][1] < self.data[j][1]

    def _exch(self, i: int, j: int) -> None:
        """交换方法"""
        self.data[i], self.data[j] = self.data[j], self.data[i]

    def _swim(self, k: int) -> None:
        """
        上浮方法。
        如果堆的有序状态因为某个结点变得比它的父结点更大而被打破，
        那么我们就需要通过交换它和它的父结点来修复堆。
        """
        while k > 1 and self._less(k // 2, k):
            self._exch(k, k // 2)
            k = k // 2

    def _sink(self, k: int) -> None:
        """
        下沉方法。
        如果堆的有序状态因为某个结点变得比它的两个子结点或是其中
        之一更小了而被打破了，那么我们可以通过将它和它的两个子结
        点中的较大者交换来恢复堆。
        """
        while k * 2 <= self._size:
            j = k * 2
            if j < self._size and self._less(j, j+1):
                j += 1
            if not self._less(k, j):
                break
            self._exch(k, j)
            k = j

    def size(self) -> int:
        """返回队列大小"""
        return self._size

    def insert(self, value: int) -> None:
        """添加元素"""
        self.data.append(value)
        self._size += 1
        self._swim(self._size)

    def get_max(self) -> int:
        """获取最大元素"""
        if not self.data:
            raise ValueError("The PriorityQueue is empty!")
        return self.data[1]

    def del_max(self) -> int:
        """删除最大元素"""
        if not self.data:
            raise ValueError("The PriorityQueue is empty!")
        max_v = self.data[1]
        # 将根节点元素与数组最后一个元素交换
        self._exch(1, self._size)
        # 将交换后的最大元素移除
        self.data.pop(-1)
        self._size -= 1
        self._sink(1)
        return max_v


class Solution2:
    """
    优先级队列：基于自定义的最大堆 MaxPQ
    """

    def maxAltitude(self, heights: List[int], limit: int) -> List[int]:
        if not heights or not limit:
            return []
        pq = MaxPQ()
        result = []
        for i in range(limit):
            pq.insert((heights[i], i))
        result.append(pq.get_max()[0])

        for i in range(limit, len(heights)):
            pq.insert((heights[i], i))
            while True:
                max_idx = pq.get_max()[1]
                if max_idx <= i - limit:
                    pq.del_max()
                else:
                    break
            result.append(pq.get_max()[0])

        return result


class Solution3:
    """
    优先级队列：基于 Python 标准库 heapq
    注意：heapq 中实现的是最小堆，可以存储数据的相反数来将其作为最大堆使用
    """

    def maxAltitude(self, heights: List[int], limit: int) -> List[int]:
        if not heights or not limit:
            return []

        pq = []
        for i in range(limit):
            # 注意：为当作最大堆使用，此处存储的是数据的相反数和其索引
            pq.append((-heights[i], i))

        # 将 pq 数据转化为堆
        heapq.heapify(pq)

        result = []
        result.append(-pq[0][0])
        for i in range(limit, len(heights)):
            heapq.heappush(pq, (-heights[i], i))
            while True:
                max_idx = pq[0][1]
                if max_idx <= i - limit:
                    heapq.heappop(pq)
                else:
                    break
            result.append(-pq[0][0])

        return result


class Solution:
    """
    单调队列
    """

    def maxAltitude(self, heights: List[int], limit: int) -> List[int]:
        if not heights or not limit:
            return []

        deque = []
        result = []
        # 未形成窗口时
        for i in range(limit):
            # 尝试将 heights[i] 添加到 deque，并删除掉 deque 中比 heights[i] 小的元素
            while deque and heights[i] > deque[-1]:
                deque.pop(-1)
            deque.append(heights[i])
        result.append(deque[0])
        # 形成窗口后
        for i in range(limit, len(heights)):
            # 将 heights[i-limit] 从 deque 中移除
            if deque[0] == heights[i - limit]:
                deque.pop(0)
            # 尝试将 heights[i] 添加到 deque，并删除掉 deque 中比 heights[i] 小的元素
            while deque and heights[i] > deque[-1]:
                deque.pop(-1)
            deque.append(heights[i])
            result.append(deque[0])
        return result


if __name__ == "__main__":
    sln = Solution()
    heights = [14, 2, 27, -5, 28, 13, 39]
    limit = 3
    res = sln.maxAltitude(heights, limit)
    assert res == [27, 27, 28, 28, 39], f"res = {res}"

    heights = [1]
    limit = 1
    res = sln.maxAltitude(heights, limit)
    assert res == [1], f"res = {res}"

    heights = [1, -1]
    limit = 1
    res = sln.maxAltitude(heights, limit)
    assert res == [1, -1], f"res = {res}"

    heights = [9, 10, 9, -7, -4, -8, 2, -6]
    limit = 5
    res = sln.maxAltitude(heights, limit)
    assert res == [10, 10, 9, 2], f"res = {res}"
