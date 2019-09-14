# -*- coding:utf-8 -*-
# 题目描述
# 给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。
# 注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。

class TreeLinkNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
        self.next = None    # parent

# 1. 如果 pNode 有右子树，那么下一个结点是它右子树的最左子结点
# 2. 如果 pNode 没有右子树: 
# （1）pNode 是根结点，返回 None
# （2）pNode 是左孩子，那么下一个结点是它的父结点
# （3）pNode 是右孩子，需要从 pNode 开始往上找它的祖先里第一个不是右孩子的那
#     个 aNode。如果 aNode 是个左孩子，返回 aNode 的父结点；如果 aNode 是
#     根节点，返回 None
class Solution:
    def GetNext(self, pNode):
        # write code here
        if pNode.right:
            # pNode 有右子树
            node = pNode.right
            while node.left:
                node = node.left
            return node
        else:
            # pNode 没有右子树
            if not pNode.next:
                # pNode 是根结点
                return None
            elif pNode == pNode.next.left:
                # pNode 是左孩子，返回它的父结点
                return pNode.next
            else:
                # pNode 是右孩子，寻找它第一个不是右孩子的祖先
                node = pNode
                while node.next:
                    if node == node.next.left:
                        return node.next
                    node = node.next
                return None
