# @problem: 145. Binary Tree Postorder Traversal
# @file: binary_tree_postorder_traversal.py
# @url: https://leetcode-cn.com/problems/binary-tree-postorder-traversal
# @description:
#
# Given the root of a binary tree, return the postorder traversal of its
# nodes' values.
# Example 1:
#
# Input: root = [1,null,2,3]
# Output: [3,2,1]
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
# The number of the nodes in the tree is in the range [0, 100].
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
    """Postorder traversal by recursion."""

    def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        self.result = []
        self._helper(root)
        return self.result

    def _helper(self, root: TreeNode) -> List[int]:
        if root is None:
            return None

        self._helper(root.left)
        self._helper(root.right)
        self.result.append(root.val)


class Solution2:
    """
    Postorder traversal by iteration.
    Goto the HVLFL (higherst leaf visible from left) and backtrace.
    """

    def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        if root is None:
            return []

        result = []
        node = root
        stack = [node]

        while stack:
            top_node = stack[-1]
            if top_node.left != node and top_node.right != node:
                # 若栈顶节点 top_node 非当前节点 node 的父亲，则一定是当前节点
                # 的右兄弟，此时需要遍历以其右兄弟为根节点的子树，寻找其 HLVFL
                self.gotoHLVFL(top_node, stack)
            # 弹出栈顶节点（即前一节点的后继），并访问之
            node = stack.pop(-1)
            result.append(node.val)

        return result

    def gotoHLVFL(self, root: Optional[TreeNode], stack: List[TreeNode]) -> None:
        """
        寻找以当前 root 节点为根节点的 HLVFL（higherst leaf visible from left），
        将途径节点结果按顺序存放到 stack 中。
        """
        if root is None:
            return

        node = root
        while node:
            if node.left:  # 尽可能向左
                if node.right:
                    # 若有右孩子，优先入栈
                    stack.append(node.right)
                # 左孩子入栈
                stack.append(node.left)
                node = node.left
            else:
                # 实不得已，才向右
                if node.right:
                    stack.append(node.right)
                node = node.right


class Solution3:
    """
    Postorder traversal by iteration.
    Based on preorder traversal (VLR), changed its order to VRL and then
    reverse to LRV (postorder).
    """

    def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        result = []

        if root is None:
            return result

        stack = [root]
        while stack:
            node = stack.pop()
            result.append(node.val)
            # 调整为先左后右入栈
            if node.left:
                stack.append(node.left)
            if node.right:
                stack.append(node.right)

        # 翻转结果顺序，VRL -> LRV
        result.reverse()

        return result
