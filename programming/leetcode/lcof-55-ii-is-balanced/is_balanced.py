# @problem: 剑指 Offer 55 - II. 平衡二叉树
# @file: is_balanced.py
# @url: https://leetcode-cn.com/problems/ping-heng-er-cha-shu-lcof
# @description:
#
# 输入一棵二叉树的根节点，判断该树是不是平衡二叉树。如果某二叉树中任意节点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。
# 示例 1:
# 给定二叉树 [3,9,20,null,null,15,7]
#
#     3
#    / \
#   9  20
#     /  \
#    15   7
# 返回 true 。
#
# 示例 2:
# 给定二叉树 [1,2,2,3,3,null,null,4,4]
#
#        1
#       / \
#      2   2
#     / \
#    3   3
#   / \
#  4   4
#
# 返回 false 。
# 限制：
#
# 0 <= 树的结点个数 <= 10000
#
# 注意：本题与主站 110 题相同：https://leetcode-cn.com/problems/balanced-binary-
# tree/
#
# @author: Du Ang
# @date: Jun 28, 2023


from typing import Tuple


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    """深度优先搜索 + 回溯"""

    def _dfs(self, root: TreeNode) -> Tuple[int, bool]:
        if not root:
            return 0, True

        left_depth, left_is_balanced = self._dfs(root.left)
        right_depth, right_is_balanced = self._dfs(root.right)
        depth = max(left_depth, right_depth) + 1
        if left_is_balanced and right_is_balanced and abs(left_depth - right_depth) <= 1:
            return depth, True
        else:
            return depth, False

    def isBalanced(self, root: TreeNode) -> bool:
        _, res = self._dfs(root)
        return res
