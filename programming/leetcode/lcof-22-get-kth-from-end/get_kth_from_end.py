# @problem: 剑指 Offer 22. 链表中倒数第k个节点
# @file: get_kth_from_end.py
# @url: https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof
# @description:
#
# 输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。例如，一个链表有6个节点
# ，从头节点开始，它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个节点是值为4的节点。
# 示例：
# 给定一个链表: 1->2->3->4->5, 和 k = 2.
#
# 返回链表 4->5.
#
# @author: Du Ang
# @date: Jan 12, 2021

from typing import List, Union


class ListNode:
    """Definition for singly-linked list."""

    def __init__(self, x):
        self.val = x
        self.next = None

    def __repr__(self):
        return "ListNode({})".format(self.val)


class Solution1:
    """ Use a dict to record every node. """

    def getKthFromEnd(self, head: ListNode, k: int) -> ListNode:
        node = head
        map_dict = {}
        i = 0
        while node:
            i += 1
            map_dict[i] = node
            node = node.next

        if i > 0:
            return map_dict[i - k + 1]
        else:
            return None


class Solution2:
    """ Traverse twice. Get the length of the linked list in the first traversal. """

    def getKthFromEnd(self, head: ListNode, k: int) -> ListNode:
        node = head
        count = 0
        while node:
            count += 1
            node = node.next

        if count > 0:
            node = head
            i = 0
            while node:
                i += 1
                if i == count - k + 1:
                    return node
                node = node.next
        else:
            return None


class Solution:
    """ Use double pointers """

    def getKthFromEnd(self, head: ListNode, k: int) -> ListNode:
        node1 = head
        node2 = head

        for _ in range(k):
            if node1:
                node1 = node1.next
            else:
                return None

        while node1:
            node1 = node1.next
            node2 = node2.next

        return node2


def preprocess_wrapper(func):
    """ Used to deal with multiple input arguments. """

    def wrapper(data: List[Union[List[int], int]]):
        head, k = data
        return func(head), k

    return wrapper


@preprocess_wrapper
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


@preprocess_wrapper
def print_input(head: ListNode) -> ListNode:
    head = print_linked_list(head)
    return head


if __name__ == "__main__":
    import sys

    sys.path.insert(0, "../")
    from util import Runner

    data = [
        "[[1,2,3,4,5], 2]",
        "[[1], 1]",
        "[[1, 2, 3], 3]",
        "[[1, 2, 3], 0]",
        "[[1, 2, 3], 5]",
    ]

    runner = Runner(
        env=locals(),
        data=data,
        verbose=True,
        preprocess=["create_linked_list", "print_input"],
        postprocess=["print_linked_list"],
    )
    runner.exec()
