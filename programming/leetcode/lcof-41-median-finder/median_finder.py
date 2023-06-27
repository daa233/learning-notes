# @problem: 剑指 Offer 41. 数据流中的中位数
# @file: median_finder.py
# @url: https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof
# @description:
#
# 如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么
# 中位数就是所有数值排序之后中间两个数的平均值。
# 例如，
# [2,3,4] 的中位数是 3
# [2,3] 的中位数是 (2 + 3) / 2 = 2.5
# 设计一个支持以下两种操作的数据结构：
#
# void addNum(int num) - 从数据流中添加一个整数到数据结构中。
# double findMedian() - 返回目前所有元素的中位数。
#
# 示例 1：
# 输入：
# ["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
# [[],[1],[2],[],[3],[]]
# 输出：[null,null,null,1.50000,null,2.00000]
#
# 示例 2：
# 输入：
# ["MedianFinder","addNum","findMedian","addNum","findMedian"]
# [[],[2],[],[3],[]]
# 输出：[null,null,2.00000,null,2.50000]
# 限制：
#
# 最多会对 addNum、findMedian 进行 50000 次调用。
#
# 注意：本题与主站 295 题相同：https://leetcode-cn.com/problems/find-median-from-
# data-stream/
#
# @author: Du Ang
# @date: Jun 26, 2023

from typing import List
from abc import abstractmethod


def binary_search(a: List, target, left: int = 0, right: int = None) -> int:
    """
    The return value i is such that all e in a[:i] have e <= x, and all e in
    a[i:] have e > x.
    """

    def condition(value, target) -> bool:
        return value > target

    if left < 0:
        raise ValueError("left must be non-negative instead of {}".format(left))
    if right is None:
        right = len(a)

    while left < right:
        mid = left + (right - left) // 2
        if condition(a[mid], target):
            right = mid
        else:
            left = mid + 1
    return left


class MedianFinder1:
    """有序链表"""

    def __init__(self):
        """
        initialize your data structure here.
        """
        self._data = []

    def addNum(self, num: int) -> None:
        i = binary_search(self._data, num)
        self._data.insert(i, num)

    def findMedian(self) -> float:
        total_len = len(self._data)
        if not total_len:
            raise ValueError("No numbers added yet!")
        elif total_len % 2 == 0:
            j = total_len // 2
            i = j - 1
            return (self._data[i] + self._data[j]) / 2.0
        else:
            return self._data[total_len // 2]


class _BasePQ:
    """基于堆实现的优先级队列的基类"""

    def __init__(self) -> None:
        self._size = 0
        self._pq = [0]

    @abstractmethod
    def _condition(self, i: int, j: int) -> bool:
        """比较两个元素"""
        pass

    def _exch(self, i: int, j: int) -> None:
        """交换两个元素"""
        self._pq[i], self._pq[j] = self._pq[j], self._pq[i]

    def _swim(self, k: int) -> None:
        """上浮方法"""
        while k > 1 and self._condition(k // 2, k):
            self._exch(k, k // 2)
            k = k // 2

    def _sink(self, k: int) -> None:
        """下沉方法"""
        while k * 2 <= self._size:
            # 让 j 指向 k 的子节点中较大的那个
            j = k * 2
            if j < self._size and self._condition(j, j + 1):
                j += 1
            if not self._condition(k, j):
                break
            self._exch(k, j)
            k = j

    def size(self) -> int:
        """返回优先级队列当前的大小"""
        return self._size

    def insert(self, v: int) -> None:
        """插入元素"""
        self._pq.append(v)
        self._size += 1
        self._swim(self._size)

    def is_empty(self) -> bool:
        """判断优先级队列是否为空"""
        return self._size == 0


class MaxPQ(_BasePQ):
    def _condition(self, i: int, j: int) -> bool:
        """比较两个元素"""
        return self._pq[i] < self._pq[j]

    def del_max(self) -> int:
        """删除最大元素"""
        if self.is_empty():
            return None
        max_v = self._pq[1]
        self._exch(1, self._size)
        self._pq.pop(-1)
        self._size -= 1
        self._sink(1)
        return max_v

    def get_max(self) -> int:
        """获取最大元素"""
        if self.is_empty():
            return None
        return self._pq[1]


class MinPQ(_BasePQ):
    def __init__(self) -> None:
        super().__init__()

    def _condition(self, i: int, j: int) -> bool:
        """比较两个元素"""
        return self._pq[i] >= self._pq[j]

    def del_min(self) -> int:
        """删除最小元素"""
        if self.is_empty():
            return None
        min_v = self._pq[1]
        self._exch(1, self._size)
        self._pq.pop(-1)
        self._size -= 1
        self._sink(1)
        return min_v

    def get_min(self) -> int:
        """获取最小元素"""
        if self.is_empty():
            return None
        return self._pq[1]


class MedianFinder2:
    """使用自定义实现的最大堆和最小堆"""

    def __init__(self):
        """
        initialize your data structure here.
        """
        self._max_pq = MaxPQ()
        self._min_pq = MinPQ()

    def addNum(self, num: int) -> None:
        if self._min_pq.is_empty() or num > self._min_pq.get_min():
            self._min_pq.insert(num)
            if self._min_pq.size() - 1 > self._max_pq.size():
                self._max_pq.insert(self._min_pq.del_min())
        else:
            self._max_pq.insert(num)
            if self._max_pq.size() > self._min_pq.size():
                self._min_pq.insert(self._max_pq.del_max())

    def findMedian(self) -> float:
        if self._max_pq.is_empty() and self._min_pq.is_empty():
            raise ValueError("No numbers added yet!")
        elif self._max_pq.size() < self._min_pq.size():
            return self._min_pq.get_min()
        else:
            return (self._max_pq.get_max() + self._min_pq.get_min()) / 2.0


import heapq


class MedianFinder:
    """使用官方实现的最大堆和最小堆"""

    def __init__(self):
        """
        initialize your data structure here.
        """
        self._max_pq = []
        self._min_pq = []

    def addNum(self, num: int) -> None:
        if not self._min_pq or num > self._min_pq[0]:
            heapq.heappush(self._min_pq, num)
            if len(self._min_pq) - 1 > len(self._max_pq):
                heapq.heappush(self._max_pq, -heapq.heappop(self._min_pq))
        else:
            heapq.heappush(self._max_pq, -num)
            if len(self._max_pq) > len(self._min_pq):
                heapq.heappush(self._min_pq, -heapq.heappop(self._max_pq))

    def findMedian(self) -> float:
        if not self._max_pq and not self._min_pq:
            raise ValueError("No numbers added yet!")
        elif len(self._max_pq) < len(self._min_pq):
            return self._min_pq[0]
        else:
            return (-self._max_pq[0] + self._min_pq[0]) / 2.0


# Your MedianFinder object will be instantiated and called as such:
# obj = MedianFinder()
# obj.addNum(num)
# param_2 = obj.findMedian()
