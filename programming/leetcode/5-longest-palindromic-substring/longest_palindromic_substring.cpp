/** 
 * @problem: 5. Longest Palindromic Substring
 * @file: longest-palindromic-substring.cpp
 * @url: https://leetcode-cn.com/problems/longest-palindromic-substring
 * @description: 
 * 
 * Given a string s, find the longest palindromic substring in s. You may
 * assume that the maximum length of s is 1000.
 * Example 1:
 * Input: "babad"
 * Output: "bab"
 * Note: "aba" is also a valid answer.
 * 
 * Example 2:
 * Input: "cbbd"
 * Output: "bb"
 * 
 * @author: Du Ang
 * @date: Mar 30, 2019
 */

#include <iostream>

using namespace std;

// Solution1, Brute Force
// Time Limit Exeeded
class Solution1 {
public:
    string longestPalindrome(string s) {
        int len = s.size();
        string max_str = s.substr(0, 1);
        string temp_substr = "";
        for (int i = 0; i < len; i++) {
            bool is_palindromic = true;
            temp_substr = s[i];
            for (int j = i + 1; j < len; j++) {
                temp_substr.append(1, s[j]);
                if (is_palindromic) {
                    // s[i...j-1] is palindromic
                    if (s[j] == temp_substr[0]) {
                        // temp_substr is palindromic
                        is_palindromic = true;
                        int k = 0;
                        while (k++ < temp_substr.size() - 1) {
                            if (temp_substr[k] != s[j]) {
                                is_palindromic = false;
                            }
                        }
                        if (is_palindromic &&
                            temp_substr.size() > max_str.size()) {
                            max_str = temp_substr;
                        }
                    } else {
                        is_palindromic = false;
                    }
                } else {
                    // s[i...j-1] is not palindromic
                    if (s[j] == temp_substr[0]) {
                        int k = 0, l = temp_substr.size() - 1;
                        is_palindromic = true;
                        while (k++ < l--) {
                            if (temp_substr[k] != temp_substr[l]) {
                                is_palindromic = false;
                                break;
                            }
                        }
                        if (is_palindromic &&
                            temp_substr.size() > max_str.size()) {
                            max_str = temp_substr;
                        }
                    } else {
                        is_palindromic = false;
                    }
                }
            }
        }
        return max_str;
    }
};

// Solution2, Expand Around Center
// Accepted
class Solution2 {
public:
    string longestPalindrome(string s) {
        int len = s.size();
        if (len <= 1) {
            return s;
        }
        int start = 0, max_len = 1;
        for (double axis = 0.5; axis <= len - 1.5; axis = axis + 0.5) {
            int left, right;
            if (((int)(axis * 2)) % 2 == 0) {
                left = (int)(axis - 1);
                right = (int)(axis + 1);
            } else {
                left = (int)axis;
                right = (int)(axis + 0.5);
            };
            while (left >= 0 && right < len && left < axis && right > axis) {
                if (s[left] == s[right]) {
                    left--;
                    right++;
                    if (!(left >= 0 && right < len)) {
                        int temp_len = right - 1 - (left + 1) + 1;
                        if (temp_len > max_len) {
                            start = left + 1;
                            max_len = temp_len;
                        }
                    }
                } else {
                    int temp_len = right - 1 - (left + 1) + 1;
                    if (temp_len > max_len) {
                        start = left + 1;
                        max_len = temp_len;
                    }
                    break;
                }
            }
        }
        return s.substr(start, max_len);
    }
};

// Solution3, Dynamic Programming (Dumb)
// Memory Limit Exceeded
#define MAX 1000
#define NIL -1
#define YES 1
#define NO 0

int lookup[MAX][MAX];
void initialize() {
    memset(lookup, NIL, sizeof(lookup));
}

int is_palindromic(string s, int i, int j)
{
    int result;
    if (i >= j) {
        result = YES;
    } else {
        if (lookup[i][j] != NIL) {
            return lookup[i][j];
        } else {
            if (s[i] == s[j]) {
                result = is_palindromic(s, i + 1, j - 1);
            } else {
                result = NO;
            }
            lookup[i][j] = result;
        }
    }
    return result;
}

