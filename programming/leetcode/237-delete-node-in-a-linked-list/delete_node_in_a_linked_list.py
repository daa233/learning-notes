# @problem: 237. Delete Node in a Linked List
# @file: delete_node_in_a_linked_list.py
# @url: https://leetcode-cn.com/problems/delete-node-in-a-linked-list
# @description:
#
# Write a function to delete a node (except the tail) in a singly linked
# list, given only access to that node.
# Given linked list -- head = [4,5,1,9], which looks like following:
#
# Example 1:
# Input: head = [4,5,1,9], node = 5
# Output: [4,1,9]
# Explanation: You are given the second node with value 5, the linked
# list should become 4 -> 1 -> 9 after calling your function.
#
# Example 2:
# Input: head = [4,5,1,9], node = 1
# Output: [4,5,9]
# Explanation: You are given the third node with value 1, the linked
# list should become 4 -> 5 -> 9 after calling your function.
#
# Note:
#
# The linked list will have at least two elements.
# All of the nodes' values will be unique.
# The given node will not be the tail and it will always be a valid node
# of the linked list.
# Do not return anything from your function.
#
# @author: Du Ang
# @date: Jun 05, 2020


# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class LinedList:
    def __init__(self, vals):
        if vals:
            self.head = ListNode(vals[0])
            node = self.head
            for v in vals[1:]:
                new_node = ListNode(v)
                node.next = new_node
                node = node.next
        else:
            self.head = None

    def get_node(self, val):
        # NOTE: every node has a unique val
        node = self.head
        while node:
            if node.val == val:
                return node
            else:
                node = node.next

    def show(self):
        print_linked_list(self.head)


def print_linked_list(node):
    msg = []
    while node:
        msg.append(str(node.val))
        node = node.next
    print(' -> '.join(msg))


class Solution:
    def deleteNode(self, node):
        """
        :type node: ListNode
        :rtype: void Do not return anything, modify node in-place instead.
        """
        node.val = node.next.val
        node.next = node.next.next


class WrongSolution:
    def deleteNode(self, node):
        """
        :type node: ListNode
        :rtype: void Do not return anything, modify node in-place instead.
        """
        node = node.next


if __name__ == "__main__":
    list_vals = [4, 5, 1, 9]
    node_val = 5

    s = Solution()
    # s = WrongSolution()

    print("############# a naive version ##############")
    # construct the linked list one by one
    head = ListNode(list_vals[0])
    node = head
    delete_node = ListNode(list_vals[1])
    node.next = delete_node
    node = node.next
    node.next = ListNode(list_vals[2])
    node = node.next
    node.next = ListNode(list_vals[3])
    node = node.next
    # print the linked list before delete
    print_linked_list(head)
    s.deleteNode(delete_node)
    # print the linked list after delete
    print_linked_list(head)

    print("\n############# a complicated version ##############")
    # construct the linked list
    linked_list = LinedList(list_vals)
    # print the linked list before delete
    linked_list.show()
    # get the node to delete
    delete_node = linked_list.get_node(node_val)
    s.deleteNode(delete_node)
    # print the linked list after delete
    linked_list.show()
