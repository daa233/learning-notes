/**
 * @problem: 8. String to Integer (atoi)
 * @file: string-to-integer-atoi.cpp
 * @url: https://leetcode-cn.com/problems/string-to-integer-atoi
 * @description:
 *
 * Implement atoi which converts a string to an integer.
 * The function first discards as many whitespace characters as necessary
 * until the first non-whitespace character is found. Then, starting from
 * this character, takes an optional initial plus or minus sign followed
 * by as many numerical digits as possible, and interprets them as a
 * numerical value.
 *
 * The string can contain additional characters after those that form the
 * integral number, which are ignored and have no effect on the behavior
 * of this function.
 *
 * If the first sequence of non-whitespace characters in str is not a
 * valid integral number, or if no such sequence exists because either
 * str is empty or it contains only whitespace characters, no conversion
 * is performed.
 *
 * If no valid conversion could be performed, a zero value is returned.
 *
 * Note:
 * Only the space character ' ' is considered as whitespace character.
 * Assume we are dealing with an environment which could only store
 * integers within the 32-bit signed integer range: [−2^{31},  2^{31} − 1]. If
 * the numerical value is out of the range of representable values,
 * INT_MAX (2^{31} − 1) or INT_MIN (−2^{31}) is returned.
 *
 * Example 1:
 * Input: "42"
 * Output: 42
 *
 * Example 2:
 * Input: "   -42"
 * Output: -42
 * Explanation: The first non-whitespace character is '-', which is the
 * minus sign. Then take as many numerical digits as possible, which
 * gets 42.
 *
 * Example 3:
 * Input: "4193 with words"
 * Output: 4193
 * Explanation: Conversion stops at digit '3' as the next character is
 * not a numerical digit.
 *
 * Example 4:
 * Input: "words and 987"
 * Output: 0
 * Explanation: The first non-whitespace character is 'w', which is not a
 * numerical digit or a +/- sign. Therefore no valid conversion could
 * be performed.
 * Example 5:
 * Input: "-91283472332"
 * Output: -2147483648
 * Explanation: The number "-91283472332" is out of the range of a 32-bit
 * signed integer. Thefore INT_MIN (−2^{31}) is returned.
 *
 * @author: Du Ang
 * @date: Apr 10, 2019
 */

#include <iostream>

using namespace std;

class Solution1 {
public:
    int myAtoi(string str) {
        int result = 0;
        string num_str, sign = "";
        int start = -1, end = -1, len = str.size();
        for (int i = 0; i < len; i++) {
            if (str[i] == ' ') {
                continue;   // discard whitespace characeters
            } else if (str[i] == '-' || str[i] == '+') {
                if (i + 1 < len && str[i+1] >= '0' && str[i+1] <= '9') {
                    // a number started with +/- sign
                    if (start == -1) {
                        start = i + 1;
                        sign = str[i];
                    }
                } else {
                    // invalid number, such as '+-2'
                    break;
                }
            } else if (str[i] >= '0' && str[i] <= '9') {
                if (start == -1) {
                    start = i;
                }
                if ((i + 1 < len && (str[i + 1] < '0' || str[i + 1] > '9')) ||
                    i + 1 == len) {
                    // the number chararacters should be continous
                    end = i;
                    break;
                }
            } else {
                // invalid number, the first character is not a digit or a sign
                break;
            }
        }
        // Get the numerical string
        if (start < 0) {
            num_str = "0";
        } else {
            num_str = str.substr(start, end - start + 1);
        }
        // Convert the numerical string to integer
        for (int i = 0; i < num_str.size(); i++) {
            int digit = num_str[i] - '0';
            if (sign == "+" || sign == "") {
                if (result > INT_MAX / 10 ||
                    (result == INT_MAX / 10 && digit > 7)) {
                    return INT_MAX;
                } else {
                    result = result * 10 + digit;
                }
            } else if (sign == "-") {
                if (result < INT_MIN / 10 ||
                    (result == INT_MIN / 10 && digit > 8)) {
                    return INT_MIN;
                } else {
                    result = result * 10 - digit;
                }
            } else {
                exit(-1);
            }
        }
        return result;
    }
};

class Solution {
   public:
    int myAtoi(string str) {
        int result = 0;
        string num_str, sign = "";
        int len = str.size();
        for (int i = 0; i < len; i++) {
            if (str[i] == ' ') {
                continue;  // discard whitespace characeters
            } else if (str[i] == '-' || str[i] == '+') {
                if (i + 1 < len && str[i + 1] >= '0' && str[i + 1] <= '9') {
                    // a number started with +/- sign
                    sign = str[i];
                } else {
                    // invalid number, such as '+-2'
                    return 0;
                }
            } else if (str[i] >= '0' && str[i] <= '9') {
                int digit = str[i] - '0';
                if (sign == "-") {
                    if (result < INT_MIN / 10 ||
                        (result == INT_MIN / 10 && digit > 8)) {
                        return INT_MIN;
                    } else {
                        result = result * 10 - digit;
                    }
                } else {
                    if (result > INT_MAX / 10 ||
                        (result == INT_MAX / 10 && digit > 7)) {
                        return INT_MAX;
                    } else {
                        result = result * 10 + digit;
                    }
                }
                if ((i + 1 < len && (str[i + 1] < '0' || str[i + 1] > '9')) ||
                    i + 1 == len) {
                    // the number chararacters should be continous
                    break;
                }
            } else {
                // invalid number, the first character is not a digit or a sign
                return 0;
            }
        }
        return result;
    }
};

int main (int argc, char *argv[])
{
    Solution s;
    cout << s.myAtoi("42") << endl;                 // 42
    cout << s.myAtoi(" -42") << endl;               // -42
    cout << s.myAtoi("4193 with words") << endl;    // 4193
    cout << s.myAtoi("words and 987") << endl;      // 0
    cout << s.myAtoi("-91283472332") << endl;       // -2147483648
    cout << s.myAtoi("+-2") << endl;                // 0
    cout << s.myAtoi(" b11228552307") << endl;      // 0
    cout << s.myAtoi("   +0 123") << endl;          // 0
    return 0;
}
