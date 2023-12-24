# @problem: LCR 137. 模糊搜索验证
# @file: article_match.py
# @url: https://leetcode-cn.com/problems/zheng-ze-biao-da-shi-pi-pei-lcof
# @description:
#
# 请设计一个程序来支持用户在文本编辑器中的模糊搜索功能。用户输入内容中可能使用到如下两种通配符：
#
# '.' 匹配任意单个字符。
# '*' 匹配零个或多个前面的那一个元素。
#
# 请返回用户输入内容 input 所有字符是否可以匹配原文字符串 article。
# 示例 1:
#
# 输入: article = "aa", input = "a"
# 输出: false
# 解释: "a" 无法匹配 "aa" 整个字符串。
#
# 示例 2:
#
# 输入: article = "aa", input = "a*"
# 输出: true
# 解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a'
# 重复了一次。
#
# 示例 3:
#
# 输入: article = "ab", input = ".*"
# 输出: true
# 解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
#
# 提示：
#
# 1 <= article.length <= 20
# 1 <= input.length <= 20
# article 只包含从 a-z 的小写字母。
# input 只包含从 a-z 的小写字母，以及字符 . 和 * 。
# 保证每次出现字符 * 时，前面都匹配到有效的字符
#
# 注意：本题与主站 10 题相同：https://leetcode-cn.com/problems/regular-expression-
# matching/
#
# @author: Du Ang
# @date: Dec 24, 2023


class Solution:
    """
    动态规划
    参考题解 https://leetcode.cn/problems/zheng-ze-biao-da-shi-pi-pei-lcof/solutions/92888/zhu-xing-xiang-xi-jiang-jie-you-qian-ru-shen-by-je
    """

    def articleMatch(self, s: str, p: str) -> bool:
        n = len(s) + 1
        m = len(p) + 1

        # dp[i][j] 表示 s 的前 $i$ 个字符（即 $s[:i]$）与 p 中的前 $j$ 个
        # 字符（即 $p[:j]$）是否能够匹配。
        # 初始化 dp 大小为 n x m 的二维数组
        dp = [[False] * m for _ in range(n)]

        for i in range(n):
            for j in range(m):
                # 分成空正则和非空正则两种
                if j == 0:
                    # p 为空正则
                    if i == 0:
                        # 空串和空正则匹配
                        dp[i][j] = True
                    else:
                        # 非空串和空正则必不匹配
                        dp[i][j] = False
                else:
                    # p 为非空正则
                    if p[j - 1] == ".":
                        if i > 0:
                            dp[i][j] = dp[i - 1][j - 1]
                    elif p[j - 1] != "*":
                        # p[j-1] 为正常字符
                        if i > 0:
                            if s[i - 1] == p[j - 1]:
                                dp[i][j] = dp[i - 1][j - 1]
                            else:
                                dp[i][j] = False
                    else:
                        # p[j-1] 为 *，需要分两种情况，两种情况满足其一即匹配
                        # 不看正则最后的 c*
                        if j >= 2:
                            # $s[i-1]$ 对应 0 个 $c$，即 $p$ 最后的 $c*$ 直接作废
                            # 了，最终能否匹配取决于 $s[:i]$ 和 $p[:j-2]$ 能否匹
                            # 配，即 $dp[i][j-2]$ 的结果
                            dp[i][j] = dp[i][j - 2]
                        if dp[i][j]:
                            # 条件已满足，无需判断第二种情况
                            continue
                        # 看正则最后的 c*
                        if (
                            i >= 1
                            and j >= 2
                            and (s[i - 1] == p[j - 2] or p[j - 2] == ".")
                        ):
                            #  $s[i-1]$ 是多个 $c$ 中的最后一个，即 $s[i-1]$ 已经
                            # 被匹配上了，则 $s$ 左移一位，$p$ 继续匹配，最终能否
                            # 匹配取决于 $s[:i-1]$ 和 $p[:j]$ 能否匹配，即
                            # $dp[i-1][j]$  的结果
                            dp[i][j] = dp[i - 1][j]

        return dp[-1][-1]


if __name__ == "__main__":
    sln = Solution()
    # assert sln.articleMatch("aa", "a") == False
    assert sln.articleMatch("aa", "a.") == True
    assert sln.articleMatch("aa", "a*") == True
    assert sln.articleMatch("aab", "a*b") == True
    assert sln.articleMatch("aaa", "a*a") == True
    assert sln.articleMatch("aaaaaaaae", "a*e") == True
    assert sln.articleMatch("abce", "a*e") == False
    assert sln.articleMatch("aab", "c*a*b") == True
    assert sln.articleMatch("aaa", "ab*a*c*a") == True
