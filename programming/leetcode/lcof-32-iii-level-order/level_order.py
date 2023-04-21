# @problem: 剑指 Offer 32 - III. 从上到下打印二叉树 III
# @file: level_order.py
# @url: https://leetcode-cn.com/problems/cong-shang-dao-xia-da-yin-er-cha-shu-iii-lcof
# @description:
#
# 请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行
# 以此类推。
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
#   [20,9],
#   [15,7]
# ]
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
                if level % 2 == 0:
                    level_res.append(node.val)
                else:
                    level_res.insert(0, node.val)
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
