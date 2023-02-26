# @problem: 138. Copy List with Random Pointer
# @file: copy_list_with_random_pointer.py
# @url: https://leetcode-cn.com/problems/copy-list-with-random-pointer
# @description:
#
# A linked list of length n is given such that each node contains an
# additional random pointer, which could point to any node in the list,
# or null.
# Construct a deep copy of the list. The deep copy should consist of
# exactly n brand new nodes, where each new node has its value set to
# the value of its corresponding original node. Both the next and random
# pointer of the new nodes should point to new nodes in the copied list
# such that the pointers in the original list and copied list represent
# the same list state. None of the pointers in the new list should point
# to nodes in the original list.
# For example, if there are two nodes X and Y in the original list,
# where X.random --> Y, then for the corresponding two nodes x and y in
# the copied list, x.random --> y.
# Return the head of the copied linked list.
# The linked list is represented in the input/output as a list of n
# nodes. Each node is represented as a pair of [val, random_index]
# where:
#
# val: an integer representing Node.val
# random_index: the index of the node (range from 0 to n-1) that the
# random pointer points to, or null if it does not point to any node.
#
# Your code will only be given the head of the original linked list.
# Example 1:
#
# Input: head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
# Output: [[7,null],[13,0],[11,4],[10,2],[1,0]]
#
# Example 2:
#
# Input: head = [[1,1],[2,1]]
# Output: [[1,1],[2,1]]
#
# Example 3:
#
# Input: head = [[3,null],[3,0],[3,null]]
# Output: [[3,null],[3,0],[3,null]]
#
# Constraints:
#
# 0 <= n <= 1000
# -104 <= Node.val <= 104
# Node.random is null or is pointing to some node in the linked list.
#
# @author: Du Ang
# @date: Feb 25, 2023

from typing import Optional


# Definition for a Node.
class Node:
    def __init__(self, x: int, next: "Node" = None, random: "Node" = None):
        self.val = int(x)
        self.next = next
        self.random = random


class Solution:
    """
    两次迭代，第一次迭代复制节点值，第二次迭代复制关系。
    时间复杂度：O(n)
    空间复杂度：O(n)
    """

    def copyRandomList(self, head: "Optional[Node]") -> "Optional[Node]":
        if not head:
            return None

        self.hash_map = {}

        # copy the linked list values
        node = head
        while node:
            new_node = Node(node.val)
            self.hash_map[node] = new_node
            node = node.next

        # build the linked list relations
        node = head
        while node:
            new_node = self.hash_map[node]
            if node.next:
                new_node.next = self.hash_map[node.next]
            if node.random:
                new_node.random = self.hash_map[node.random]
            node = node.next

        return self.hash_map[head]


class Solution2:
    """
    一次迭代，按需创建并缓存节点到 hash_map。
    时间复杂度：O(n)
    空间复杂度：O(n)
    """

    def copyRandomList(self, head: "Optional[Node]") -> "Optional[Node]":
        if not head:
            return None

        self.hash_map = {}

        # copy the linked list values
        node = head
        while node:
            new_node = self.get_copy_node(node)
            if node.next:
                new_next_node = self.get_copy_node(node.next)
                new_node.next = new_next_node
            if node.random:
                new_random_node = self.get_copy_node(node.random)
                new_node.random = new_random_node
            node = node.next

        return self.hash_map[head]

    def get_copy_node(self, node: "Node") -> "Node":
        if node in self.hash_map:
            new_node = self.hash_map[node]
        else:
            new_node = Node(node.val)
            self.hash_map[node] = new_node
        return new_node


class Solution3:
    """
    回溯 + 哈希表
    时间复杂度：O(n)
    空间复杂度：O(n)
    """

    def __init__(self) -> None:
        self.hash_map = {}

    def copyRandomList(self, head: "Optional[Node]") -> "Optional[Node]":
        if head is None:
            return None
        if head in self.hash_map:
            return self.hash_map[head]

        new_head = Node(head.val)
        self.hash_map[head] = new_head

        if head.next:
            new_head.next = self.copyRandomList(head.next)
        if head.random:
            new_head.random = self.copyRandomList(head.random)
        return new_head


class Solution4:
    """
    迭代 + 节点拆分，空间 O(1) 解法
    时间复杂度：O(n)
    空间复杂度：O(1)
    """

    def copyRandomList(self, head: "Optional[Node]") -> "Optional[Node]":
        if head is None:
            return None

        # copy and make the copy node the direct successor of the original node
        node = head
        while node:
            new_node = Node(node.val)
            new_node.next = node.next
            node.next = new_node
            node = node.next.next

        # copy the raondom relations to the new sub-linked-list
        node = head
        while node:
            if node.random:
                node.next.random = node.random.next
            node = node.next.next

        # restore the input linked-list and split the copied linked-list
        new_head = head.next
        node = head
        while node:
            temp_next_node = node.next
            if node.next:
                node.next = node.next.next
            node = temp_next_node

        return new_head
