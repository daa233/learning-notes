# @problem: 236. Lowest Common Ancestor of a Binary Tree
# @file: lowest_common_ancestor_of_a_binary_tree.py
# @url: https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree
# @description:
#
# Given a binary tree, find the lowest common ancestor (LCA) of two
# given nodes in the tree.
# According to the definition of LCA on Wikipedia: “The lowest common
# ancestor is defined between two nodes p and q as the lowest node in T
# that has both p and q as descendants (where we allow a node to be a
# descendant of itself).”
# Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]
#
# Example 1:
# Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
# Output: 3
# Explanation: The LCA of nodes 5 and 1 is 3.
#
# Example 2:
# Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
# Output: 5
# Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a
# descendant of itself according to the LCA definition.
#
# Note:
#
# All of the nodes' values will be unique.
# p and q are different and both values will exist in the binary tree.
#
# @author: Du Ang
# @date: Sep 08, 2019


# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class BinaryTree:
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
            if l[pl] != "null":
                left_child = TreeNode(l[pl])
                queue.append(left_child)
            else:
                left_child = None
            pl += 1
            if pl < n:
                if l[pl] != "null":
                    right_child = TreeNode(l[pl])
                    queue.append(right_child)
                else:
                    right_child = None
                pl += 1
            else:
                right_child = None
            parent.left = left_child
            parent.right = right_child

    def get_node(self, node, val):
        if not node:
            return None
        else:
            if node.val == val:
                return node
            left_res = self.get_node(node.left, val)
            if left_res:
                return left_res
            right_res = self.get_node(node.right, val)
            if right_res:
                return right_res
        return None

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
                if node is "null":
                    cur.append("null".center(gap_size ** level_count * 2 + 2 ** level_count * 2))
                    continue
                cur.append(str(node.val).center(gap_size ** level_count * 2 + 2 ** level_count * 2))
                # if has left/right child, add to the next level
                if node.left:
                    next_level.append(node.left)
                    next_level_all_null_flag = False
                else:
                    next_level.append("null")
                if node.right:
                    next_level.append(node.right)
                    next_level_all_null_flag = False
                else:
                    next_level.append("null")
            ans.append(cur)
            level_count -= 1
            if next_level_all_null_flag:
                level = []
            else:
                level = next_level
        for nodes in ans:
            print("".join(nodes))


##### Solutions #####

# Parent pointers
class Solution:
    def lowestCommonAncestor(self, root: "TreeNode", p: "TreeNode", q: "TreeNode") -> "TreeNode":
        stack = [root]
        # create parent pointers for p and q ancestors
        parent = {root: None}
        while p not in parent or q not in parent:
            node = stack.pop()
            if node.left:
                stack.append(node.left)
                parent[node.left] = node
            if node.right:
                stack.append(node.right)
                parent[node.right] = node
        ancestors = set()
        while p:
            ancestors.add(p)
            p = parent[p]
        while q not in ancestors:
            q = parent[q]
        return q


# Just like Solution3, a little different
class Solution4:
    def lowestCommonAncestor(self, root: "TreeNode", p: "TreeNode", q: "TreeNode") -> "TreeNode":
        self.ans = None
        self.recurse(root, p, q)
        return self.ans

    def recurse(self, node, p, q):
        if not node:
            return False
        mid = node.val == p.val or node.val == q.val
        left = self.recurse(node.left, p, q)
        right = self.recurse(node.right, p, q)

        if mid + left + right >= 2:
            self.ans = node

        return mid or left or right


# Single traversal in bottom-up fashion
class Solution3:
    def lowestCommonAncestor(self, root: "TreeNode", p: "TreeNode", q: "TreeNode") -> "TreeNode":
        if not root:
            return None
        if root.val == p.val or root.val == q.val:
            return root
        # look up p and q in root's subtrees
        left_res = self.lowestCommonAncestor(root.left, p, q)
        right_res = self.lowestCommonAncestor(root.right, p, q)
        if left_res and right_res:
            # find p and q are in different subtrees
            return root
        elif left_res:
            # p and q are both in the left subtree, and left_res is the lca
            return left_res
        else:
            # p and q are both in the right subtree, and right_res is the lca
            return right_res


# Storing root to p and root to q paths.
# Traverse both paths till the values are the same.
class Solution2:
    def lowestCommonAncestor(self, root: "TreeNode", p: "TreeNode", q: "TreeNode") -> "TreeNode":
        self.path_p = []
        self.path_q = []
        self.find_path(root, p, self.path_p)
        self.find_path(root, q, self.path_q)
        lca = None
        while self.path_p and self.path_q:
            node_p = self.path_p.pop()
            node_q = self.path_q.pop()
            if node_p == node_q:
                lca = node_p
            else:
                break
        return lca

    def find_path(self, root: "TreeNode", node: "TreeNode", path: "List"):
        if not root:
            return None
        if root.val == node.val:
            path.append(root)
            return True
        if root.left:
            left_res = self.find_path(root.left, node, path)
            if left_res:
                path.append(root)
                return True
        if root.right:
            right_res = self.find_path(root.right, node, path)
            if right_res:
                path.append(root)
                return True
        return False


# TLE, brute force
class Solution1:
    def lowestCommonAncestor(self, root: "TreeNode", p: "TreeNode", q: "TreeNode") -> "TreeNode":
        if self.isChild(root.left, p) and self.isChild(root.left, q):
            return self.lowestCommonAncestor(root.left, p, q)
        elif self.isChild(root.right, p) and self.isChild(root.right, q):
            return self.lowestCommonAncestor(root.right, p, q)
        else:
            return root

    def isChild(self, root: "TreeNode", node: "TreeNode") -> bool:
        if root is None:
            return False
        elif root == node:
            return True
        else:
            return self.isChild(root.left, node) or self.isChild(root.right, node)


def test():
    tree = BinaryTree([3, 5, 1, 6, 2, 0, 8, "null", "null", 7, 4])
    print("Binary Tree:")
    tree.level_print()
    p = tree.get_node(tree.root, 5)
    q = tree.get_node(tree.root, 1)
    print("node p:", p.val)
    print("node q:", q.val)
    print("lca node (solution 1):", Solution1().lowestCommonAncestor(tree.root, p, q).val)
    print("lca node (solution 2):", Solution2().lowestCommonAncestor(tree.root, p, q).val)
    print("lca node (solution 3):", Solution3().lowestCommonAncestor(tree.root, p, q).val)
    print("lca node (solution 4):", Solution4().lowestCommonAncestor(tree.root, p, q).val)
    print("lca node (solution 5):", Solution().lowestCommonAncestor(tree.root, p, q).val)
    p = tree.get_node(tree.root, 5)
    q = tree.get_node(tree.root, 4)
    print("node p:", p.val)
    print("node q:", q.val)
    print("lca node (solution 1):", Solution1().lowestCommonAncestor(tree.root, p, q).val)
    print("lca node (solution 2):", Solution2().lowestCommonAncestor(tree.root, p, q).val)
    print("lca node (solution 3):", Solution3().lowestCommonAncestor(tree.root, p, q).val)
    print("lca node (solution 4):", Solution4().lowestCommonAncestor(tree.root, p, q).val)
    print("lca node (solution 5):", Solution().lowestCommonAncestor(tree.root, p, q).val)


if __name__ == "__main__":
    test()
