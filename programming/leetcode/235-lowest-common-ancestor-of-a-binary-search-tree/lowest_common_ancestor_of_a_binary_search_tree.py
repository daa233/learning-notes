# @problem: 235. Lowest Common Ancestor of a Binary Search Tree
# @file: lowest_common_ancestor_of_a_binary_search_tree.py
# @url: https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-search-tree
# @description: 
# 
# Given a binary search tree (BST), find the lowest common ancestor
# (LCA) of two given nodes in the BST.
# According to the definition of LCA on Wikipedia: “The lowest common
# ancestor is defined between two nodes p and q as the lowest node in T
# that has both p and q as descendants (where we allow a node to be a
# descendant of itself).”
# Given binary search tree:  root = [6,2,8,0,4,7,9,null,null,3,5]
# 
# Example 1:
# Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
# Output: 6
# Explanation: The LCA of nodes 2 and 8 is 6.
# 
# Example 2:
# Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
# Output: 2
# Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a
# descendant of itself according to the LCA definition.
# 
# Note:
# 
# All of the nodes' values will be unique.
# p and q are different and both values will exist in the BST.
# 
# @author: Du Ang
# @date: Sep 08, 2019

# BST 的性质：
# 1. 节点 N 左子树上的所有节点的值都小于等于节点 N 的值
# 2. 节点 N 右子树上的所有节点的值都大于等于节点 N 的值
# 3. 左子树和右子树也都是 BST

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class BinarySearchTree:
    def __init__(self, l):
        n = len(l)
        self.count = n
        if not l:
            self.root = None
        self.root = TreeNode(l[0])
        queue = [self.root]
        pl = 1
        while pl < n:
            parent = queue.pop(0)
            if l[pl] != 'null':
                left_child = TreeNode(l[pl])
                queue.append(left_child)
            else:
                left_child = None
            pl += 1
            if pl < n:
                if l[pl] != 'null':
                    right_child = TreeNode(l[pl])
                    queue.append(right_child)
                else:
                    right_child = None
                pl += 1
            else:
                right_child = None
            parent.left = left_child
            parent.right = right_child
            
    def get_node(self, val):
        node = self.root
        while node:
            if val < node.val:
                node = node.left
            elif val > node.val:
                node = node.right
            else:
                return node
        return node

    def level_print(self):
        if not self.root:
            return []
        ans = []
        level = [self.root]
        import numpy as np
        level_count = int(np.log2(self.count)) + 1
        gap_size = 2
        while level:
            cur = []
            next_level = []
            next_level_all_null_flag = True
            for node in level:
                if node is 'null':
                    cur.append('null'.center(gap_size**level_count*2+2**level_count*2))
                    continue
                cur.append(str(node.val).center(gap_size**level_count*2+2**level_count*2))
                # if has left/right child, add to the next level
                if node.left:
                    next_level.append(node.left)
                    next_level_all_null_flag = False
                else:
                    next_level.append('null')
                if node.right:
                    next_level.append(node.right)
                    next_level_all_null_flag = False
                else:
                    next_level.append('null')
            ans.append(cur)
            level_count -= 1
            if next_level_all_null_flag:
                level = []
            else:
                level = next_level
        for nodes in ans:
            print(''.join(nodes))


##### Solutions #####

# Recursion
class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        if root is None:
            return None
        if p.val < root.val and q.val < root.val:
            return self.lowestCommonAncestor(root.left, p, q)
        elif p.val > root.val and q.val > root.val:
            return self.lowestCommonAncestor(root.right, p, q)
        else:
            return root

# Iteration
class Solution1:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        node = root
        while node:
            if p.val < node.val and q.val < node.val:
                node = node.left
            elif p.val > node.val and q.val > node.val:
                node = node.right
            else:
                return node
        return root


def test():
    bst = BinarySearchTree([6,2,8,0,4,7,9,'null','null',3,5])
    print("Binary Search Tree:")
    bst.level_print()
    p = bst.get_node(2)
    q = bst.get_node(8)
    print("node p:", p.val)
    print("node q:", q.val)
    print("lca node (solution 1):", Solution1().lowestCommonAncestor(bst.root, p, q).val)
    print("lca node (solution 2):", Solution().lowestCommonAncestor(bst.root, p, q).val)
    p = bst.get_node(2)
    q = bst.get_node(4)
    print("node p:", p.val)
    print("node q:", q.val)
    print("lca node (solution 1):", Solution1().lowestCommonAncestor(bst.root, p, q).val)
    print("lca node (solution 2):", Solution().lowestCommonAncestor(bst.root, p, q).val)


if __name__ == '__main__':
    test()
