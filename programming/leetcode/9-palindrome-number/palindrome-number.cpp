/** 
 * @problem: 9. Palindrome Number
 * @file: palindrome-number.cpp
 * @url: https://leetcode-cn.com/problems/palindrome-number
 * @description: 
 * 
 * Determine whether an integer is a palindrome. An
 * integer is a palindrome when it reads the same backward as forward.
 * Example 1:
 * Input: 121
 * Output: true
 * 
 * Example 2:
 * Input: -121
 * Output: false
 * Explanation: From left to right, it reads -121. From right to left, it
 * becomes 121-. Therefore it is not a palindrome.
 * 
 * Example 3:
 * Input: 10
 * Output: false
 * Explanation: Reads 01 from right to left. Therefore it is not a
 * palindrome.
 * 
 * Follow up:
 * Coud you solve it without converting the integer to a string?
 * 
 * @author: Du Ang
 * @date: Apr 15, 2019
 */

#include <iostream>
#include <math.h>

using namespace std;

class Solution1 {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        } else {
            string num = "";
            while (x > 0) {
                num.push_back(x % 10 + '0');
                x = x / 10;
            }
            string::const_iterator i = num.begin();
            string::const_iterator j = num.end() - 1;
            while (i <= j) {
                if (*i != *j) {
                    return false;
                }
                i++;
                j--;
            }
            return true;
        }
    }
};

class Solution2 {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        } else if (x < 10) {
            return true;
        } else if (x % 10 == 0) {
            return false;
        } else {
            int zero_num = (int) log10((double) x);
            for (int i = 0; i <= zero_num / 2; i++) {
                if (x / (int)pow(10.0, (double)i) % 10 !=
                    x / (int)pow(10.0, (double)(zero_num - i)) % 10) {
                    return false;
                }
            }
            return true;
        }
    }
};

class Solution3 {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        } else if (x < 10) {
            return true;
        } else if (x % 10 == 0) {
            return false;
        } else {
            int zero_num = (int)log10((double)x);
            int small_divisor = 1;
            int big_divisor = (int)pow(10.0, (double)(zero_num));
            while (small_divisor < big_divisor) {
                if (x / small_divisor % 10 != x / big_divisor % 10) {
                    return false;
                }
                small_divisor *= 10;
                big_divisor /= 10;
            }
            return true;
        }
    }
};

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {
            return false;
        } else if (x < 10) {
            return true;
        } else if (x % 10 == 0) {
            return false;
        } else {
            int reverse = 0;
            while (x > reverse) {
                reverse = reverse * 10 + x % 10;
                x = x / 10;
            }
            return x == reverse || x == (reverse / 10);
        }
    }
};

int main (int argc, char *argv[])
{
    Solution s;
    cout << s.isPalindrome(10) << endl;
    cout << s.isPalindrome(121) << endl;
    cout << s.isPalindrome(-121) << endl;
    cout << s.isPalindrome(1000000001) << endl;
    cout << s.isPalindrome(1000021) << endl;
    return 0;
}
