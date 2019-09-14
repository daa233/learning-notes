# -*- coding:utf-8 -*-

# 题目描述
# 用两个栈来实现一个队列，完成队列的Push和Pop操作。队列中的元素为int类型。

class Solution:
    stack1 = []
    stack2 = []

    def push(self, node):
        # write code here
        self.stack1.append(node)

    def pop(self):
        # return xx
        if not self.stack2:
            # stack2 为空，将 stack1 中的元素压入 stack2
            while len(self.stack1) > 1:
                self.stack2.append(self.stack1.pop())
            return self.stack1.pop()
        else:
            # stack2 不为空，直接 pop 栈顶元素
            return self.stack2.pop()
        