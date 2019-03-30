/** 
 * @problem: 3. Longest Substring Without Repeating Characters
 * @file: longest-substring-without-repeating-characters.cpp
 * @url: https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
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

#include <iostream>
#include <string>
#include <set>

using namespace std;

class Solution1 {
public:
    int lengthOfLongestSubstring(string s) {
        int max_len = 0;
        for (int i = 0; i < s.size(); i++) {
            int j;
            int len;
            for (j = i+1; j < s.size(); j++) {
                string sub_s = s.substr(i, j-i);
                if (sub_s.find(s[j]) != string::npos) {
                    break;
                }
            }
            len = j - i ;
            if (len > max_len) {
                max_len = len;
            }
        }
        return max_len;
    }
};

class Solution2 {
public:
    int lengthOfLongestSubstring(string s) {
        string max_substr = s.substr(0, 1), temp_substr = "";
        for (int i = 0; i < s.size(); i++) {
            temp_substr.clear();
            temp_substr.append(1, s[i]);
            for (int j = i+1; j < s.size(); j++) {
                if (temp_substr.find(s[j]) != string::npos) {
                    if (temp_substr.size() > max_substr.size()) {
                        max_substr = temp_substr;
                    }
                    break;
                } else {
                    temp_substr.append(1, s[j]);
                    if (temp_substr.size() > max_substr.size()) {
                        max_substr = temp_substr;
                    }
                }
            }
        }
        return max_substr.size();
    }
};

bool contain_repeat_chars(string s)
{
    int m[256] = {0};
    for (int i = 0; i < s.size(); i++) {
        if (m[s[i]] > 0) {
            return true;
        } else {
            m[s[i]] = 1;
        }
    }
    return false;
}

class Solution3 {
public:
    int lengthOfLongestSubstring(string s) {
        string substr = s.substr(0, 1);
        for (int i = 1; i < s.size(); ) {
            size_t found_pos = substr.find(s[i]);
            if (found_pos != string::npos) {
                if (found_pos == 0) {
                    substr.erase(0, 1);
                    substr.append(1, s[i]);
                    i++;
                    continue;
                } else {
                    // move the window to the next char of the found_pos
                    int substr_len = substr.size();
                    i += found_pos + 1;
                    if (i >= s.size()) {
                        return substr.size();
                    } else {
                        substr = s.substr(i - substr_len, substr_len);
                    }
                    // if substr contains repeat chars, keep moving forward
                    while (contain_repeat_chars(substr)) {
                        substr.erase(0, 1);
                        substr.append(1, s[i]);
                        i++;
                        if (i >= s.size()) {
                            return substr.size();
                        }
                    }
                }
            } else {
                substr.append(1, s[i]);
                i++;
            }
        }
        return substr.size();
    }
};

class Solution4 {
   public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0) {
            return 0;
        }
        string substr = s.substr(0, 1);
        int max_len = 1;
        for (int i = 1; i < s.size();) {
            size_t found_pos = substr.find(s[i]);
            if (found_pos != string::npos) {
                if (found_pos == 0) {
                    substr.erase(0, 1);
                    substr.append(1, s[i]);
                    i++;
                    continue;
                } else {
                    int new_start = i - substr.size() + found_pos + 1;
                    i = new_start + 1;
                    if (i < s.size()) {
                        substr = s.substr(new_start, 1);
                    }
                }
            } else {
                substr.append(1, s[i]);
                i++;
            }
            if (substr.size() > max_len) {
                max_len = substr.size();
            }
        }
        return max_len;
    }
};

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

void test(Solution sol, string s)
{
    cout << "Input: " << s << endl;
    int len = sol.lengthOfLongestSubstring(s);
    cout << "Output: " << len << endl;
}

int main (int argc, char *argv[])
{
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
