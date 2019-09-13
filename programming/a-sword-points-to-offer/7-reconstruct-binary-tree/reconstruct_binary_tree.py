# -*- coding:utf-8 -*-
# 题目描述
# 输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历
# 和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}
# 和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

# 先通过前序遍历得到 root 的值，然后在中序遍历中确定 root 的位置；
# 根据中序遍历中 root 的位置，确定左子树和右子树的中序遍历；
# 根据左子树和右子树中序遍历的长度，可以从前序遍历中得到左子树和右子树的前序遍历；
# 递归构建子树
class Solution:
    # 返回构造的TreeNode根节点
    def reConstructBinaryTree(self, pre, tin):
        # write code here
        if len(pre) == 0:
            return None
        elif len(pre) == 1:
            return TreeNode(pre[0])
        root_val = pre[0]
        inorder_root_index = tin.index(root_val)
        left_tin = tin[:inorder_root_index]
        right_tin = tin[inorder_root_index+1:]
        left_pre = pre[1:1+len(left_tin)]
        right_pre = pre[(1+len(left_tin)):]
        root = TreeNode(root_val)
        root.left = self.reConstructBinaryTree(left_pre, left_tin)
        root.right = self.reConstructBinaryTree(right_pre, right_tin)

        return root
