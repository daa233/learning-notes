# @problem: 232. Implement Queue using Stacks
# @file: implement_queue_using_stacks.py
# @url: https://leetcode-cn.com/problems/implement-queue-using-stacks
# @description: 
# 
# Implement the following operations of a queue using stacks.
# 
# push(x) -- Push element x to the back of queue.
# pop() -- Removes the element from in front of queue.
# peek() -- Get the front element.
# empty() -- Return whether the queue is empty.
# 
# Example:
# MyQueue queue = new MyQueue();
# queue.push(1);
# queue.push(2);
# queue.peek();  // returns 1
# queue.pop();   // returns 1
# queue.empty(); // returns false
# Notes:
# 
# You must use only standard operations of a stack -- which means only
# push to top, peek/pop from top, size, and is empty operations are
# valid.
# Depending on your language, stack may not be supported natively. You
# may simulate a stack by using a list or deque (double-ended queue), as
# long as you use only standard operations of a stack.
# You may assume that all operations are valid (for example, no pop or
# peek operations will be called on an empty queue).
# 
# @author: Du Ang
# @date: Sep 14, 2019


class MyQueue:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.stack1 = []
        self.stack2 = []

    def push(self, x: int) -> None:
        """
        Push element x to the back of queue.
        """
        self.stack1.append(x)

    def pop(self) -> int:
        """
        Removes the element from in front of queue and returns that element.
        """
        if self.stack2:
            return self.stack2.pop()
        elif self.stack1:
            while len(self.stack1) > 1:
                self.stack2.append(self.stack1.pop())
            return self.stack1.pop()
        else:
            return None

    def peek(self) -> int:
        """
        Get the front element.
        """
        if self.stack2:
            return self.stack2[-1]
        elif self.stack1:
            while self.stack1:
                self.stack2.append(self.stack1.pop())
            return self.stack2[-1]
        else:
            return None

    def empty(self) -> bool:
        """
        Returns whether the queue is empty.
        """
        return not (self.stack1 or self.stack2)
        

# Your MyQueue object will be instantiated and called as such:
# obj = MyQueue()
# obj.push(x)
# param_2 = obj.pop()
# param_3 = obj.peek()
# param_4 = obj.empty()



