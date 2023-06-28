# @problem: 剑指 Offer 55 - I. 二叉树的深度
# @file: max_depth.py
# @url: https://leetcode-cn.com/problems/er-cha-shu-de-shen-du-lcof
# @description:
#
# 输入一棵二叉树的根节点，求该树的深度。从根节点到叶节点依次经过的节点（含根、叶节点）形成树的一条路径，最长路径的长度为树的深度。
# 例如：
# 给定二叉树 [3,9,20,null,null,15,7]，
#     3
#    / \
#   9  20
#     /  \
#    15   7
# 返回它的最大深度 3 。
# 提示：
#
# 节点总数 <= 10000
#
# 注意：本题与主站 104 题相同：https://leetcode-cn.com/problems/maximum-depth-of-
# binary-tree/
#
# @author: Du Ang
# @date: Jun 28, 2023


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution1:
    """深度优先搜索"""

    def _dfs(self, root: TreeNode, depth: int) -> None:
        if not root:
            return

        self._dfs(root.left, depth + 1)
        self._dfs(root.right, depth + 1)

        if depth > self._max_depth:
            self._max_depth = depth

    def maxDepth(self, root: TreeNode) -> int:
        self._max_depth = 0
        self._dfs(root, 1)
        return self._max_depth


class Solution2:
    """深度优先搜索 + 回溯"""

    def _dfs(self, root: TreeNode) -> int:
        if not root:
            return 0

        left_depth = self._dfs(root.left)
        right_depth = self._dfs(root.right)
        depth = max(left_depth, right_depth) + 1

        return depth

    def maxDepth(self, root: TreeNode) -> int:
        return self._dfs(root)


class Solution:
    """广度优先搜索"""

    def maxDepth(self, root: TreeNode) -> int:
        if not root:
            return 0

        max_depth = 0
        q = [(root, 1)]
        while q:
            node, depth = q.pop()
            if node:
                if depth > max_depth:
                    max_depth = depth
                q.append((node.left, depth + 1))
                q.append((node.right, depth + 1))

        return max_depth
