# @problem: 剑指 Offer 40. 最小的k个数
# @file: get_least_numbers.py
# @url: https://leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof
# @description:
#
# 输入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。
# 示例 1：
# 输入：arr = [3,2,1], k = 2
# 输出：[1,2] 或者 [2,1]
#
# 示例 2：
# 输入：arr = [0,1,2,1], k = 1
# 输出：[0]
# 限制：
#
# 0 <= k <= arr.length <= 10000
# 0 <= arr[i] <= 10000
#
# @author: Du Ang
# @date: May 31, 2023

from typing import List


class Solution1:
    """quick sort"""

    def _partition(self, arr: List[int], left: int, right: int) -> int:
        pivot = left
        index = left + 1
        for i in range(index, right + 1):
            if arr[i] < arr[pivot]:
                arr[i], arr[index] = arr[index], arr[i]
                index += 1
        index -= 1
        arr[index], arr[pivot] = arr[pivot], arr[index]
        return index

    def _quick_sort(self, arr: List[int], left: int, right: int) -> None:
        if left < right:
            pivot = self._partition(arr, left, right)
            self._quick_sort(arr, left, pivot - 1)
            self._quick_sort(arr, pivot + 1, right)

    def getLeastNumbers(self, arr: List[int], k: int) -> List[int]:
        self._quick_sort(arr, 0, len(arr) - 1)
        return arr[:k]


class Solution2:
    """quick selection"""

    def _partition(self, arr: List[int], left: int, right: int) -> int:
        pivot = left
        index = left + 1
        for i in range(left + 1, right + 1):
            if arr[i] < arr[pivot]:
                arr[i], arr[index] = arr[index], arr[i]
                index += 1
        index -= 1
        arr[index], arr[pivot] = arr[pivot], arr[index]
        return index

    def _quick_selection(self, arr: List[int], left: int, right: int, k: int) -> None:
        if left < right:
            pivot = self._partition(arr, left, right)
            count = pivot - left + 1
            if count == k:
                return
            elif count < k:
                return self._quick_selection(arr, pivot + 1, right, k - count)
            else:
                return self._quick_selection(arr, left, pivot - 1, k)

    def getLeastNumbers(self, arr: List[int], k: int) -> List[int]:
        self._quick_selection(arr, 0, len(arr) - 1, k)
        return arr[:k]


class MaxPQ:
    """基于最大堆实现的优先级队列"""

    def __init__(self) -> None:
        self._size = 0
        self._pq = [0]

    def _less(self, i: int, j: int) -> bool:
        """比较两个元素"""
        return self._pq[i] < self._pq[j]

    def _exch(self, i: int, j: int) -> None:
        """交换两个元素"""
        self._pq[i], self._pq[j] = self._pq[j], self._pq[i]

    def _swim(self, k: int) -> None:
        """上浮方法"""
        while k > 1 and self._less(k // 2, k):
            self._exch(k, k // 2)
            k = k // 2

    def _sink(self, k: int) -> None:
        """下沉方法"""
        while k * 2 <= self._size:
            # 让 j 指向 k 的子节点中较大的那个
            j = k * 2
            if j < self._size and self._less(j, j + 1):
                j += 1
            if not self._less(k, j):
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

    def is_empty(self) -> bool:
        """判断优先级队列是否为空"""
        return self._size == 0


class Solution:
    """优先级队列"""

    def getLeastNumbers(self, arr: List[int], k: int) -> List[int]:
        max_pq = MaxPQ()
        for num in arr[:k]:
            max_pq.insert(num)
        for num in arr[k:]:
            if not max_pq.is_empty() and num > max_pq.get_max():
                continue
            max_pq.del_max()
            max_pq.insert(num)
        return max_pq._pq[1 : k + 1]


def check_result(inp: List[int], k: int, expected: List[str]) -> None:
    out = sln.getLeastNumbers(inp, k)
    out.sort()
    assert out == expected, f"inp {inp}, out {out} not equal {expected}"


if __name__ == "__main__":
    sln = Solution()

    arr = [0, 0, 0, 2, 0, 5]
    k = 0
    expected = []
    check_result(arr, k, expected)

    arr = [
        0,
        1,
        2,
        2,
        2,
        1,
        3,
        6,
        3,
        1,
        8,
        2,
        5,
        3,
        11,
        4,
        11,
        12,
        6,
        2,
        7,
        19,
        20,
        16,
        23,
        6,
        23,
        4,
        3,
        25,
        19,
        15,
        15,
        17,
        26,
        30,
        24,
        31,
        2,
        26,
        32,
        6,
        27,
        21,
        3,
        6,
        18,
        46,
        14,
        13,
        43,
        19,
        17,
        50,
        46,
        40,
        13,
        2,
        10,
        43,
        6,
        5,
        8,
        23,
        41,
        21,
        58,
        10,
        28,
        22,
        25,
        63,
        7,
        40,
        64,
        50,
        7,
        57,
        61,
        43,
        45,
        64,
        78,
        50,
        49,
        15,
        45,
        10,
        27,
        66,
        14,
        68,
        81,
        48,
        51,
        33,
        17,
        35,
        71,
        31,
    ]
    k = 24
    expected = [0, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 5, 5, 6, 6, 6, 6]
    check_result(arr, k, expected)
