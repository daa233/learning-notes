// @problem: LCR 180. 文件组合
// @file: file_combination.rs
// @url: https://leetcode.cn/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof
// @description:
//
// 待传输文件被切分成多个部分，按照原排列顺序，每部分文件编号均为一个 正整数（至少含有两个文件）。传输要求为：连续文件编号总和为接收方指定数字
// target 的所有文件。请返回所有符合该要求的文件传输组合列表。
// 注意，返回时需遵循以下规则：
//
// 每种组合按照文件编号 升序 排列；
// 不同组合按照第一个文件编号 升序 排列。
//
// 示例 1：
//
// 输入：target = 12
// 输出：[[3, 4, 5]]
// 解释：在上述示例中，存在一个连续正整数序列的和为 12，为 [3, 4, 5]。
//
// 示例 2：
//
// 输入：target = 18
// 输出：[[3,4,5,6],[5,6,7]]
// 解释：在上述示例中，存在两个连续正整数序列的和分别为 18，分别为 [3, 4, 5, 6] 和 [5, 6, 7]。
//
// 提示：
//
// 1 <= target <= 10^5
//
// @author: Du Ang
// @date: Jan 10, 2024

impl Solution1 {
    // 等差数列求和公式
    // $s = a_1 n + d \cdot \frac{n(n-1)}{2}$，公差 $d = 1$
    // 数列左边界 i，数列总和 s，则右边界 j 为
    // $j = i + n - 1 = -\frac{1}{2} + \sqrt{(i - \frac{1}{2})^2 + 2s}$
    // 注意：f32 计算精度可能不够导致出错！
    pub fn file_combination(target: i32) -> Vec<Vec<i32>> {
        let mut res: Vec<Vec<i32>> = vec![];
        let epsilon = 10f64.powi(-(12 as i32));

        for i in 1..(target / 2 + 1) {
            let j = -0.5 + ((i as f64 - 0.5).powi(2) + 2_f64 * target as f64).powf(0.5_f64);
            if (i as f64) < j && (j.floor() - j).abs() < epsilon {
                let mut data: Vec<i32> = vec![];
                for k in i..(j as i32 + 1) {
                    data.push(k);
                }
                res.push(data);
            }
        }
        return res;
    }
}

impl Solution {
    // 滑动窗口法（双指针法）
    pub fn file_combination(target: i32) -> Vec<Vec<i32>> {
        let mut left = 1;
        let mut right = 1;
        let mut s = 1;
        let mut res: Vec<Vec<i32>> = vec![];
        while left <= target / 2 + 1 {
            if s > target {
                s -= left;
                left += 1;
            } else if s < target {
                right += 1;
                s += right;
            } else {
                let mut data: Vec<i32> = Vec::new();
                for i in left..right + 1 {
                    data.push(i);
                }
                res.push(data);
                s -= left;
                left += 1;
            }
        }
        return res;
    }
}
