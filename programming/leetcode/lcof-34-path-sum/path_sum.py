# @problem: 剑指 Offer 34. 二叉树中和为某一值的路径
# @file: path_sum.py
# @url: https://leetcode-cn.com/problems/er-cha-shu-zhong-he-wei-mou-yi-zhi-de-lu-jing-lcof
# @description:
#
# 给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。
# 叶子节点 是指没有子节点的节点。
# 示例 1：
#
# 输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
# 输出：[[5,4,11,2],[5,8,4,5]]
#
# 示例 2：
#
# 输入：root = [1,2,3], targetSum = 5
# 输出：[]
#
# 示例 3：
#
# 输入：root = [1,2], targetSum = 0
# 输出：[]
#
# 提示：
#
# 树中节点总数在范围 [0, 5000] 内
# -1000 <= Node.val <= 1000
# -1000 <= targetSum <= 1000
#
# 注意：本题与主站 113 题相同：https://leetcode-cn.com/problems/path-sum-ii/
#
# @author: Du Ang
# @date: May 17, 2023
from typing import List

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution1:
    """深度优先搜索"""

    def _dfs(self, root: TreeNode, path: List[int], target: int, result: List[List[int]]) -> None:
        if root is None:
            return None

        path.append(root.val)
        if root.left:
            self._dfs(root.left, path, target - root.val, result)
        if root.right:
            self._dfs(root.right, path, target - root.val, result)
        if not root.left and not root.right and root.val == target:
            # 当前节点已经是叶子节点，且整条路径的和与目标值相等
            result.append(path[:])
        path.pop(-1)

    def pathSum(self, root: TreeNode, target: int) -> List[List[int]]:
        result = []
        self._dfs(root, [], target, result)
        return result


class Solution:
    """深度优先搜索 + 回溯"""

    def _dfs(self, root: TreeNode, target: int) -> List[List[int]]:
        if root is None:
            return []

        all_paths = []
        for node in [root.left, root.right]:
            if node:
                paths = self._dfs(node, target - root.val)
                if paths:
                    all_paths.extend(paths)

        if not root.left and not root.right:
            # 当前节点已经是叶子节点
            if root.val == target:
                # 整条路径的和与目标值相等，将当前的 path 返回，
                # 通过回溯构建从叶子节点到 root 节点的路径
                all_paths.append([])

        # 将当前节点放入每个符合目标的回溯路径 path 中
        for path in all_paths:
            path.insert(0, root.val)
        
        return all_paths

    def pathSum(self, root: TreeNode, target: int) -> List[List[int]]:
        return self._dfs(root, target)
