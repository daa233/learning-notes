# @problem: 剑指 Offer 06. 从尾到头打印链表
# @file: reverse_print.py
# @url: https://leetcode-cn.com/problems/cong-wei-dao-tou-da-yin-lian-biao-lcof
# @description:
#
# 输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。
# 示例 1：
# 输入：head = [1,3,2]
# 输出：[2,3,1]
# 限制：
# 0 <= 链表长度 <= 10000
#
# @author: Du Ang
# @date: Jan 07, 2021

from typing import List


class ListNode:
    """Definition for singly-linked list."""

    def __init__(self, x):
        self.val = x
        self.next = None

    def __repr__(self):
        return "ListNode({})".format(self.val)


class Solution1:
    """
    遍历链表，将所有元素依次存入 list 中，每次从头部插入。
    时间复杂度：O(n)
    空间复杂度：O(n)
    """

    def reversePrint(self, head: ListNode) -> List[int]:
        outputs = []
        node = head
        while node:
            outputs.insert(0, node.val)
            node = node.next
        return outputs


class Solution:
    """
    遍历链表，将所有元素依次存入 list 中，然后反转一下。
    时间复杂度：O(n)
    空间复杂度：O(n)
    """

    def reversePrint(self, head: ListNode) -> List[int]:
        outputs = []
        node = head
        while node:
            outputs.append(node.val)
            node = node.next
        outputs.reverse()
        return outputs


class Solution2:
    """
    采用递归的方式，每访问到一个节点，先递归输出它后面的节点，再输出该节点自身。
    当链表非常长的时候，可能会导致函数调用的层级很深，从而有可能导致函数调用栈溢出。
    因此用栈基于循环实现的代码的鲁棒性要好一些。
    """

    def reversePrint(self, head: ListNode) -> List[int]:
        self.outputs = []
        self._helper(head)
        return self.outputs

    def _helper(self, head: ListNode) -> ListNode:
        if head:
            node = self._helper(head.next)
            self.outputs.append(head.val)
            return node


def create_linked_list(data: List[int]) -> ListNode:
    """Create a linked list from a data list"""
    if not data:
        return None

    head = ListNode(data[0])
    node = head
    for val in data[1:]:
        node.next = ListNode(val)
        node = node.next

    return head


def print_linked_list(head: ListNode) -> ListNode:
    """Print the linked list and keep it unchanged."""
    node = head
    vals = []
    while node:
        vals.append(str(node.val))
        node = node.next

    print("LinkedList: " + " -> ".join(vals))

    return head


if __name__ == "__main__":

    data_list = [[1, 3, 2], [3, 5, 6, 7, 9]]

    s = Solution()

    for data in data_list:
        linked_list = create_linked_list(data)
        print_linked_list(linked_list)
        out = s.reversePrint(linked_list)
        print(out)
