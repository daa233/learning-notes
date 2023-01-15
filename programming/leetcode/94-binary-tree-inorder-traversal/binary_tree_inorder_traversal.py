# @problem: 94. Binary Tree Inorder Traversal
# @file: binary_tree_inorder_traversal.py
# @url: https://leetcode-cn.com/problems/binary-tree-inorder-traversal
# @description:
#
# Given the root of a binary tree, return the inorder traversal of its
# nodes' values.
# Example 1:
#
# Input: root = [1,null,2,3]
# Output: [1,3,2]
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
# @date: Jan 08, 2023


from typing import Optional, List


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    """Inorder traversal by recursion."""

    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        self.result = []
        self._helper(root)
        return self.result

    def _helper(self, root: TreeNode) -> List[int]:
        if root is None:
            return None

        self._helper(root.left)
        self.result.append(root.val)
        self._helper(root.right)


class Solution2:
    """Inorder traversal by iteration."""

    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        if root is None:
            return []

        result = []
        stack = []
        node = root
        while True:
            # 沿最左侧通路自顶向下访问各结点，并将沿途结点入栈暂存
            self.goAlongLeftBranch(node, stack)
            if not stack:
                break
            # 依次出栈，自底向上遍历各结点及其右子树
            node = stack.pop(-1)
            result.append(node.val)
            # 转向右子树
            node = node.right

        return result

    def goAlongLeftBranch(self, root: Optional[TreeNode], stack: List[TreeNode]) -> None:
        if root is None:
            return

        node = root
        while node:
            # 将该结点入栈暂存
            stack.append(node)
            node = node.left


class Solution3:
    """Inorder traversal by iteration."""

    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        result = []

        if root is None:
            return result

        stack = []
        node = root
        while True:
            if node:
                # 当前节点入栈，并深入遍历其左子树
                stack.append(node)
                node = node.left
            elif stack:
                # 已到达左子树末端，尚未访问的最低祖先节点出栈，计入结果
                node = stack.pop(-1)
                result.append(node.val)
                node = node.right  # 遍历其右子树
            else:
                break  # 遍历完成

        return result
