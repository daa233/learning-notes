# @problem: 155. Min Stack
# @file: min_stack.py
# @url: https://leetcode-cn.com/problems/min-stack
# @description:
#
# Design a stack that supports push, pop, top, and retrieving the
# minimum element in constant time.
#
# push(x) -- Push element x onto stack.
# pop() -- Removes the element on top of the stack.
# top() -- Get the top element.
# getMin() -- Retrieve the minimum element in the stack.
#
# Example:
# MinStack minStack = new MinStack();
# minStack.push(-2);
# minStack.push(0);
# minStack.push(-3);
# minStack.getMin();   --> Returns -3.
# minStack.pop();
# minStack.top();      --> Returns 0.
# minStack.getMin();   --> Returns -2.
#
# @author: Du Ang
# @date: Sep 14, 2019


class MinStack:
    """
    维护一个辅助栈 min_stack，在执行 push、pop 操作时，同时将此时 min_val_stack 栈中对应的最小元素也
    push 或 pop。
    """

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.stack = []
        self.min_stack = []

    def push(self, x: int) -> None:
        self.stack.append(x)
        if self.min_stack:
            min_val = self.getMin()
            if x < min_val:
                min_val = x
        else:
            min_val = x
        self.min_stack.append(min_val)

    def pop(self) -> None:
        self.stack.pop(-1)
        self.min_stack.pop(-1)

    def top(self) -> int:
        return self.stack[-1]

    def getMin(self) -> int:
        return self.min_stack[-1]


# Your MinStack object will be instantiated and called as such:
# obj = MinStack()
# obj.push(x)
# obj.pop()
# param_3 = obj.top()
# param_4 = obj.getMin()
