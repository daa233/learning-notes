# @problem: 226. Invert Binary Tree
# @file: invert_binary_tree.py
# @url: https://leetcode-cn.com/problems/invert-binary-tree
# @description:
#
# Given the root of a binary tree, invert the tree, and return its root.
# Example 1:
#
# Input: root = [4,2,7,1,3,6,9]
# Output: [4,7,2,9,6,3,1]
#
# Example 2:
#
# Input: root = [2,1,3]
# Output: [2,3,1]
#
# Example 3:
#
# Input: root = []
# Output: []
#
# Constraints:
#
# The number of nodes in the tree is in the range [0, 100].
# -100 <= Node.val <= 100
#
# @author: Du Ang
# @date: Apr 28, 2023

from typing import Optional


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if root is None:
            return None

        copy_node = TreeNode(val=root.val)
        left_child = self.invertTree(root.left)
        right_child = self.invertTree(root.right)
        copy_node.left = right_child
        copy_node.right = left_child

        return copy_node
