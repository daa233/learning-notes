// @problem: LCR 185. 统计结果概率
// @file: statistics_probability.rs
// @url: https://leetcode.cn/problems/nge-tou-zi-de-dian-shu-lcof
// @description:
//
// 你选择掷出 num 个色子，请返回所有点数总和的概率。
// 你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 num 个骰子所能掷出的点数集合中第 i 小的那个的概率。
// 示例 1：
//
// 输入：num = 3
// 输出：[0.00463,0.01389,0.02778,0.04630,0.06944,0.09722,0.11574,0.12500,0.
// 12500,0.11574,0.09722,0.06944,0.04630,0.02778,0.01389,0.00463]
//
// 示例 2：
//
// 输入：num = 5
// 输出:[0.00013,0.00064,0.00193,0.00450,0.00900,0.01620,0.02636,0.03922,0.
// 05401,0.06944,0.08372,0.09452,0.10031,0.10031,0.09452,0.08372,0.06944,
// 0.05401,0.03922,0.02636,0.01620,0.00900,0.00450,0.00193,0.00064,0.0001
// 3]
//
// 提示：
//
// 1 <= num <= 11
//
// @author: Du Ang
// @date: Jan 06, 2024

struct Solution {}

impl Solution {
    // 动态规划

    pub fn statistics_probability(num: i32) -> Vec<f64> {
        // 初始条件，1个骰子，掷的点数和为1~6，排列数均为1种
        let mut dp: Vec<i32> = vec![1; 6];
        for i in 2..(num + 1) {
            // i 个骰子点数和范围是 [i, i * 6]，点数和有 (i * 6 - i + 1)种可能
            let mut tmp: Vec<i32> = vec![0; (i * 6 - i + 1) as usize];
            for j in 0..dp.len() {
                // dp[j] 是有 i-1 个骰子时掷的点数和，现新增一个骰子，点数可能为
                // 1~6 中的某个点数，新的点数和存储到 tmp 中。
                // dp[j] 加上新增的骰子点数 1~6，会让 tmp[j] 到 tmp[j+5] 范围内的
                // 排列数增加 dp[j]
                for k in 0..6 {
                    tmp[j + k] += dp[j];
                }
            }
            // 将 tmp 赋值给 dp，新增下一个骰子
            dp = tmp;
        }

        let res: Vec<f64> = dp
            .clone()
            .into_iter()
            .map(|x| (x as f64) / (6_i32.pow(num as u32) as f64))
            .collect();

        return res;
    }
}

fn main() {
    println!("{:?}", Solution::statistics_probability(3));
}
