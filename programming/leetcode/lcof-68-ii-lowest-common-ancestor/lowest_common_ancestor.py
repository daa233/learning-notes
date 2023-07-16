# @problem: 剑指 Offer 68 - II. 二叉树的最近公共祖先
# @file: lowest_common_ancestor.py
# @url: https://leetcode-cn.com/problems/er-cha-shu-de-zui-jin-gong-gong-zu-xian-lcof
# @description:
#
# 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
# 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x
# 的深度尽可能大（一个节点也可以是它自己的祖先）。”
# 例如，给定如下二叉树:  root = [3,5,1,6,2,0,8,null,null,7,4]
#
# 示例 1:
# 输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
# 输出: 3
# 解释: 节点 5 和节点 1 的最近公共祖先是节点 3。
#
# 示例 2:
# 输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
# 输出: 5
# 解释: 节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。
#
# 说明:
#
# 所有节点的值都是唯一的。
# p、q 为不同节点且均存在于给定的二叉树中。
#
# 注意：本题与主站 236 题相同：https://leetcode-cn.com/problems/lowest-common-
# ancestor-of-a-binary-tree/
#
# @author: Du Ang
# @date: Jul 08, 2023

from typing import List


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution1:
    """
    遍历二叉树，存储每个节点对应的路径（链表），问题可以转换为求两个链表的最后一个公共节点
    """

    def _get_node_path(self, root: TreeNode, p: TreeNode, result: List[TreeNode]) -> bool:
        if not root:
            return False

        if root.val == p.val:
            result.append(root)
            return True
        else:
            result.append(root)
            left_res = self._get_node_path(root.left, p, result)
            if left_res:
                return True
            right_res = self._get_node_path(root.right, p, result)
            if right_res:
                return True
            result.pop(-1)
            return False

    def lowestCommonAncestor(self, root: TreeNode, p: TreeNode, q: TreeNode) -> TreeNode:
        if not root:
            return

        p_path = []
        q_path = []
        self._get_node_path(root, p, p_path)
        self._get_node_path(root, q, q_path)

        last_common_node = None
        for p_node, q_node in zip(p_path, q_path):
            if p_node != q_node:
                break
            last_common_node = p_node

        return last_common_node


class Solution2:
    """后序遍历，递归条件判断"""

    def _dfs(self, root: TreeNode, p: TreeNode, q: TreeNode) -> bool:
        """
        表示 root 节点的子树中是否包含 p 或 q 节点，若包含返回 true，否则返回 false
        这样设计的好处是，当找到最近公共祖先后，再向上回溯时，其他祖先仅能满足 lson 或者 rson，
        不可能再满足最近公共祖先的判断条件。
        """

        if not root:
            return False

        lson = self._dfs(root.left, p, q)
        rson = self._dfs(root.right, p, q)

        # 满足以下两种情况之一，当前树即为 p, q 的最近公共祖先：
        #   1. 左子树包含 p 或 q 且右子树包含 p 或 q
        #   2. 当前节点为 p 或 q，且其左子树或右子树中的一个包含 p 或 q
        res = (lson and rson) or ((root.val == p.val or root.val == q.val) and (lson or rson))
        if res:
            self.result = root

        # 注意返回值是 _dfs 方法的目标：包含 p 或 q 即返回 true，否则返回 false
        return lson or rson or root.val == p.val or root.val == q.val

    def lowestCommonAncestor(self, root: TreeNode, p: TreeNode, q: TreeNode) -> TreeNode:
        self.result = None
        self._dfs(root, p, q)
        return self.result


class Solution3:
    """后序遍历"""

    def lowestCommonAncestor(self, root: TreeNode, p: TreeNode, q: TreeNode) -> TreeNode:
        """
        考虑以 root 为根节点的子树：
          - 当其中包含 p 和 q 两个节点时，返回 p 和 q 的最近公共祖先
          - 当其中包含 p 或 q 一个节点时，返回对应的 p 或 q 节点
          - 当中不包含 p 或 q 时，返回 None
        """
        if not root:
            return None

        left_res = self.lowestCommonAncestor(root.left, p, q)
        right_res = self.lowestCommonAncestor(root.right, p, q)
        if left_res and right_res:
            # p 和 q 在当前节点的不同子树里
            return root
        if root == p or root == q:
            # 当前节点为 p 或 q
            return root
        return left_res or right_res


class Solution:
    """哈希表存储父节点"""

    def _dfs(self, root: TreeNode, p: TreeNode) -> TreeNode:
        if not root:
            return None

        left_res = self._dfs(root.left, p)
        right_res = self._dfs(root.right, p)
        if left_res or right_res or root == p:
            if not self.res and root.val in self.hash_table:
                self.res = root
            self.hash_table.add(root.val)
            return root
        return left_res or right_res

    def lowestCommonAncestor(self, root: TreeNode, p: TreeNode, q: TreeNode) -> TreeNode:
        self.hash_table = set()
        self.res = None
        self._dfs(root, p)
        self._dfs(root, q)
        return self.res
