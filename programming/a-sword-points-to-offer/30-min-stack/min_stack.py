# -*- coding:utf-8 -*-
# 题目描述
# 定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的min函数（时间
# 复杂度应为O(1)）。

# 维护一个辅助栈，在 push/pop 的同时，压入/弹出当前的最小元素
class Solution:
    stack = []
    min_stack = []

    def push(self, node):
        # write code here
        self.stack.append(node)
        if self.min_stack:
            if node < self.min_stack[-1]:
                self.min_stack.append(node)
            else:
                self.min_stack.append(self.min_stack[-1])
        else:
            self.min_stack.append(node)

    def pop(self):
        # write code here
        if self.stack and self.min_stack:
            self.min_stack.pop()
            self.stack.pop()
            
    def top(self):
        # write code here
        if self.stack:
            return self.stack[-1]

    def min(self):
        # write code here
        if self.min_stack:
            return self.min_stack[-1]
