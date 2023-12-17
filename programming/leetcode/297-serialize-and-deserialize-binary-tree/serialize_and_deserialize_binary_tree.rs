// @problem: 297. Serialize and Deserialize Binary Tree
// @file: serialize_and_deserialize_binary_tree.rs
// @url: https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree
// @description:
//
// Serialization is the process of converting a data structure or object
// into a sequence of bits so that it can be stored in a file or memory
// buffer, or transmitted across a network connection link to be
// reconstructed later in the same or another computer environment.
// Design an algorithm to serialize and deserialize a binary tree. There
// is no restriction on how your serialization/deserialization algorithm
// should work. You just need to ensure that a binary tree can be
// serialized to a string and this string can be deserialized to the
// original tree structure.
// Clarification: The input/output format is the same as how LeetCode
// serializes a binary tree. You do not necessarily need to follow this
// format, so please be creative and come up with different approaches
// yourself.
// Example 1:
//
// Input: root = [1,2,3,null,null,4,5]
// Output: [1,2,3,null,null,4,5]
//
// Example 2:
//
// Input: root = []
// Output: []
//
// Constraints:
//
// The number of nodes in the tree is in the range [0, 104].
// -1000 <= Node.val <= 1000
//
// @author: Du Ang
// @date: Dec 16, 2023

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
    pub val: i32,
    // `Rc` 支持多重所有权，`RefCell` 可以可变地借用一个不可变的值
    pub left: Option<Rc<RefCell<TreeNode>>>,
    pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    #[inline]
    pub fn new(val: i32) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

use std::cell::RefCell;
use std::rc::Rc;
struct DfsCodec {}
use std::collections::VecDeque;

/**
 * Preorder DFS
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl DfsCodec {
    fn new() -> Self {
        DfsCodec {}
    }

    // 使用深度优先搜索（DFS）进行先序遍历（preorder）
    fn traverse_dfs(&self, root: Option<Rc<RefCell<TreeNode>>>, result: &mut Vec<String>) {
        match root {
            Some(p_root) => {
                result.push(p_root.borrow().val.to_string());
                self.traverse_dfs(p_root.borrow().left.clone(), result);
                self.traverse_dfs(p_root.borrow().right.clone(), result);
            }
            None => {
                result.push(String::from("null"));
            }
        }
    }

    // 使用深度优先搜索（DFS）构建二叉树
    fn build_dfs(&self, seq: &mut VecDeque<&str>) -> Option<Rc<RefCell<TreeNode>>> {
        if seq.is_empty() {
            return None;
        }
        let val_str = seq.pop_front().unwrap();
        let maybe_node = match val_str.parse::<i32>() {
            Ok(val) => {
                // 关键步骤：连续递归调用构建左子树、右子树
                let left_node = self.build_dfs(seq);
                let right_node = self.build_dfs(seq);
                let node = TreeNode {
                    val,
                    left: left_node,
                    right: right_node,
                };
                Some(Rc::new(RefCell::new(node)))
            }
            _ => None,
        };
        return maybe_node;
    }

    fn serialize(&self, root: Option<Rc<RefCell<TreeNode>>>) -> String {
        let mut val_str_vec: Vec<String> = vec![];
        self.traverse_dfs(root, &mut val_str_vec);
        let mut result = String::from("[");
        result.push_str(&val_str_vec.join(","));
        result.push_str("]");
        result
    }

    fn deserialize(&self, data: String) -> Option<Rc<RefCell<TreeNode>>> {
        assert!(
            data.chars().nth(0).unwrap() == '[' && data.chars().nth(data.len() - 1).unwrap() == ']'
        );
        // trim the `[` and the `]` at the head and tail, split by ','
        let mut parts: VecDeque<&str> = (&data[1..data.len() - 1]).split(",").collect();
        return self.build_dfs(&mut parts);
    }
}

struct Codec {}

/**
 * BFS
 */
impl Codec {
    fn new() -> Self {
        Codec {}
    }

    fn serialize(&self, root: Option<Rc<RefCell<TreeNode>>>) -> String {
        if root == None {
            return "[]".to_string();
        }

        let mut val_str_vec = vec![];
        let mut queue = VecDeque::new();
        queue.push_back(root);
        while !queue.is_empty() {
            let maybe_node = queue.pop_front().unwrap();
            match maybe_node {
                Some(p_node) => {
                    val_str_vec.push(p_node.borrow().val.to_string());
                    queue.push_back(p_node.borrow().left.clone());
                    queue.push_back(p_node.borrow().right.clone());
                }
                None => {
                    val_str_vec.push("null".to_string());
                }
            }
        }
        let mut result = String::from("[");
        result.push_str(&val_str_vec.join(","));
        result.push_str("]");
        result
    }

    fn deserialize(&self, data: String) -> Option<Rc<RefCell<TreeNode>>> {
        assert!(
            data.chars().nth(0).unwrap() == '[' && data.chars().nth(data.len() - 1).unwrap() == ']'
        );
        // trim the `[` and the `]` at the head and tail, split by ','
        let mut parts: VecDeque<&str> = (&data[1..data.len() - 1]).split(",").collect();
        if parts.is_empty() {
            return None;
        }

        fn parse_str_to_node(val_str: &str) -> Option<TreeNode> {
            match val_str.parse::<i32>() {
                Ok(val) => Some(TreeNode {
                    val,
                    left: None,
                    right: None,
                }),
                _ => None,
            }
        }

        let root = parse_str_to_node(parts.pop_front().unwrap()).unwrap();
        let mut queue = VecDeque::new();
        let p_root = Some(Rc::new(RefCell::new(root)));
        queue.push_back(p_root.clone());

        while !queue.is_empty() {
            let parent = queue.pop_front().unwrap().unwrap();
            // left child
            if parts.is_empty() {
                break;
            }
            match parse_str_to_node(parts.pop_front().unwrap()) {
                Some(left_child) => {
                    let p_left_child = Rc::new(RefCell::new(left_child));
                    parent.borrow_mut().left = Some(p_left_child.clone());
                    queue.push_back(Some(p_left_child.clone()));
                }
                None => {}
            }
            // right child
            if parts.is_empty() {
                break;
            }
            match parse_str_to_node(parts.pop_front().unwrap()) {
                Some(right_child) => {
                    let p_right_child = Rc::new(RefCell::new(right_child));
                    parent.borrow_mut().right = Some(p_right_child.clone());
                    queue.push_back(Some(p_right_child.clone()));
                }
                None => {}
            }
        }
        p_root
    }
}

/**
 * Your Codec object will be instantiated and called as such:
 * let obj = Codec::new();
 * let data: String = obj.serialize(strs);
 * let ans: Option<Rc<RefCell<TreeNode>>> = obj.deserialize(data);
 */

fn main() {
    // DFS Codec
    let data = String::from("[1,2,3,null,null,4,null,6,null,null,5]");
    let obj = DfsCodec::new();
    let ans: Option<Rc<RefCell<TreeNode>>> = obj.deserialize(data);
    let data: String = obj.serialize(ans);
    println!("dfs serialize tree: {:?}", data);

    // BFS Codec
    let data = String::from("[1,2,3,null,null,4,5,6]");
    let obj = Codec::new();
    let ans: Option<Rc<RefCell<TreeNode>>> = obj.deserialize(data);
    let data: String = obj.serialize(ans);
    println!("bfs serialize tree: {:?}", data);
}
