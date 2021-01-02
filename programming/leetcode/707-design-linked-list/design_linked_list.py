# @problem: 707. Design Linked List
# @file: design_linked_list.py
# @url: https://leetcode-cn.com/problems/design-linked-list
# @description:
# Design your implementation of the linked list. You can choose to use
# the singly linked list or the doubly linked list. A node in a
# singly linked list should have two attributes: val and next. val is
# the value of the current node, and next is a pointer/reference to the
# next node. If you want to use the doubly linked list, you will
# need one more attribute prev to indicate the previous node in the
# linked list. Assume all nodes in the linked list are 0-indexed.
# Implement these functions in your linked list class:
#
# get(index) : Get the value of the index-th node in the linked list. If
# the index is invalid, return -1.
# addAtHead(val) : Add a node of value val before the first element of
# the linked list. After the insertion, the new node will be the first
# node of the linked list.
# addAtTail(val) : Append a node of value val to the last element of the
# linked list.
# addAtIndex(index, val) : Add a node of value val before the index-
# th node in the linked list. If index equals to the length of linked
# list, the node will be appended to the end of linked list. If index is
# greater than the length, the node will not be inserted.
# deleteAtIndex(index) : Delete the index-th node in the linked list, if
# the index is valid.
#
# Example:
#
# Input:
# ["MyLinkedList","addAtHead","addAtTail","addAtIndex","get","deleteAtIn
# dex","get"]
# [[],[1],[3],[1,2],[1],[1],[1]]
# Output:
# [null,null,null,null,2,null,3]
#
# Explanation:
# MyLinkedList linkedList = new MyLinkedList(); // Initialize empty
# LinkedList
# linkedList.addAtHead(1);
# linkedList.addAtTail(3);
# linkedList.addAtIndex(1, 2);  // linked list becomes 1->2->3
# linkedList.get(1);            // returns 2
# linkedList.deleteAtIndex(1);  // now the linked list is 1->3
# linkedList.get(1);            // returns 3
#
# Constraints:
#
# 0 <= index,val <= 1000
# Please do not use the built-in LinkedList library.
# At most 2000 calls will be made to get, addAtHead, addAtTail,
# addAtIndex and deleteAtIndex.
#
# @author: Du Ang
# @date: Jul 26, 2020


class SinglyListNode:
    def __init__(self, val):
        self.val = val
        self.next = None

    def __str__(self):
        return str(self.val)


class MyLinkedList:
    def __init__(self):
        """
        Initialize your data structure here.
        """
        # NOTE: the pseudo head is just the sentinel node of the list
        self.head = SinglyListNode(0)
        self.size = 0

    def get(self, index: int) -> int:
        """
        Get the value of the index-th node in the linked list. If the index is invalid, return -1.
        """
        if index < 0 or index >= self.size:
            return -1

        cur = self.head
        for _ in range(index + 1):
            cur = cur.next
        return cur.val

    def addAtHead(self, val: int) -> None:
        """
        Add a node of value val before the first element of the linked list. After the insertion,
        the new node will be the first node of the linked list.
        """
        self.addAtIndex(0, val)

    def addAtTail(self, val: int) -> None:
        """
        Append a node of value val to the last element of the linked list.
        """
        self.addAtIndex(self.size, val)

    def addAtIndex(self, index: int, val: int) -> None:
        """
        Add a node of value val before the index-th node in the linked list. If index equals to the
        length of linked list, the node will be appended to the end of linked list. If index is
        greater than the length, the node will not be inserted.
        """
        if index > self.size:
            return

        if index < 0:
            index = 0

        self.size += 1
        pred = self.head
        for _ in range(index):
            pred = pred.next

        new_node = SinglyListNode(val)
        new_node.next = pred.next
        pred.next = new_node

    def deleteAtIndex(self, index: int) -> None:
        """
        Delete the index-th node in the linked list, if the index is valid.
        """
        if index < 0 or index >= self.size:
            return

        self.size -= 1
        pred = self.head
        for _ in range(index):
            pred = pred.next

        pred.next = pred.next.next

    def show(self):
        vals = []
        pred = self.head
        for _ in range(self.size):
            pred = pred.next
            vals.append(str(pred.val))
        print(" -> ".join(vals))


