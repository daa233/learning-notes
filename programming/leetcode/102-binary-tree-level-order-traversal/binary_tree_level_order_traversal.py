# @problem: 102. Binary Tree Level Order Traversal
# @file: binary_tree_level_order_traversal.py
# @url: https://leetcode-cn.com/problems/binary-tree-level-order-traversal
# @description: 
# 
# Given a binary tree, return the level order traversal of its nodes'
# values. (ie, from left to right, level by level).
# For example:
# Given binary tree [3,9,20,null,null,15,7],
#     3
#    / \
#   9  20
#     /  \
#    15   7
# 
# return its level order traversal as:
# [
#   [3],
#   [9,20],
#   [15,7]
# ]
# 
# @author: Du Ang
# @date: Sep 14, 2019

from typing import List

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

# BFS
class Solution:
    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        res = []
        if not root:
            return res
        level = [root]
        while level:
            next_level = []
            level_res = []
            for node in level:
                level_res.append(node.val)
                if node.left:
                    next_level.append(node.left)
                if node.right:
                    next_level.append(node.right)
            level = next_level
            res.append(level_res)
        return res
        
        

