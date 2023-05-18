# @problem: 剑指 Offer 54. 二叉搜索树的第k大节点
# @file: kth_largest.py
# @url: https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-di-kda-jie-dian-lcof
# @description:
#
# 给定一棵二叉搜索树，请找出其中第 k 大的节点的值。
# 示例 1:
#
# 输入: root = [3,1,4,null,2], k = 1
#    3
#   / \
#  1   4
#   \
#    2
# 输出: 4
# 示例 2:
#
# 输入: root = [5,3,6,2,4,null,null,1], k = 3
#        5
#       / \
#      3   6
#     / \
#    2   4
#   /
#  1
# 输出: 4
# 限制：
#
# 1 ≤ k ≤ 二叉搜索树元素个数
#
# @author: Du Ang
# @date: May 17, 2023

from typing import Tuple

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    """逆中序遍历"""

    def _inv_inorder_traversal(
        self, root: TreeNode, k: int, prev_count: int
    ) -> Tuple[TreeNode, int]:
        if root is None:
            return (None, 0)

        count = prev_count
        if root.right:
            node, count = self._inv_inorder_traversal(root.right, k, count)
            if node:
                return (node, count)

        count += 1
        if count == k:
            return (root, k)

        if root.left:
            node, count = self._inv_inorder_traversal(root.left, k, count)
            if node:
                return (node, count)

        return (None, count)

    def kthLargest(self, root: TreeNode, k: int) -> int:
        node, count = self._inv_inorder_traversal(root, k, 0)
        if node:
            return node.val
        else:
            return None
