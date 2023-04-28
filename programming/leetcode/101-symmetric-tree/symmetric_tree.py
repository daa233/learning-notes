# @problem: 101. Symmetric Tree
# @file: symmetric_tree.py
# @url: https://leetcode-cn.com/problems/symmetric-tree
# @description:
#
# Given the root of a binary tree, check whether it is a mirror of
# itself (i.e., symmetric around its center).
# Example 1:
#
# Input: root = [1,2,2,3,4,4,3]
# Output: true
#
# Example 2:
#
# Input: root = [1,2,2,null,3,null,3]
# Output: false
#
# Constraints:
#
# The number of nodes in the tree is in the range [1, 1000].
# -100 <= Node.val <= 100
#
# Follow up: Could you solve it both recursively and iteratively?
#
# @author: Du Ang
# @date: Apr 28, 2023


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def checkSymmetric(self, A: TreeNode, B: TreeNode) -> bool:
        if A is None and B is None:
            return True
        elif A is None or B is None:
            return False

        if A.val == B.val:
            left_symm = self.checkSymmetric(A.left, B.right)
            if not left_symm:
                return False
            right_symm = self.checkSymmetric(A.right, B.left)
            if right_symm:
                return True

        return False

    def isSymmetric(self, root: TreeNode) -> bool:
        if root is None:
            return True

        return self.checkSymmetric(root.left, root.right)


class Solution2:
    def isSymmetric(self, root: TreeNode) -> bool:
        if root is None:
            return True

        left_q = [root.left]
        right_q = [root.right]
        while left_q and right_q:
            left_root = left_q.pop()
            right_root = right_q.pop()
            if left_root is None and right_root is None:
                continue
            elif left_root is None or right_root is None:
                return False

            if left_root.val == right_root.val:
                left_q.append(left_root.left)
                right_q.append(right_root.right)
                left_q.append(left_root.right)
                right_q.append(right_root.left)
            else:
                return False
        return True
