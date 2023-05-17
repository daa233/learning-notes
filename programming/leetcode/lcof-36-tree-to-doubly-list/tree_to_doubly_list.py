# @problem: 剑指 Offer 36. 二叉搜索树与双向链表
# @file: tree_to_doubly_list.py
# @url: https://leetcode-cn.com/problems/er-cha-sou-suo-shu-yu-shuang-xiang-lian-biao-lcof
# @description:
#
# 输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。
# 为了让您更好地理解问题，以下面的二叉搜索树为例：
#
# 我们希望将这个二叉搜索树转化为双向循环链表。链表中的每个节点都有一个前驱和后继指针。对于双向循环链表，第一个节点的前驱是最后一个节点，最后一
# 个节点的后继是第一个节点。
# 下图展示了上面的二叉搜索树转化成的链表。“head” 表示指向链表中有最小元素的节点。
#
# 特别地，我们希望可以就地完成转换操作。当转化完成以后，树中节点的左指针需要指向前驱，树中节点的右指针需要指向后继。还需要返回链表中的第一个节
# 点的指针。
# 注意：本题与主站 426 题相同：https://leetcode-cn.com/problems/convert-binary-
# search-tree-to-sorted-doubly-linked-list/
# 注意：此题对比原题有改动。
#
# @author: Du Ang
# @date: May 17, 2023

from typing import List


# Definition for a Node.
class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution1:
    """深度优先搜素，使用辅助空间存储节点"""

    def _inorder_traversal(self, root: "Node", result: List["Node"]) -> None:
        if root is None:
            return None

        if root.left:
            self._inorder_traversal(root.left, result)
        result.append(root)
        if root.right:
            self._inorder_traversal(root.right, result)

    def treeToDoublyList(self, root: "Node") -> "Node":
        result = []
        self._inorder_traversal(root, result)
        if result:
            head = result[0]
            tail = result[-1]
            prev_node = head
            for node in result[1:]:
                prev_node.right = node
                node.left = prev_node
                prev_node = node
            head.left = tail
            tail.right = head
            return head
        else:
            return None


class Solution:
    """深度优先搜素，不使用辅助空间存储节点"""

    def _inorder_traversal(self, root: "Node") -> "Node":
        if root is None:
            return None

        if root.left:
            # 遍历左子树
            self._inorder_traversal(root.left)

        # 此时已遍历完左子树，last_node 指向左子树的最后一个节点
        root.left = self.last_node
        if self.last_node:
            self.last_node.right = root

        # 更新 last_node
        self.last_node = root

        if root.right:
            # 遍历右子树
            self._inorder_traversal(root.right)

    def treeToDoublyList(self, root: "Node") -> "Node":
        self.last_node: "Node" = None
        self._inorder_traversal(root)

        # 找到双向链表的 head 节点
        node = self.last_node
        while node and node.left:
            node = node.left
        head = node

        # 双向链表转换完成，但是还不是循环双向链表，因此需要找到首尾再连接起来
        if head:
            head.left = self.last_node
            self.last_node.right = head

        return head
