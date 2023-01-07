# @problem: 剑指 Offer 07. 重建二叉树
# @file: build_eree.py
# @url: https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof
# @description:
#
# 输入某二叉树的前序遍历和中序遍历的结果，请构建该二叉树并返回其根节点。
# 假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
# 示例 1:
#
# Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
# Output: [3,9,20,null,null,15,7]
#
# 示例 2:
#
# Input: preorder = [-1], inorder = [-1]
# Output: [-1]
#
# 限制：
# 0 <= 节点个数 <= 5000
# 注意：本题与主站 105 题重复：https://leetcode-cn.com/problems/construct-binary-
# tree-from-preorder-and-inorder-traversal/
#
# @author: Du Ang
# @date: Feb 12, 2022

from typing import List


class TreeNode:
    """Definition for a binary tree node."""

    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:
    """
    取前序遍历首个元素作为root，在中序遍历中进行搜索 root val，搜索到后，中序遍历中该元素左边为左子树，
    右边为右子树，再根据中序遍历的子树长度确定前序遍历的子树位置，然后对左右子树分别递归地执行此算法。

      前序遍历：[根节点，左子树，右子树]
      中序遍历：[左子树，根节点，右子树]

    时间复杂度：O(n)，n 为树的节点个数。
    空间复杂度：O(n)。需要用 O(n) 的空间存储树，递归栈的空间占用 O(h)，h 为树的深度。
    """

    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        self.preorder = preorder
        self.inorder = inorder

        if not self.preorder or not self.inorder:
            return None
        else:
            return self._helper(0, len(preorder) - 1, 0, len(inorder) - 1)

    def _helper(
        self, start_preorder: int, end_preorder: int, start_inorder: int, end_inorder
    ) -> TreeNode:
        root_value = self.preorder[start_preorder]
        root = TreeNode(root_value)

        if start_inorder == end_preorder:
            if (
                start_inorder == end_inorder
                and self.preorder[start_preorder] == self.inorder[start_inorder]
            ):
                return root
            else:
                raise ValueError("Invalid input!")

        root_inorder = start_inorder
        while root_inorder <= end_inorder and self.inorder[root_inorder] != root_value:
            root_inorder += 1

        if root_inorder == end_inorder and self.inorder[root_inorder] != root_value:
            raise ValueError("Invalid input!")

        left_tree_len = root_inorder - start_inorder
        left_tree_end_preorder = start_preorder + left_tree_len
        if left_tree_len > 0:
            root.left = self._helper(
                start_preorder + 1, left_tree_end_preorder, start_inorder, root_inorder - 1
            )

        right_tree_len = end_inorder - root_inorder
        if right_tree_len > 0:
            root.right = self._helper(
                left_tree_end_preorder + 1, end_preorder, root_inorder + 1, end_inorder
            )

        return root


class Solution2:
    """
    同方法1，不过提前建立一个中序遍历 {root_val: index} 的哈希表映射，方便快速得到元素在中序遍历中的位置。

    时间复杂度：O(n)，n 为树的节点个数。
    空间复杂度：O(n)。需要用 O(n) 的空间存储树，O(n) 的空间存储哈希表映射，递归栈的空间占用 O(h)，h 为树的深度。
    """

    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        self.preorder = preorder
        self.inorder = inorder
        self.inorder_index_map = {v: i for i, v in enumerate(inorder)}

        return self._helper(0, len(preorder) - 1, 0, len(inorder) - 1)

    def _helper(
        self, start_preorder: int, end_preorder: int, start_inorder: int, end_inorder: int
    ) -> TreeNode:
        if start_preorder > end_preorder:
            return None
        elif start_preorder == end_preorder:
            return TreeNode(self.preorder[start_preorder])
        else:
            v = self.preorder[start_preorder]
            root = TreeNode(v)
            root_inorder = self.inorder_index_map[v]
            left_tree_len = root_inorder - start_inorder
            left_tree_end_preorder = start_preorder + left_tree_len
            root.left = self._helper(
                start_preorder + 1, left_tree_end_preorder, start_inorder, root_inorder - 1
            )
            root.right = self._helper(
                left_tree_end_preorder + 1, end_preorder, root_inorder + 1, end_inorder
            )
            return root


class Solution3:
    """
    在前序遍历中，两个连续的 u 和 v，只存在三种关系：
        1. v 是 u 的左儿子
        2. v 是 u 的右儿子
        3. v 是 u 的某个祖先的右儿子

    引理：一棵只有左子树的树，其前序遍历和中序遍历的顺序是相反的。

    算法步骤：
        1. 若前序遍历为空，返回 None
        2. 若前序遍历不为空，取首个元素为 root 结点。
        3. 依次遍历前序遍历剩余元素 preorder_val，stack = [root]，stack 用于存储“当前节
           点的所有还没有考虑过右儿子的祖先节点”，index 指向中序遍历首个元素
            1. 若 inorder[index] != stack.top()，
                则 stack.top() 的左孩子为 preorder_val；
                stack.append(TreeNode(inorder[index]))
            2. 若 inorder[index] == stack.top()
                若 stack 不为空且 stack.top() == inorder[index]
                node = stack.pop()
                index += 1
                node.right = TreeNode(preorder_val)
                stack.append(node.right)

    时间复杂度：O(n)，n 为树的节点个数。
    空间复杂度：O(n)。需要用 O(n) 的空间存储树，递归栈的空间占用 O(h)，h 为树的深度。
    """

    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        if not preorder:
            return None

        root = TreeNode(preorder[0])
        stack = [root]
        inorder_index = 0

        for preorder_val in preorder[1:]:
            node = stack[-1]
            if node.val != inorder[inorder_index]:
                node.left = TreeNode(preorder_val)
                stack.append(node.left)
            else:
                while stack and stack[-1].val == inorder[inorder_index]:
                    node = stack.pop(-1)
                    inorder_index += 1
                node.right = TreeNode(preorder_val)
                stack.append(node.right)

        return root
