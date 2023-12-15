// @problem: LCR 135. 报数
// @file: count_numbers.rs
// @url: https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof
// @description:
//
// 实现一个十进制数字报数程序，请按照数字从小到大的顺序返回一个整数数列，该数列从数字 1 开始，到最大的正整数 cnt 位数字结束。
// 示例 1:
//
// 输入：cnt = 2
// 输出：[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
// 26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,4
// 9,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72
// ,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,
// 96,97,98,99]
//
// @author: Du Ang
// @date: Dec 11, 2023

struct Solution1 {}
struct Solution {}

// 直接生成，不考虑大数越界
impl Solution1 {
    pub fn count_numbers(cnt: i32) -> Vec<i32> {
        let result: Vec<_> = (1..(10_i32).pow(cnt as u32)).collect();
        return result;
    }
}

// 考虑大数越界，全排列，优化去掉开头0的方法
impl Solution {
    fn vec_to_large_int(nums: &Vec<char>, start: usize) -> i32 {
        let mut sum: i32 = 0;
        for i in start..nums.len() {
            sum = sum * 10 + nums[i].to_digit(10).unwrap() as i32;
        }
        return sum;
    }

    pub fn count_numbers(cnt: i32) -> Vec<i32> {
        let mut result: Vec<i32> = vec![];
        let mut nums: Vec<char> = vec!['0'; cnt as usize];
        let start: Option<usize> = None;

        fn dfs(
            i: usize,
            start: Option<usize>,
            cnt: i32,
            nums: &mut Vec<char>,
            result: &mut Vec<i32>,
        ) {
            if i == cnt as usize {
                if let Some(start_v) = start {
                    let sum = Solution::vec_to_large_int(nums, start_v);
                    result.push(sum as i32);
                }
                return;
            }

            for j in 0..10 {
                let vi = match start {
                    Some(start_v) => Some(start_v),
                    None => {
                        if j == 0 {
                            None
                        } else {
                            Some(i)
                        }
                    }
                };
                nums[i] = char::from_digit(j, 10).unwrap();
                dfs(i + 1, vi, cnt, nums, result);
            }
        }

        dfs(0, start, cnt, &mut nums, &mut result);
        return result;
    }
}

fn main() {
    let cnt = 2;
    let result = Solution::count_numbers(2);
    println!("input: {cnt}, ouptut: {:?}", result);
}
