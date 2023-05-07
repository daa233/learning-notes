/**
 * @problem: 3. Longest Substring Without Repeating Characters
 * @file: longest-substring-without-repeating-characters.cpp
 * @url:
 * https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
 * @description:
 *
 * Given a string, find the length of the longest substring without
 * repeating characters.
 *
 * Example 1:
 * Input: "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3.
 *
 * Example 2:
 * Input: "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 *
 * Example 3:
 * Input: "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3.
 *              Note that the answer must be a substring, "pwke" is a
 * subsequence and not a substring.
 *
 * @author: Du Ang
 * @date: Mar 29, 2019
 */

#include <cstring>
#include <iostream>
#include <string>

using namespace std;

class Solution {
   public:
    int lengthOfLongestSubstring(string s) {
        int hash[128] = {};
        // initialize all hash elements to -1
        memset(hash, -1, sizeof(hash));
        int max_len = 0;
        // we use i and j to indicate the window range
        for (int i = 0, j = 0, len = 0; i < s.size() && j < s.size(); j++) {
            int found_index = hash[s[j]];
            if (found_index != -1 && found_index >= i) {
                // s[j] is already in substr, move forward the window
                i = found_index + 1;
            }
            hash[s[j]] = j;
            len = j - i + 1;
            if (len > max_len) {
                max_len = len;
            }
        }
        return max_len;
    }
};

void test(Solution sol, string s) {
    cout << "Input: " << s << endl;
    int len = sol.lengthOfLongestSubstring(s);
    cout << "Output: " << len << endl;
}

int main(int argc, char *argv[]) {
    Solution s;
    test(s, "");
    test(s, "abcabcbb");
    test(s, "bbbbb");
    test(s, "pwwkew");
    test(s, "aab");
    test(s, "dvdi");
    test(s, "ggububgvfk");
    return 0;
}
