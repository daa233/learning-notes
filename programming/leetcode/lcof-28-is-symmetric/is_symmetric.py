# @problem: 剑指 Offer 28. 对称的二叉树
# @file: is_symmetric.py
# @url: https://leetcode-cn.com/problems/dui-cheng-de-er-cha-shu-lcof
# @description:
#
# 请实现一个函数，用来判断一棵二叉树是不是对称的。如果一棵二叉树和它的镜像一样，那么它是对称的。
# 例如，二叉树 [1,2,2,3,4,4,3] 是对称的。
#     1
#    / \
#   2   2
#  / \ / \
# 3  4 4  3
# 但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:
#     1
#    / \
#   2   2
#    \   \
#    3    3
# 示例 1：
# 输入：root = [1,2,2,3,4,4,3]
# 输出：true
#
# 示例 2：
# 输入：root = [1,2,2,null,3,null,3]
# 输出：false
# 限制：
# 0 <= 节点个数 <= 1000
# 注意：本题与主站 101 题相同：https://leetcode-cn.com/problems/symmetric-tree/
#
# @author: Du Ang
# @date: Apr 28, 2023


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution1:
    def mirrorTree(self, root: TreeNode) -> TreeNode:
        if root is None:
            return None

        copy_node = TreeNode(root.val)
        left_child = self.mirrorTree(root.left)
        right_child = self.mirrorTree(root.right)
        copy_node.left = right_child
        copy_node.right = left_child

        return copy_node

    def isSame(self, A: TreeNode, B: TreeNode) -> bool:
        if A is None and B is None:
            return True
        elif A is None or B is None:
            return False

        if A.val == B.val:
            left_same = self.isSame(A.left, B.left)
            if not left_same:
                return False
            right_same = self.isSame(A.right, B.right)
            if right_same:
                return True

        return False

    def isSymmetric(self, root: TreeNode) -> bool:
        mirror_tree = self.mirrorTree(root)
        return self.isSame(root, mirror_tree)


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
