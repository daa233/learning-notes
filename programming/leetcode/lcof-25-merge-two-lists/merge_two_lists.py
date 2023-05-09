# @problem: 剑指 Offer 25. 合并两个排序的链表
# @file: merge_two_lists.py
# @url: https://leetcode-cn.com/problems/he-bing-liang-ge-pai-xu-de-lian-biao-lcof
# @description:
#
# 输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的。
# 示例1：
# 输入：1->2->4, 1->3->4
# 输出：1->1->2->3->4->4
# 限制：
# 0 <= 链表长度 <= 1000
# 注意：本题与主站 21 题相同：https://leetcode-cn.com/problems/merge-two-sorted-
# lists/
#
# @author: Du Ang
# @date: May 09, 2023


# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    """Iteration"""

    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        prev = None
        head = None

        while l1 or l2:
            if l1 and l2:
                if l1.val <= l2.val:
                    val = l1.val
                    l1 = l1.next
                else:
                    val = l2.val
                    l2 = l2.next
            elif l1 and l2 is None:
                val = l1.val
                l1 = l1.next
            else:
                val = l2.val
                l2 = l2.next

            node = ListNode(val)
            if prev is None:
                head = node
            else:
                prev.next = node
            prev = node

        return head


class Solution2:
    """Recursion"""

    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        if l1 and l2:
            if l1.val <= l2.val:
                node = l1
                node.next = self.mergeTwoLists(l1.next, l2)
            else:
                node = l2
                node.next = self.mergeTwoLists(l1, l2.next)
        elif l1 and not l2:
            node = l1
        elif not l1 and l2:
            node = l2
        else:
            node = None
        return node
