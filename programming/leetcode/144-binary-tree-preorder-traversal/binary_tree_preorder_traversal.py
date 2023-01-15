# @problem: 144. Binary Tree Preorder Traversal
# @file: binary_tree_preorder_traversal.py
# @url: https://leetcode-cn.com/problems/binary-tree-preorder-traversal
# @description:
#
# Given the root of a binary tree, return the preorder traversal of its
# nodes' values.
# Example 1:
#
# Input: root = [1,null,2,3]
# Output: [1,2,3]
#
# Example 2:
#
# Input: root = []
# Output: []
#
# Example 3:
#
# Input: root = [1]
# Output: [1]
#
# Constraints:
#
# The number of nodes in the tree is in the range [0, 100].
# -100 <= Node.val <= 100
#
# Follow up: Recursive solution is trivial, could you do it iteratively?
#
# @author: Du Ang
# @date: Jan 07, 2023


from typing import Optional, List


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    """Preorder traversal by recursion."""

    def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        self.result = []
        self._helper(root)
        return self.result

    def _helper(self, root: TreeNode) -> List[int]:
        if root is None:
            return None

        self.result.append(root.val)
        self._helper(root.left)
        self._helper(root.right)


class Solution2:
    """Preorder traversal by iteration. Eliminate the tail recursion."""

    def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        result = []

        if root is None:
            return result

        stack = [root]
        while stack:
            node = stack.pop()
            result.append(node.val)
            # 注意先右后左入栈，因为栈是后进先出（LIFO）的
            if node.right:
                stack.append(node.right)
            if node.left:
                stack.append(node.left)

        return result


class Solution3:
    """Preorder traversal by iteration."""

    def preorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        if root is None:
            return []

        result = []
        stack = []
        node = root
        while True:
            # 沿最左侧通路自顶向下访问各结点，并将右孩子入栈暂存
            self.visitAlongLeftBranch(node, result, stack)
            if not stack:
                break
            # 右孩子依次出栈，自底向上遍历各结点的右子树
            node = stack.pop(-1)

        return result

    def visitAlongLeftBranch(
        self, root: Optional[TreeNode], result: List[int], stack: List[TreeNode]
    ) -> None:
        if root is None:
            return

        node = root
        while node:
            result.append(node.val)
            # 右孩子入栈暂存
            if node.right:
                stack.append(node.right)
            node = node.left
