// @problem: LCR 187. 破冰游戏
// @file: josephus_problem.rs
// @url: https://leetcode.cn/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof
// @description:
//
// 社团共有 num 为成员参与破冰游戏，编号为 0 ~ num-1。成员们按照编号顺序围绕圆桌而坐。社长抽取一个数字 target，从 0
// 号成员起开始计数，排在第 target 位的成员离开圆桌，且成员离开后从下一个成员开始计数。请返回游戏结束时最后一位成员的编号。
// 示例 1：
//
// 输入：num = 7, target = 4
// 输出：1
//
// 示例 2：
//
// 输入：num = 12, target = 5
// 输出：0
//
// 提示：
//
// 1 <= num <= 10^5
// 1 <= target <= 10^6
//
// @author: Du Ang
// @date: Jan 12, 2024

impl Solution1 {
    // 暴力模拟法（超出时间限制）
    pub fn ice_breaking_game(num: i32, target: i32) -> i32 {
        let mut nums: Vec<i32> = vec![];
        for i in 0..num {
            nums.push(i);
        }
        let mut index: usize = 0;
        let mut ti: i32 = (target - 1) % nums.len() as i32;
        while nums.len() > 1 {
            if index == ti as usize {
                nums.remove(index);
                ti = (index as i32 + target - 1) % nums.len() as i32;
            } else {
                index += 1;
            }
            index %= nums.len();
        }
        return nums[0];
    }
}

impl Solution {
    // 动态规划
    // dp[i] = (dp[i - 1] + m) \mod i
    pub fn ice_breaking_game(num: i32, target: i32) -> i32 {
        let mut dp: i32 = 0;
        for i in 1..num+1 {
            dp = (dp + target) % i;
        }
        return dp;
    }
}
