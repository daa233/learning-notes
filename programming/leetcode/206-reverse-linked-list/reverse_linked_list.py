# @problem: 206. Reverse Linked List
# @file: reverse_linked_list.py
# @url: https://leetcode-cn.com/problems/reverse-linked-list
# @description:
#
# Reverse a singly linked list.
# Example:
# Input: 1->2->3->4->5->NULL
# Output: 5->4->3->2->1->NULL
#
# Follow up:
# A linked list can be reversed either iteratively or recursively. Could
# you implement both?
#
# @author: Du Ang
# @date: Aug 04, 2020

from typing import List


class ListNode:
    """Definition for singly-linked list."""

    def __init__(self, x):
        self.val = x
        self.next = None

    @classmethod
    def from_nums(cls, nums: List[int]) -> "ListNode":
        head = None
        prev = None
        for num in nums:
            node = ListNode(num)
            if not head:
                head = node
                prev = node
            else:
                prev.next = node
                prev = node

        return head

    def print(self) -> str:
        node = self
        result = []
        while node:
            result.append(str(node.val))
            node = node.next
        if result:
            print("->".join(result))
        else:
            print("null")


class Solution:
    """迭代法"""

    def reverseList(self, head: ListNode) -> ListNode:
        new_head = None
        while head:
            left = head.next
            head.next = new_head
            new_head = head
            head = left
        return new_head


class Solution2:
    """递归法"""

    def reverseList(self, head: ListNode) -> ListNode:
        if head is None or head.next is None:
            return head

        new_head = self.reverseList(head.next)
        if not new_head:
            return new_head

        # 找到 new_head 的最后一个节点，让其 next 指向 head，
        # 并且将 head.next 指向 None
        node = new_head
        while node.next:
            node = node.next
        node.next = head
        head.next = None

        return new_head


class Solution3:
    """递归法"""

    def reverseList(self, head: ListNode) -> ListNode:
        if head is None or head.next is None:
            return head

        new_head = self.reverseList(head.next)

        # 找到 new_head 的最后一个节点，让其 next 指向 head，
        # 注意：head.next 在翻转后即指向 new_head 的最后一个节点
        # 并且将 head.next 指向 None
        head.next.next = head
        head.next = None

        return new_head


if __name__ == "__main__":
    nums = [1, 2, 3, 4]
    head = ListNode.from_nums(nums)
    head.print()
    new_head = Solution().reverseList(head)
    new_head.print()
    head = ListNode.from_nums(nums)
    new_head2 = Solution2().reverseList(head)
    new_head2.print()
    head = ListNode.from_nums(nums)
    new_head3 = Solution3().reverseList(head)
    new_head3.print()
