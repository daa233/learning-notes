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
    def reversePrint(self, head: ListNode) -> List[int]:
        outputs = []
        node = head
        while node:
            outputs.insert(0, node.val)
            node = node.next
        return outputs


class Solution:
    def reversePrint(self, head: ListNode) -> List[int]:
        outputs = []
        node = head
        while node:
            outputs.append(node.val)
            node = node.next
        outputs.reverse()
        return outputs


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

    print("Input LinkedList: " + " -> ".join(vals))

    return head


if __name__ == "__main__":
    import sys

    sys.path.insert(0, "../")
    from util import Runner

    data = ["[1,3,2]", "[3,5,6,7,9]"]

    runner = Runner(
        env=locals(),
        data=data,
        verbose=True,
        preprocess=["create_linked_list", "print_linked_list"],
    )
    runner.exec()
