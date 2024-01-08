# @problem: LCR 180. 文件组合
# @file: file_combination.py
# @url: https://leetcode.cn/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof
# @description:
#
# 待传输文件被切分成多个部分，按照原排列顺序，每部分文件编号均为一个 正整数（至少含有两个文件）。传输要求为：连续文件编号总和为接收方指定数字
# target 的所有文件。请返回所有符合该要求的文件传输组合列表。
# 注意，返回时需遵循以下规则：
#
# 每种组合按照文件编号 升序 排列；
# 不同组合按照第一个文件编号 升序 排列。
#
# 示例 1：
#
# 输入：target = 12
# 输出：[[3, 4, 5]]
# 解释：在上述示例中，存在一个连续正整数序列的和为 12，为 [3, 4, 5]。
#
# 示例 2：
#
# 输入：target = 18
# 输出：[[3,4,5,6],[5,6,7]]
# 解释：在上述示例中，存在两个连续正整数序列的和分别为 18，分别为 [3, 4, 5, 6] 和 [5, 6, 7]。
#
# 提示：
#
# 1 <= target <= 10^5
#
# @author: Du Ang
# @date: Jan 07, 2024

from typing import List


class Solution1:
    """暴力法（超出时间限制）"""

    def fileCombination(self, target: int) -> List[List[int]]:
        res = []
        for i in range(target // 2, 1, -1):
            for j in range(1, target // i + 1):
                tmp = []
                count = 0
                s = 0
                k = j
                while count < i:
                    tmp.append(k)
                    s += k
                    count += 1
                    k += 1
                    if s < target and count < i:
                        continue
                    elif s == target and count == i:
                        res.append(tmp)
                    else:
                        break
        return res


class Solution2:
    """
    等差数列求和公式
    $s = a_1 n + d \cdot \frac{n(n-1)}{2}$，公差 $d = 1$
    """

    def fileCombination(self, target: int) -> List[List[int]]:
        res = []
        for i in range(target // 2, 1, -1):
            for j in range(1, target // i + 1):
                s = j * i + i * (i - 1) // 2
                if s == target:
                    res.append([k for k in range(j, j + i)])
                else:
                    continue
        return res


class Solution:
    """
    等差数列求和公式
    $s = a_1 n + d \cdot \frac{n(n-1)}{2}$，公差 $d = 1$

    数列左边界 i，数列总和 s，则右边界 j 为
    $j = i + n - 1 = -\frac{1}{2} + \sqrt{(i - \frac{1}{2})^2 + 2s}$
    """

    def fileCombination(self, target: int) -> List[List[int]]:
        res = []
        for i in range(1, target // 2 + 1):
            j = -0.5 + ((i - 0.5) ** 2 + 2 * target) ** 0.5
            if i < j and j == int(j):
                res.append([k for k in range(i, int(j) + 1)])

        return res


if __name__ == "__main__":
    sln = Solution()
    for target in [12, 18, 93, 87760]:
        print(f"{target}: {sln.fileCmbination(target)}")
