# @problem: 剑指 Offer 32 - I. 从上到下打印二叉树
# @file: level_order.py
# @url: https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-lcof
# @description:
#
# 从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。
# 例如:
# 给定二叉树: [3,9,20,null,null,15,7],
#     3
#    / \
#   9  20
#     /  \
#    15   7
#
# 返回：
# [3,9,20,15,7]
#
# 提示：
#
# 节点总数 <= 1000
#
# @author: Du Ang
# @date: Apr 20, 2023

from typing import List


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def levelOrder(self, root: TreeNode) -> List[int]:
        res = []
        if not root:
            return res
        q = [root]
        while q:
            node = q.pop(0)
            res.append(node.val)
            if node.left:
                q.append(node.left)
            if node.right:
                q.append(node.right)
        return res
