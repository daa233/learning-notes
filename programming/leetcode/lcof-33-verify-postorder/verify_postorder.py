# @problem: 剑指 Offer 33. 二叉搜索树的后序遍历序列
# @file: verify_postorder.py
# @url: https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof
# @description:
#
# 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互
# 不相同。
# 参考以下这颗二叉搜索树：
#      5
#     / \
#    2   6
#   / \
#  1   3
# 示例 1：
# 输入: [1,6,3,2,5]
# 输出: false
# 示例 2：
# 输入: [1,3,2,6,5]
# 输出: true
# 提示：
#
# 数组长度 <= 1000
#
# @author: Du Ang
# @date: Jul 17, 2023

from typing import List
import sys


class Solution1:
    """递归分治"""

    def _dfs(self, postorder: List[int], start: int, end: int) -> bool:
        if start >= end:
            return True

        root_val = postorder[end]

        # 将根节点元素前的所有元素分为左右子树两个部分，需要满足：
        # 左子树的所有值 < 根节点的值 < 右子树的所有值
        i = start
        while postorder[i] < root_val:
            i += 1
        m = i  # m 是左右子树的边界，右子树的起始位置
        while postorder[i] > root_val:
            i += 1
        if i < end:
            # 右子树部分存在小于根节点的值，不满足要求
            return False

        return self._dfs(postorder, start, m - 1) and self._dfs(postorder, m, end - 1)

    def verifyPostorder(self, postorder: List[int]) -> bool:
        if not postorder:
            return True
        return self._dfs(postorder, 0, len(postorder) - 1)


class Solution2:
    """单调栈"""

    def verifyPostorder(self, postorder: List[int]) -> bool:
        if not postorder:
            return True

        stack = []
        parent = sys.maxsize

        for i in range(len(postorder) - 1, -1, -1):
            cur = postorder[i]
            if not stack or cur > stack[-1]:
                # 当前栈为空，或者遇到的是右节点，将遇到的节点入栈
                stack.append(cur)
            else:
                # 当前遇到的是左节点，从 stack 中寻找当前元素的父节点
                while stack and stack[-1] > cur:
                    parent = stack.pop(-1)
            # 如果当前节点比 parent 大，说明左子树节点比 parent 大，
            # 不符合二叉搜索树定义
            if cur > parent:
                return False

        return True


class Solution:
    """构造二叉搜索树"""

    def _build(self, postorder: List[int], lower_bound: int, upper_bound: int) -> None:
        if not postorder:
            # 后序遍历结果为空，直接返回
            return

        # 取数组中最后一个元素为当前树的根节点
        val = postorder[-1]
        if val <= lower_bound or val >= upper_bound:
            # 当前值不在二叉搜索树限定的值范围
            return

        # 当前值符合二叉搜索树限定的值范围，从数组中 pop 出来用于构造
        postorder.pop(-1)

        # 构造右子树部分，上界不变，下界为当前树根节点的值
        self._build(postorder, val, upper_bound)
        # 构造左子树部分，上界为当前树根节点的值，下界不变
        self._build(postorder, lower_bound, val)

    def verifyPostorder(self, postorder: List[int]) -> bool:
        self._build(postorder, -sys.maxsize, sys.maxsize)
        # 如果 postorder 不为空，说明没有构造完成，不是二叉搜索树
        if postorder:
            return False
        else:
            return True