class Solution3 {
public:
    string longestPalindrome(string s) {
        initialize();
        int str_len = s.size();
        int substr_len = 0, max_len = 0, max_i = 0, max_j = 0;
        for (int i = 0; i < str_len; i++) {
            for (int j = i; j < str_len; j++) {
                if (is_palindromic(s, i, j) == YES) {
                    substr_len = j - i + 1;
                    if (substr_len > max_len) {
                        max_len = substr_len;
                        max_i = i;
                        max_j = j;
                    }
                }
            }
        }
        return s.substr(max_i, max_len);
    }
};

// Solution4, Dynamic Programming
// Accepted
class Solution4 {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n <= 1) {
            return s;
        }
        int table[n][n];
        memset(table, NIL, sizeof(table));

        int max_len = 1;
        for (int i = 0; i < n; i++) {
            table[i][i] = YES;
        }

        int start = 0;
        for (int i = 0; i < n-1; i++) {
            if (s[i] == s[i+1]) {
                table[i][i+1] = YES;
                if (max_len < 2) {
                    start = i;
                    max_len = 2;
                }
            }
        }

        for (int k = 3; k <= n; k++) {
            for (int i = 0; i < n-k+1; i++) {
                int j = i + k - 1;
                if (table[i+1][j-1] == YES && s[i] == s[j]) {
                    table[i][j] = YES;
                    if (k > max_len) {
                        start = i;
                        max_len = k;
                    }
                }
            }
        }
        return s.substr(start, max_len);
    }
};

// TODO
// - Reverse and solve Longest Common String
// - Using Palindromic Tree
// - Manacher’s Algorithm

int main (int argc, char *argv[])
{
    Solution2 s;
    cout << s.longestPalindrome("babad") << endl;
    cout << s.longestPalindrome("cbbd") << endl;
    cout << s.longestPalindrome("abcde") << endl;
    cout << s.longestPalindrome("abcda") << endl;
    cout << s.longestPalindrome("aaaaaaaa") << endl;
    cout << s.longestPalindrome("caba") << endl;
    cout << s.longestPalindrome("aaabaaaa") << endl;
    cout << s.longestPalindrome(
                "jglknendplocymmvwtoxvebkekzfdhykknufqdkntnqvgfbahsljkobhbxkvyi"
                "ctzkqjqydczuxjkgecdyhixdttxfqmgksrkyvopwprsgoszftuhawflzjyuyru"
                "jrxluhzjvbflxgcovilthvuihzttzithnsqbdxtafxrfrblulsakrahulwthhb"
                "jcslceewxfxtavljpimaqqlcbrdgtgjryjytgxljxtravwdlnrrauxplempnbf"
                "eusgtqzjtzshwieutxdytlrrqvyemlyzolhbkzhyfyttevqnfvmpqjngcnazma"
                "agwihxrhmcibyfkccyrqwnzlzqeuenhwlzhbxqxerfifzncimwqsfatudjihtu"
                "mrtjtggzleovihifxufvwqeimbxvzlxwcsknksogsbwwdlwulnetdysvsfkong"
                "geedtshxqkgbhoscjgpiel")
         << endl;
    cout
        << s.longestPalindrome(
               "civilwartestingwhetherthatnaptionoranynartionsoconceivedandsode"
               "dicatedcanlongendureWeareqmetonagreatbattlefiemldoftzhatwarWeha"
               "vecometodedicpateaportionofthatfieldasafinalrestingplaceforthos"
               "ewhoheregavetheirlivesthatthatnationmightliveItisaltogetherfang"
               "andproperthatweshoulddothisButinalargersensewecannotdedicatewec"
               "annotconsecratewecannothallowthisgroundThebravelmenlivinganddea"
               "dwhostruggledherehaveconsecrateditfaraboveourpoorponwertoaddord"
               "etractTgheworldadswfilllittlenotlenorlongrememberwhatwesayhereb"
               "utitcanneverforgetwhattheydidhereItisforusthelivingrathertobede"
               "dicatedheretotheulnfinishedworkwhichtheywhofoughtherehavethusfa"
               "rsonoblyadvancedItisratherforustobeherededicatedtothegreattdafs"
               "kremainingbeforeusthatfromthesehonoreddeadwetakeincreaseddevoti"
               "ontothatcauseforwhichtheygavethelastpfullmeasureofdevotionthatw"
               "eherehighlyresolvethatthesedeadshallnothavediedinvainthatthisna"
               "tionunsderGodshallhaveanewbirthoffreedomandthatgovernmentofthep"
               "eoplebythepeopleforthepeopleshallnotperishfromtheearth")
        << endl;
    return 0;
}