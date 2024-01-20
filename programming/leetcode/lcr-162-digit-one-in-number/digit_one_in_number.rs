// @problem: LCR 162. 数字 1 的个数
// @file: digit_one_in_number.rs
// @url: https://leetcode.cn/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof
// @description:
//
// 给定一个整数 num，计算所有小于等于 num 的非负整数中数字 1 出现的个数。
// 示例 1：
//
// 输入：num = 0
// 输出：0
//
// 示例 2：
//
// 输入：num = 13
// 输出：6
// 提示：
//
// 0 <= num < 109
//
// 注意：本题与主站 233 题相同：https://leetcode-cn.com/problems/number-of-digit-one/
//
// @author: Du Ang
// @date: Jan 13, 2024

impl Solution1 {
    // 遍历累加（超出时间限制）

    pub fn count_one(num: i32) -> i32 {
        let mut n: i32 = num;
        let mut res: i32 = 0;
        while n > 0 {
            let r = n % 10;
            if r == 1 {
                res += 1;
            }
            n = n / 10;
        }
    }

    pub fn digit_one_in_number(num: i32) -> i32 {
        let mut res: i32 = 0;
        for i in 0..num + 1 {
            res += count_one(i);
        }
    }
}

impl Solution {
    // 数学规律
    pub fn digit_one_in_number(num: i32) -> i32 {
        let mut res: i32 = 0;
        let mut digit: i32 = 1;

        let mut high = num / 10;
        let mut cur = num % 10;
        let mut low = 0;
        while high != 0 || cur != 0 {
            if cur == 0 {
                // 此位出现1的次数只由高位 high 决定
                res += high * digit;
            } else if cur == 1 {
                // 此位出现1的次数由高位 high 和低位 low 决定
                res += high * digit + low + 1;
            } else {
                // 此位出现1的次数只由高位 high 决定
                res += (high + 1) * digit;
            }
            
            low += cur * digit;
            cur = high % 10;
            high /= 10;
            digit *= 10;
        }
        return res;
    }
}
