# @problem: 297. Serialize and Deserialize Binary Tree
# @file: serialize_and_deserialize_binary_tree.py
# @url: https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree
# @description:
#
# Serialization is the process of converting a data structure or object
# into a sequence of bits so that it can be stored in a file or memory
# buffer, or transmitted across a network connection link to be
# reconstructed later in the same or another computer environment.
# Design an algorithm to serialize and deserialize a binary tree. There
# is no restriction on how your serialization/deserialization algorithm
# should work. You just need to ensure that a binary tree can be
# serialized to a string and this string can be deserialized to the
# original tree structure.
# Clarification: The input/output format is the same as how LeetCode
# serializes a binary tree. You do not necessarily need to follow this
# format, so please be creative and come up with different approaches
# yourself.
# Example 1:
#
# Input: root = [1,2,3,null,null,4,5]
# Output: [1,2,3,null,null,4,5]
#
# Example 2:
#
# Input: root = []
# Output: []
#
# Constraints:
#
# The number of nodes in the tree is in the range [0, 104].
# -1000 <= Node.val <= 1000
#
# @author: Du Ang
# @date: Nov 14, 2022
from typing import List


# Definition for a binary tree node.
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Codec:
    """The binary tree codec by DFS."""

    def serialize(self, root: TreeNode) -> str:
        """Encodes a tree to a single string.

        :type root: TreeNode
        :rtype: str
        """

        def dfs(root: TreeNode, result_list: List) -> None:
            if root is None:
                result_list.append("null")
            else:
                result_list.append(str(root.val))
                dfs(root.left, result_list)
                dfs(root.right, result_list)

        result_list = []
        dfs(root, result_list)

        return "[" + ",".join(result_list) + "]"

    def deserialize(self, data: str) -> TreeNode:
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: TreeNode
        """

        def build_tree(val_list: List) -> TreeNode:
            if not val_list:
                return

            val = val_list.pop(0)
            if val == "null":
                return None
            else:
                node = TreeNode(int(val))
                node.left = build_tree(val_list)
                node.right = build_tree(val_list)
                return node

        assert "[" == data[0] and "]" == data[-1], f"data {data} is not invalid"
        # strip the "[" and "]" and split by ","
        val_list = data[1:-1].split(",")
        return build_tree(val_list)


class CodecByBFS:
    """The binary tree codec by BFS."""

    def serialize(self, root: TreeNode) -> str:
        """Encodes a tree to a single string.

        :type root: TreeNode
        :rtype: str
        """
        val_list = []
        q = [root]
        while q:
            node = q.pop(0)
            if node:
                val_list.append(node.val)
                q.append(node.left)
                q.append(node.right)
            else:
                val_list.append("null")
        result = "[{}]".format(",".join([str(i) for i in val_list]))
        return result

    def deserialize(self, data: str) -> TreeNode:
        """Decodes your encoded data to tree.

        :type data: str
        :rtype: TreeNode
        """
        if not data:
            return None

        data = data[1:-1]  # stripe the '[' and ']'
        val_list = data.split(",")

        if not val_list or (len(val_list) == 1 and val_list[0] == "null"):
            return None

        node_list = []
        for val in val_list:
            if val == "null":
                node_list.append(None)
            else:
                node_list.append(TreeNode(val))

        root = node_list.pop(0)
        q = [root]
        while q:
            node = q.pop(0)
            node.left = node_list.pop(0)
            node.right = node_list.pop(0)
            if node.left:
                q.append(node.left)
            if node.right:
                q.append(node.right)

        return root


# Your Codec object will be instantiated and called as such:
# ser = Codec()
# deser = Codec()
# ans = deser.deserialize(ser.serialize(root))
