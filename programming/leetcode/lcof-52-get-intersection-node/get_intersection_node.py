# @problem: 剑指 Offer 52. 两个链表的第一个公共节点
# @file: get_intersection_node.py
# @url: https://leetcode-cn.com/problems/liang-ge-lian-biao-de-di-yi-ge-gong-gong-jie-dian-lcof
# @description:
#
# 输入两个链表，找出它们的第一个公共节点。
# 如下面的两个链表：
#
# 在节点 c1 开始相交。
# 示例 1：
#
# 输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA
# = 2, skipB = 3
# 输出：Reference of the node with value = 8
# 输入解释：相交节点的值为 8 （注意，如果两个列表相交则不能为 0）。从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B
# 为 [5,0,1,8,4,5]。在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
#
# 示例 2：
#
# 输入：intersectVal = 2, listA = [0,9,1,2,4], listB = [3,2,4], skipA = 3,
# skipB = 1
# 输出：Reference of the node with value = 2
# 输入解释：相交节点的值为 2 （注意，如果两个列表相交则不能为 0）。从各自的表头开始算起，链表 A 为 [0,9,1,2,4]，链表 B
# 为 [3,2,4]。在 A 中，相交节点前有 3 个节点；在 B 中，相交节点前有 1 个节点。
#
# 示例 3：
#
# 输入：intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB
# = 2
# 输出：null
# 输入解释：从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。由于这两个链表不相交，所以 intersectVal
# 必须为 0，而 skipA 和 skipB 可以是任意值。
# 解释：这两个链表不相交，因此返回 null。
#
# 注意：
#
# 如果两个链表没有交点，返回 null.
# 在返回结果后，两个链表仍须保持原有的结构。
# 可假定整个链表结构中没有循环。
# 程序尽量满足 O(n) 时间复杂度，且仅用 O(1) 内存。
# 本题与主站 160 题相同：https://leetcode-cn.com/problems/intersection-of-two-linked-lists/
#
# @author: Du Ang
# @date: May 10, 2023


# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution1:
    """哈希表"""

    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        hash_table = set()
        nodeA = headA
        nodeB = headB

        while nodeA or nodeB:
            if nodeA:
                if nodeA in hash_table:
                    return nodeA
                else:
                    hash_table.add(nodeA)
                nodeA = nodeA.next
            if nodeB:
                if nodeB in hash_table:
                    return nodeB
                else:
                    hash_table.add(nodeB)
                nodeB = nodeB.next

        return None


class Solution2:
    """哈希表"""

    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        hash_table = set()

        nodeA = headA
        while nodeA:
            hash_table.add(nodeA)
            nodeA = nodeA.next

        if not hash_table:
            return None

        nodeB = headB
        while nodeB:
            if nodeB in hash_table:
                return nodeB
            nodeB = nodeB.next

        return None


class Solution:
    """双指针"""

    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        if headA is None or headB is None:
            return None

        pA = headA
        pB = headB

        while pA != pB:
            if pA is None:
                pA = headB
            else:
                pA = pA.next
            if pB is None:
                pB = headA
            else:
                pB = pB.next

        return pA
