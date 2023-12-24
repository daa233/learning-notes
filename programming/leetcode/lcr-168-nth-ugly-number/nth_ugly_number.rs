// @problem: LCR 168. 丑数
// @file: nth_ugly_number.rs
// @url: https://leetcode-cn.com/problems/chou-shu-lcof
// @description:
//
// 给你一个整数 n ，请你找出并返回第 n 个 丑数 。
// 说明：丑数是只包含质因数 2、3 和/或 5 的正整数；1 是丑数。
// 示例 1：
//
// 输入: n = 10
// 输出: 12
// 解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
// 提示：
//
// 1 <= n <= 1690
//
// 注意：本题与主站 264 题相同：https://leetcode-cn.com/problems/ugly-number-ii/
//
// @author: Du Ang
// @date: Dec 23, 2023

use std::cmp::min;

/**
 * 动态规划
 * dp[i] = min {dp[a] * 2, dp[b] * 3, dp[c] * 5}
 * a, b, c 会依次遍历每一个丑数的位置，它们位于分别乘2、3、5后的结果会
 * 超过当前最大丑数的位置
 */
impl Solution {
    pub fn nth_ugly_number(n: i32) -> i32 {
        let mut data: Vec<i32> = vec![1];
        let mut a: usize = 0; // 用于乘2
        let mut b: usize = 0; // 用于乘3
        let mut c: usize = 0; // 用于乘5

        while (data.len() as i32) < n {
            let m2 = data[a] * 2;
            let m3 = data[b] * 3;
            let m5 = data[c] * 5;
            let min_num = min(min(m2, m3), m5);

            data.push(min_num);

            // NOTE: 为了避免重复，这里a、b、c 要独立更新
            if m2 == min_num {
                a += 1;
            }
            if m3 == min_num {
                b += 1;
            }
            if m5 == min_num {
                c += 1;
            }
        }

        return data.pop().unwrap();
    }
}
