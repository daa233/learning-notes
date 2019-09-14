# -*- coding:utf-8 -*-
# 题目描述
# 从上往下打印出二叉树的每个节点，同层节点从左至右打印。

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

# 借助队列，广度优先搜索
class Solution:
    # 返回从上到下每个节点值列表，例：[1,2,3]
    def PrintFromTopToBottom(self, root):
        # write code here
        res = []
        if not root:
            return res
        queue = [root]
        while queue:
            node = queue.pop(0)
            res.append(node.val)
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
        return res
