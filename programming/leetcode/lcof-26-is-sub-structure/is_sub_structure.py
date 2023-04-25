# @problem: 剑指 Offer 26. 树的子结构
# @file: is_sub_structure.py
# @url: https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof
# @description:
#
# 输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)
# B是A的子结构， 即 A中有出现和B相同的结构和节点值。
# 例如:
# 给定的树 A:
#      3
#     / \
#    4   5
#   / \
#  1   2
# 给定的树 B：
#    4
#   /
#  1
# 返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。
# 示例 1：
# 输入：A = [1,2,3], B = [3,1]
# 输出：false
#
# 示例 2：
# 输入：A = [3,4,5,1,2], B = [4,1]
# 输出：true
# 限制：
# 0 <= 节点个数 <= 10000
#
# @author: Du Ang
# @date: Apr 21, 2023

from typing import List


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def containsSameRootTree(self, A: TreeNode, B: TreeNode) -> bool:
        if B is None:
            return True
        if A is None:
            return False
        if A.val != B.val:
            return False
        else:
            return self.containsSameRootTree(A.left, B.left) and self.containsSameRootTree(
                A.right, B.right
            )

    def isSubStructure(self, A: TreeNode, B: TreeNode) -> bool:
        res = False
        if A is None or B is None:
            return res
        if A.val == B.val:
            res = self.containsSameRootTree(A, B)
        if not res:
            res = self.isSubStructure(A.left, B)
        if not res:
            res = self.isSubStructure(A.right, B)
        return res
