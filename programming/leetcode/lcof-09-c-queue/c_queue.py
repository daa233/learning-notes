# @problem: 剑指 Offer 09. 用两个栈实现队列
# @file: c_queue.py
# @url: https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof
# @description:
#
# 用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead
# ，分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 -1 )
# 示例 1：
#
# 输入：
# ["CQueue","appendTail","deleteHead","deleteHead","deleteHead"]
# [[],[3],[],[],[]]
# 输出：[null,null,3,-1,-1]
#
# 示例 2：
#
# 输入：
# ["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteH
# ead"]
# [[],[],[5],[2],[],[]]
# 输出：[null,-1,null,null,5,2]
#
# 提示：
#
# 1 <= values <= 10000
# 最多会对 appendTail、deleteHead 进行 10000 次调用
#
# @author: Du Ang
# @date: Feb 03, 2023


class CQueue:
    def __init__(self):
        self.stack1 = []  # only for input
        self.stack2 = []  # only for output

    def appendTail(self, value: int) -> None:
        self.stack1.append(value)

    def deleteHead(self) -> int:
        if self.stack2:
            return self.stack2.pop(-1)
        elif self.stack1:
            while self.stack1:
                self.stack2.append(self.stack1.pop(-1))
            return self.stack2.pop(-1)
        else:
            return -1


# Your CQueue object will be instantiated and called as such:
# obj = CQueue()
# obj.appendTail(value)
# param_2 = obj.deleteHead()
