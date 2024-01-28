// @problem: LCR 163. 找到第 k 位数字
// @file: nth_digit.rs
// @url: https://leetcode.cn/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof
// @description:
//
// 某班级学号记录系统发生错乱，原整数学号序列 [0,1,2,3,4,...] 分隔符丢失后变为 01234...
// 的字符序列。请实现一个函数返回该字符序列中的第 k 位数字。
// 示例 1：
//
// 输入：k = 5
// 输出：5
//
// 示例 2：
//
// 输入：k = 12
// 输出：1
// 解释：第 12 位数字在序列 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... 里是 1 ，它是 11
// 的一部分。
// 提示：
//
// 0 <= k < 231
//
// 注意：本题与主站 400 题相同：https://leetcode-cn.com/problems/nth-digit/
//
// @author: Du Ang
// @date: Jan 21, 2024

struct Solution {}

// 数学规律
impl Solution {
    pub fn find_kth_number(k: i32) -> i32 {
        if k == 0 {
            return 0;
        }

        let mut i: i32 = 0; // 数字的位数
        let mut c: i32 = 0; // 数字累积位数
        let mut start: i32 = 1; // i 位数的起始数字
        let mut offset: i32 = k; // 位的偏移量

        // 1. 确定所求数位是 i 位数，i 位数的起始数字为 start
        // 定位到 s_k <= k < s_{i+1}
        // 使用 `k -= c` 的写法可以防止 i32 溢出
        while k > c {
            i += 1;
            offset -= c;
            start = 10_i32.pow((i - 1) as u32);
            if 9_i32 * i > i32::MAX / start {
                break;
            } else {
                c = 9 * start * i;
            }
        }

        // 2. 确定所求数位所在的数字
        let num = start + (offset - 1) / i;

        // 3. 确定所求数位在 num 的哪一数位
        let j = (offset - 1) % i;

        // 求 num 的从高位开始数，第 j 位数字
        let res = num
            .to_string()
            .chars()
            .nth(j as usize)
            .unwrap()
            .to_digit(10)
            .unwrap() as i32;

        return res;
    }
}

fn main() {
    for inp in vec![0, 5, 10, 12, 1000000000] {
        let res = Solution::find_kth_number(inp);
        println!("k = {}, result = {}", inp, res);
    }
}
