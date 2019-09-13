# -*- coding:utf-8 -*-
# 题目描述
# 输入一个链表，按链表从尾到头的顺序返回一个ArrayList。

class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

# 使用栈
class Solution:
    # 返回从尾部到头部的列表值序列，例如[1,2,3]
    def printListFromTailToHead(self, listNode):
        # write code here
        stack = []
        node = listNode
        while node:
            stack.append(node.val)
            node = node.next
        res = []
        while stack:
            res.append(stack.pop())
        return res

# 使用递归（调用层级过深时可能会溢出）
class Solution1:
    # 返回从尾部到头部的列表值序列，例如[1,2,3]
    def printListFromTailToHead(self, listNode):
        # write code here
        if listNode:
            next_res = self.printListFromTailToHead(listNode.next)
            return next_res + [listNode.val]
        else:
            return []
        