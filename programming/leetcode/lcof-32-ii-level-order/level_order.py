# @problem: 剑指 Offer 32 - II. 从上到下打印二叉树 II
# @file: level_order.py
# @url: https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-ii-lcof
# @description:
#
# 从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。
# 例如:
# 给定二叉树: [3,9,20,null,null,15,7],
#     3
#    / \
#   9  20
#     /  \
#    15   7
#
# 返回其层次遍历结果：
# [
#   [3],
#   [9,20],
#   [15,7]
# ]
#
# 提示：
#
# 节点总数 <= 1000
#
# 注意：本题与主站 102 题相同：https://leetcode-cn.com/problems/binary-tree-level-
# order-traversal/
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
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        res = []
        if not root:
            return res
        level_res = []
        current_level = 0
        q = [(0, root)]
        while q:
            level, node = q.pop(0)
            if level <= current_level:
                level_res.append(node.val)
            else:
                res.append(level_res)
                level_res = [node.val]
                current_level += 1
            if node.left:
                q.append((level + 1, node.left))
            if node.right:
                q.append((level + 1, node.right))
        if level_res:
            res.append(level_res)
        return res
