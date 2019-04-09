/** 
 * @problem: 7. Reverse Integer
 * @file: reverse-integer.cpp
 * @url: https://leetcode-cn.com/problems/reverse-integer
 * @description: 
 * 
 * Given a 32-bit signed integer, reverse digits of an integer.
 * Example 1:
 * Input: 123
 * Output: 321
 * 
 * Example 2:
 * Input: -123
 * Output: -321
 * 
 * Example 3:
 * Input: 120
 * Output: 21
 * 
 * Note:
 * Assume we are dealing with an environment which could only store
 * integers within the 32-bit signed integer range: [−2^{31},  2^{31} − 1]. For
 * the purpose of this problem, assume that your function returns 0 when
 * the reversed integer overflows.
 * 
 * @author: Du Ang
 * @date: Apr 09, 2019
 */

#include <iostream>
#include <stack>
#include <limits>

using namespace std;

// Solution 1, execute first, then check if it is overflow
class Solution1 {
public:
    int reverse(int x) {
        if (x == 0) {
            return 0;
        }
        bool pos = (x > 0);
        if (!pos) {
            x = x * (-1);
        }
        stack<int> stk;
        while (x / 10 > 0) {
            stk.push(x % 10);
            x = x / 10;
        }
        stk.push(x);

        int result = 0;
        while (stk.top() == 0) {
            stk.pop();
        }

        int times = 1;
        while (!stk.empty()) {
            int temp = stk.top();
            if (temp * times / times == temp) {
                temp = temp * times;
                if (result + temp - temp == result) {
                    result += temp;
                } else {
                    return 0;   // add overflow
                }
            } else {
                return 0;   // multiplication overflow
            }
            stk.pop();
            times *= 10;
        }

        if (result < 0) {
            return 0;   // add overflow
        } else if (!pos) {
            result = result * (-1);
        }

        return result;
    }
};

class Solution {
public:
    int reverse(int x) {
        int imax = numeric_limits<int>::max();  // 2147483647
        int imin = numeric_limits<int>::min();  // -2147483648
        int result = 0;
        while (x != 0) {
            int pop = x % 10;
            x = x / 10;
            if (result > imax / 10 || (result == imax / 10 && pop > 7)) {
                return 0;
            }
            if (result < imin / 10 || (result == imin / 10 && pop < -8)) {
                return 0;
            }
            result = result * 10 + pop;
        }
        return result;
    }
};

int main (int argc, char *argv[])
{
    Solution s;
    cout << s.reverse(0) << endl;           // 0
    cout << s.reverse(123) << endl;         // 321
    cout << s.reverse(-123) << endl;        // -321
    cout << s.reverse(120) << endl;         // 21
    cout << s.reverse(2147483647) << endl;  // 0
    cout << s.reverse(1534236469) << endl;  // 0
    return 0;
}
