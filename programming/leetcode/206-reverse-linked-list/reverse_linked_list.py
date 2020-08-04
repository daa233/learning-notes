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


# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class List:
    def __init__(self, nums):
        if not nums:
            self.head = None
        self.head = ListNode(nums[0])
        node = self.head
        for n in nums[1:]:
            node.next = ListNode(n)
            node = node.next

    @staticmethod
    def print(head):
        vals = []
        node = head

        while node:
            vals.append(str(node.val))
            node = node.next
        print('->'.join(vals))


class Solution1:
    def reverseList(self, head: ListNode) -> ListNode:
        if not head or not head.next:
            return head
        l = []
        while head:
            l.append(head)
            head = head.next
        rhead = l.pop()
        node = rhead
        while l:
            node.next = l.pop()
            node = node.next
        node.next = None
        return rhead


class Solution:
    def reverseList(self, head: ListNode) -> ListNode:
        if not head or not head.next:
            return head
        rhead = node = head
        head = head.next
        node.next = None
        while head:
            rhead = head
            head = head.next
            rhead.next = node
            node = rhead

        return rhead


if __name__ == "__main__":
    num_list = [1, 2, 3, 4]
    l = List(num_list)
    List.print(l.head)
    rhead = Solution().reverseList(l.head)
    List.print(rhead)
