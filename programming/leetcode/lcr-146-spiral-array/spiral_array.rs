// @problem: LCR 146. 螺旋遍历二维数组
// @file: spiral_array.rs
// @url: https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof
// @description:
//
// 给定一个二维数组 array，请返回「螺旋遍历」该数组的结果。
// 螺旋遍历：从左上角开始，按照 向右、向下、向左、向上 的顺序 依次 提取元素，然后再进入内部一层重复相同的步骤，直到提取完所有元素。
// 示例 1：
//
// 输入：array = [[1,2,3],[8,9,4],[7,6,5]]
// 输出：[1,2,3,4,5,6,7,8,9]
//
// 示例 2：
//
// 输入：array  = [[1,2,3,4],[12,13,14,5],[11,16,15,6],[10,9,8,7]]
// 输出：[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
//
// 限制：
//
// 0 <= array.length <= 100
// 0 <= array[i].length <= 100
//
// 注意：本题与主站 54 题相同：https://leetcode-cn.com/problems/spiral-matrix/
//
// @author: Du Ang
// @date: Dec 07, 2023

impl Solution {
    pub fn spiral_array(array: Vec<Vec<i32>>) -> Vec<i32> {
        let mut result = vec![];
        if array.len() == 0 {
            return result;
        }
        let mut min_i = 0;
        let mut max_i = array.len() - 1;
        let mut min_j = 0;
        let mut max_j = array[0].len() - 1;
        loop {
            // from left to right
            for j in min_j..max_j + 1 {
                result.push(array[min_i][j]);
            }
            min_i += 1;
            if min_i > max_i {
                break;
            }
            // from top to bootom
            for i in min_i..max_i + 1 {
                result.push(array[i][max_j]);
            }
            // in case of usize overflow
            if min_j + 1 > max_j {
                break;
            }
            max_j -= 1;
            // from right to left
            for j in (min_j..max_j + 1).rev() {
                result.push(array[max_i][j]);
            }
            if min_i + 1 > max_i {
                break;
            }
            max_i -= 1;
            // from bottom to top
            for i in (min_i..max_i + 1).rev() {
                result.push(array[i][min_j]);
            }
            min_j += 1;
            if min_j > max_j {
                break;
            }
        }
        return result;
    }
}
