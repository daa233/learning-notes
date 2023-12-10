# @problem: LCR 184. 设计自助结算系统
# @file: checkout.py
# @url: https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof
# @description: 
#
# 请设计一个自助结账系统，该系统需要通过一个队列来模拟顾客通过购物车的结算过程，需要实现的功能有：
#
# get_max()：获取结算商品中的最高价格，如果队列为空，则返回 -1
# add(value)：将价格为 value 的商品加入待结算商品队列的尾部
# remove()：移除第一个待结算的商品价格，如果队列为空，则返回 -1
#
# 注意，为保证该系统运转高效性，以上函数的均摊时间复杂度均为 O(1)
# 示例 1：
#
# 输入:
# ["Checkout","add","add","get_max","remove","get_max"]
# [[],[4],[7],[],[],[]]
#
# 输出: [null,null,null,7,4,7]
#
# 示例 2：
#
# 输入:
# ["Checkout","remove","get_max"]
# [[],[],[]]
#
# 输出: [null,-1,-1]
#
# 提示：
#
# 1 <= get_max, add, remove 的总操作数 <= 10000
# 1 <= value <= 10^5
#
# @author: Du Ang
# @date: Dec 10, 2023


class Checkout:
    """通过单调双向队列实现"""

    def __init__(self):
        self.data = []
        self.deque = []

    def get_max(self) -> int:
        """获取结算商品中的最高价格，如果队列为空，则返回 -1"""
        if not self.deque:
            return -1
        return self.deque[0]

    def add(self, value: int) -> None:
        """将价格为 `value` 的商品加入待结算商品队列的尾部"""
        self.data.append(value)
        while self.deque and value > self.deque[-1]:
            self.deque.pop(-1)
        self.deque.append(value)

    def remove(self) -> int:
        """移除第一个待结算的商品价格，如果队列为空，则返回 -1"""
        if not self.data:
            return -1
        value = self.data.pop(0)
        if value == self.deque[0]:
            self.deque.pop(0)
        return value



# Your Checkout object will be instantiated and called as such:
# obj = Checkout()
# param_1 = obj.get_max()
# obj.add(value)
# param_3 = obj.remove()



