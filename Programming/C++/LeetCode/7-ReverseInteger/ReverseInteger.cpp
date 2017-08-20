/**
 * LeetCode Problems 7. Reverse Integer
 *
 * @file:  ReverseInteger.cpp
 * @description: Reverse digits of an integer.
 * @sample_input:
    Case 1:
    123
    Case 2:
    -123
 * @sample_output:
    Case 1:
    321
    Case 2:
    -321
 *
 * @author: Du Ang
 * @date: Aug. 20th, 2017
 */

#include <iostream>

class Solution {
public:
    int reverse(int x) {
        int maxInt = 0x7FFFFFFF;
        int minInt = 0x80000000;

        int y = 0;

        if (x >= maxInt || x <= minInt) {
            return 0;
        }

        if (x == 0) {
            return y;
        } else {
            while (x >= 10 || x <= -10) {
                if ((y != 0) && (intMultiplyOverflow(y, 10) || intAddOverflow(y*10, x%10))) {
                    return y = 0;
                } else {
                    y = y * 10 + x % 10;
                    x = x / 10;
                }
            }
            if ((y != 0) && (intMultiplyOverflow(y, 10) || intAddOverflow(y*10, x))) {
                return y = 0;
            } else {
                y = y * 10 + x;
            }
        }
        return y;
    }

    // true for overflow, false for not overflow
    bool intMultiplyOverflow(int x, int y) {
        if (x == 0 || y == 0) {
            return false;
        }
        if (x == x * y / y) {
            return false;
        } else {
            // std::cout << x << " * " << y << " is overflow" << std::endl;
            return true;
        }
    }

    // true for overflow, false for not overflow
    bool intAddOverflow(int x, int y) {
        int sum = x + y;
        if (x > 0 && y > 0 && sum < 0) {
            // std::cout << x << " + " << y << " is overflow" << std::endl;
            return true;
        }
        if (x < 0 && y < 0 && sum > 0) {
            // std::cout << x << " + " << y << " is overflow" << std::endl;
            return true;
        }
        return false;
    }
};

int main(int argc, char const *argv[]) {
    Solution s;
    int maxInt = 0x7FFFFFFF;
    int minInt = 0x80000000;
    std::cout << "maxInt = " << maxInt << std::endl;
    std::cout << "minInt = " << minInt << std::endl;
    int n;

    std::cin >> n;
    int reverse = s.reverse(n);
    std::cout << "n's reverse = " << reverse << std::endl;

    int main(int argc, char const *argv[]) {
    Solution s;
    int maxInt = 0x7FFFFFFF;
    int minInt = 0x80000000;
    std::cout << "maxInt = " << maxInt << std::endl;
    std::cout << "minInt = " << minInt << std::endl;
    int n;
//     std::cin >> n;
//     int reverse = s.reverse(n);
//     std::cout << "n's reverse = " << reverse << std::endl;

    while (true) {
        std::cin >> n;
        std::cout << n << std::endl;
        int reverse = s.reverse(n);
        std::cout << "n's reverse = " << reverse << std::endl;
        std::cin.clear();  // to prevent the dead loop
    }

    return 0;
}
