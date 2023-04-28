# @problem: 剑指 Offer 27. 二叉树的镜像
# @file: missor_tree.py
# @url: https://leetcode-cn.com/problems/er-cha-shu-de-jing-xiang-lcof
# @description:
#
# 请完成一个函数，输入一个二叉树，该函数输出它的镜像。
# 例如输入：
#      4
#    /   \
#   2     7
#  / \   / \
# 1   3 6   9
# 镜像输出：
#      4
#    /   \
#   7     2
#  / \   / \
# 9   6 3   1
# 示例 1：
# 输入：root = [4,2,7,1,3,6,9]
# 输出：[4,7,2,9,6,3,1]
#
# 限制：
# 0 <= 节点个数 <= 1000
# 注意：本题与主站 226 题相同：https://leetcode-cn.com/problems/invert-binary-tree/
#
# @author: Du Ang
# @date: Apr 28, 2023


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    def mirrorTree(self, root: TreeNode) -> TreeNode:
        if root is None:
            return None

        copy_node = TreeNode(val=root.val)
        left_child = self.mirrorTree(root.left)
        right_child = self.mirrorTree(root.right)
        copy_node.left = right_child
        copy_node.right = left_child

        return copy_node
