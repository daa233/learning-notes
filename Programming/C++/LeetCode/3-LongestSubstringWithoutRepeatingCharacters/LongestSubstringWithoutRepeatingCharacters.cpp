/**
 * LeetCode Problems 3. Longest Substring Without Repeating Characters
 *
 * @file: LongestSubstringWithoutRepeatingCharacters.cpp
 * @description: Given a string, find the length of the longest substring without repeating
                characters.
                Given "abcabcbb", the answer is "abc", which the length is 3.
                Given "bbbbb", the answer is "b", with the length of 1.
                Given "pwwkew", the answer is "wke", with the length of 3.
                Note that the answer must be a substring, "pwke" is a subsequence and not a
                substring.
 * @sample_input:
    Case 1:
    abcabcbb
    Case 2:
    bbbbb
    Case 3:
    pwwkew
 * @sample_output:
    Case 1:
    3
    Case 2:
    1
    Case 3:
    3
 *
 * @author: Du Ang
 * @date: Aug. 17th, 2017
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        string maxSubStr = s.substr(0, 1);
        string tempSubStr = "";
        for (int i = 0; i < s.size(); i++) {
            tempSubStr.clear();
            tempSubStr.append(1, s[i]);
            for (int j = i + 1; j < s.size(); j++) {
                if (tempSubStr.find(s[j]) != string::npos) {
                    if (tempSubStr.size() > maxSubStr.size()) {
                        maxSubStr = tempSubStr;
                    }
                    tempSubStr.clear();
                    break;
                } else {
                    tempSubStr.append(1, s[j]);
                    if (tempSubStr.size() > maxSubStr.size()) {
                        maxSubStr = tempSubStr;
                    }
                }
            }
        }
        return maxSubStr.size();
    }
};

int main(int argc, char const *argv[]) {
    string a = "abcabcbb";
    string b = "bbbbb";
    string c = "pwwkew";
    string d = "c";
    string e = "au";
    string f = "abc";

    Solution s;
    cout << s.lengthOfLongestSubstring(a) << endl;
    cout << s.lengthOfLongestSubstring(b) << endl;
    cout << s.lengthOfLongestSubstring(c) << endl;
    cout << s.lengthOfLongestSubstring(d) << endl;
    cout << s.lengthOfLongestSubstring(e) << endl;
    cout << s.lengthOfLongestSubstring(f) << endl;
    return 0;
}
