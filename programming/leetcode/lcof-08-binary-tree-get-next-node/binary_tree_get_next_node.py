# @problem: 剑指 Offer 08. 二叉树的下一个节点
# @file: binary_tree_get_next_node.py
# @url: https://www.nowcoder.com/practice/9023a0c988684a53960365b889ceaf5e
# @description:
#
# 给定一个二叉树其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。
# 注意，树中的结点不仅包含左右子结点，同时包含指向父结点的next指针。
#
# 示例:
# 输入:{8,6,10,5,7,9,11},8
# 返回:9
#
# 要求：空间复杂度为 O(1)，时间复杂度 O(n)
#
# @author: Du Ang
# @date: Jan 07, 2023


from typing import List


class TreeNode:
    """Definition for a binary tree node."""

    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
        self.next = None  # 指向其父节点


class Solution:
    """
    给定二叉树和其中一个节点，寻找其中序遍历的下一个节点
    """

    def GetNext(self, pNode: TreeNode) -> TreeNode:
        if pNode.right:
            # 当前节点有右子树，其中序遍历下一个节点是其右子树中最靠左的节点
            return self.goAlongLeftBranch(pNode.right)
        else:
            # 当前节点没有右子树，其中序遍历下一个节点是一定是当前节点的某一祖先，
            # 且是将当前节点纳入其左子树的最低祖先
            ancestors = [pNode]  # 用于存放 pNode 的所有祖先，包含 pNode 自身
            node = pNode.next
            while node:
                # 向上寻找 pNode 的祖先，如果发现 pNode 处于某个祖先的左子树，则该祖先
                # 就是 pNode 的中序遍历后继节点
                if node.left and ancestors[-1].val == node.left.val:
                    # 已找到
                    return node
                ancestors.append(node)
                node = node.next
            return None

    def goAlongLeftBranch(self, root: TreeNode) -> TreeNode:
        """
        寻找以 root 为根节点的二叉树的最左侧叶子节点
        """
        node = root
        while True:
            if node.left:
                node = node.left
            else:
                break
        return node
