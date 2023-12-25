// @problem: LCR 137. 模糊搜索验证
// @file: article_match.rs
// @url: https://leetcode-cn.com/problems/zheng-ze-biao-da-shi-pi-pei-lcof
// @description:
//
// 请设计一个程序来支持用户在文本编辑器中的模糊搜索功能。用户输入内容中可能使用到如下两种通配符：
//
// '.' 匹配任意单个字符。
// '*' 匹配零个或多个前面的那一个元素。
//
// 请返回用户输入内容 input 所有字符是否可以匹配原文字符串 article。
// 示例 1:
//
// 输入: article = "aa", input = "a"
// 输出: false
// 解释: "a" 无法匹配 "aa" 整个字符串。
//
// 示例 2:
//
// 输入: article = "aa", input = "a*"
// 输出: true
// 解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a'
// 重复了一次。
//
// 示例 3:
//
// 输入: article = "ab", input = ".*"
// 输出: true
// 解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
//
// 提示：
//
// 1 <= article.length <= 20
// 1 <= input.length <= 20
// article 只包含从 a-z 的小写字母。
// input 只包含从 a-z 的小写字母，以及字符 . 和 * 。
// 保证每次出现字符 * 时，前面都匹配到有效的字符
//
// 注意：本题与主站 10 题相同：https://leetcode-cn.com/problems/regular-expression-
// matching/
//
// @author: Du Ang
// @date: Dec 25, 2023

struct Solution {}

// 动态规划
impl Solution {
    pub fn article_match(s: String, p: String) -> bool {
        let n = s.len() + 1;
        let m = p.len() + 1;

        // dp[i][j] 表示 s 的前 i 个字符与 p 中的前 j 个字符是否能够匹配
        // 初始化 dp 为 n x m 大小的二维数组
        let mut dp: Vec<Vec<bool>> = Vec::new();
        for _ in 0..n {
            let col: Vec<bool> = vec![false; m];
            dp.push(col);
        }

        for i in 0..n {
            for j in 0..m {
                // 分成空正则和非空正则
                if j == 0 {
                    // 空正则
                    if i == 0 {
                        // 空串空正则，匹配
                        dp[i][j] = true;
                    } else {
                        // 非空串空正则，不匹配
                        dp[i][j] = false;
                    }
                } else {
                    // 非空正则
                    if p.chars().nth(j - 1).unwrap() == '.' {
                        // p[j-1] 为 '.'，可以匹配 s[i-1] 的任意字符
                        // 此时 dp[i][j] 是否匹配取决于 dp[i-1][j-1]
                        if i >= 1 {
                            dp[i][j] = dp[i - 1][j - 1];
                        } else {
                            // 空串非空正则，且正则为 '.'
                            dp[i][j] = false;
                        }
                    } else if p.chars().nth(j - 1).unwrap() != '*' {
                        if i >= 1 {
                            // p[j-1] 为正常字符
                            if s.chars().nth(i - 1).unwrap() == p.chars().nth(j - 1).unwrap() {
                                // 若 s[i-1] == p[j-1]，则 dp[i][j] 是否匹配取决于 dp[i-1][j-1] 是否匹配
                                dp[i][j] = dp[i - 1][j - 1];
                            } else {
                                // 若 s[i-1] != p[j-1]，则 dp[i][j] 为 false
                                dp[i][j] = false;
                            }
                        } else {
                            dp[i][j] = false;
                        }
                    } else {
                        // p[j-1] 为 '*'，则 p[j-2] 与 p[j-1] 一起构成 c*
                        // 分为看 c* 和不看 c* 两种情况，两种情况满足其一即可
                        // 1. 看 c*，s[i-1] 对应 0 个 c，c* 直接作废
                        if j >= 2 {
                            dp[i][j] = dp[i][j - 2];
                        }
                        if dp[i][j] {
                            // 情况1已满足，无需判断情况2
                            continue;
                        }
                        // 2. 看 c*，s[i-1] 是多个连续 c 中的最后一个，与 p[j-2] 匹配
                        // s[i-1] 已被匹配上，则 s 左移一位，p 继续匹配剩余的 s[:i-1]
                        if i >= 1
                            && j >= 2
                            && (s.chars().nth(i - 1).unwrap() == p.chars().nth(j - 2).unwrap()
                                || p.chars().nth(j - 2).unwrap() == '.')
                        {
                            dp[i][j] = dp[i - 1][j];
                        }
                    }
                }
            }
        }

        return dp[n - 1][m - 1].clone();
    }
}

fn main() {
    assert_eq!(
        Solution::article_match(String::from("aa"), String::from("a")),
        false
    );
    assert_eq!(
        Solution::article_match(String::from("aa"), String::from("a.")),
        true
    );
    assert_eq!(
        Solution::article_match(String::from("aa"), String::from("a*")),
        true
    );
    assert_eq!(
        Solution::article_match(String::from("aab"), String::from("a*b")),
        true
    );
    assert_eq!(
        Solution::article_match(String::from("aaa"), String::from("a*a")),
        true
    );
    assert_eq!(
        Solution::article_match(String::from("aaaaaaaae"), String::from("a*e")),
        true
    );
    assert_eq!(
        Solution::article_match(String::from("abce"), String::from("a*e")),
        false
    );
    assert_eq!(
        Solution::article_match(String::from("aab"), String::from("c*a*b")),
        true
    );
    assert_eq!(
        Solution::article_match(String::from("aaa"), String::from("ab*a*c*a")),
        true
    );
}