class DoublyListNode:
    def __init__(self, val):
        self.val = val
        self.prev = None
        self.next = None

    def __str__(self):
        return str(self.val)


class MyDoublyLinkedList:
    def __init__(self):
        """
        Initialize your data structure here.
        """
        # NOTE: the pseudo head and tail are just sentinel nodes of the list
        self.head = DoublyListNode(0)
        self.tail = DoublyListNode(0)
        self.head.next = self.tail
        self.tail.prev = self.head
        self.size = 0

    def get(self, index: int) -> int:
        """
        Get the value of the index-th node in the linked list. If the index is invalid, return -1.
        """
        if index < 0 or index >= self.size:
            return -1

        if index + 1 < self.size - index:
            cur = self.head
            for _ in range(index + 1):
                cur = cur.next
        else:
            cur = self.tail
            for _ in range(self.size - index):
                cur = cur.prev

        return cur.val

    def addAtHead(self, val: int) -> None:
        """
        Add a node of value val before the first element of the linked list. After the insertion,
        the new node will be the first node of the linked list.
        """
        self.size += 1
        new_node = DoublyListNode(val)

        new_node.next = self.head.next
        new_node.prev = self.head
        self.head.next.prev = new_node
        self.head.next = new_node

    def addAtTail(self, val: int) -> None:
        """
        Append a node of value val to the last element of the linked list.
        """
        self.size += 1
        new_node = DoublyListNode(val)

        new_node.next = self.tail
        new_node.prev = self.tail.prev
        self.tail.prev.next = new_node
        self.tail.prev = new_node

    def addAtIndex(self, index: int, val: int) -> None:
        """
        Add a node of value val before the index-th node in the linked list. If index equals to the
        length of linked list, the node will be appended to the end of linked list. If index is
        greater than the length, the node will not be inserted.
        """
        if index > self.size:
            return
        if index < 0:
            index = 0

        if index < self.size - index:
            pred = self.head
            for _ in range(index):
                pred = pred.next
            succ = pred.next
        else:
            succ = self.tail
            for _ in range(self.size - index):
                succ = succ.prev
            pred = succ.prev

        self.size += 1
        new_node = DoublyListNode(val)
        new_node.next = succ
        new_node.prev = pred
        pred.next = new_node
        succ.prev = new_node

    def deleteAtIndex(self, index: int) -> None:
        """
        Delete the index-th node in the linked list, if the index is valid.
        """
        if index < 0 or index >= self.size:
            return

        if index < self.size - index:
            pred = self.head
            for _ in range(index):
                pred = pred.next
            succ = pred.next.next
        else:
            succ = self.tail
            for _ in range(self.size - index - 1):
                succ = succ.prev
            pred = succ.prev.prev

        self.size -= 1
        pred.next = succ
        succ.prev = pred

    def show(self):
        vals = []
        pred = self.head
        for _ in range(self.size):
            pred = pred.next
            vals.append(str(pred.val))
        print(" -> ".join(vals))


if __name__ == "__main__":
    import sys

    sys.path.insert(0, "../")
    from util import Runner

    data_list = [
        [
            '["MyLinkedList","addAtHead","addAtTail","deleteAtIndex","addAtTail","addAtIndex","addAtIndex","deleteAtIndex","deleteAtIndex","addAtTail","addAtIndex","addAtTail"]',
            "[[],[7],[0],[1],[5],[1,1],[2,6],[2],[1],[7],[1,7],[6]]",
        ],
        [
            '["MyDoublyLinkedList","addAtHead","addAtTail","deleteAtIndex","addAtTail","addAtIndex","addAtIndex","deleteAtIndex","deleteAtIndex","addAtTail","addAtIndex","addAtTail"]',
            "[[],[7],[0],[1],[5],[1,1],[2,6],[2],[1],[7],[1,7],[6]]",
        ],
    ]

    for i, data in enumerate(data_list, start=1):
        print(" Example {} ".format(i).center(80, "#"))
        methods, params = data
        runner = Runner(methods, params)
        results = runner.exec(locals(), verbose=True, hooks=["show"])
