/**
 * Decimal to Binary Conversion.
 * https://www.geeksforgeeks.org/program-decimal-binary-conversion/
 * 
 * Given a decimal number as input, we need to write a program to convert the
 * given decimal number (positive) into equivalent binary number.
 * 
 * Examples:
 * In: 7
 * Out: 111
 * In: 10
 * Out: 1010
 * In: 33
 * Out: 100001
 */

#include <iostream>
using namespace std;

void print_array(const int* arr, int len)
{
    int not_zero_flag = 0;
    for (int i = 0; i < len; ++i) {
        if (not_zero_flag == 0 && arr[i] == 0) {
            continue;
        } else if (not_zero_flag != 0) {
            cout << arr[i];
        } else {
            cout << arr[i];
            not_zero_flag = 1;
        }
    }
    // all zeros
    if (not_zero_flag == 0) {
        cout << "0";
    }
    cout << endl;
}

// Solution 1:
// 1. Store the remainder when the number is divided by 2 in an array.
// 2. Divide the number by 2
// 3. Repeat the above two steps until the number is greater than zero.
// 4. Print the array in reverse order now.
class Solution1 {
public:
    void decimal2binary(int dec_num, int* bin_num, int len)
    {
        memset(bin_num, 0, len * sizeof(int)); // init the bin_num with 0
        int i = 0;
        while (dec_num > 0) {
            bin_num[len - 1 - i] = dec_num % 2;
            dec_num /= 2;
            i += 1;
        }
    }
};

// Solution 2:
// Use bitwise operators.
// 1. Shift right the bits of the dec_num
// 2. Get the rightest num of the dec_num
// 3. Repeat the above two steps until the all bits are accessed.
class Solution2 {
public:
    void decimal2binary(int dec_num, int* bin_num, int len)
    {
        memset(bin_num, 0, len * sizeof(int)); // init the bin_num with 0
        for (int i = 0; i < len; ++i) {
            bin_num[len - 1 - i] = (dec_num >> i) & 1;
        }
    }
};

int main(int argc, char const* argv[])
{
    int dec_num;
    int BINARY_BITS = sizeof(int) * CHAR_BIT;
    int bin_num[BINARY_BITS];
    while (true) {
        cout << "Input: ";
        cin >> dec_num;
        if (dec_num == -1) {
            break;
        } else {
            Solution1().decimal2binary(dec_num, bin_num, BINARY_BITS);
            cout << "Solution1 output:" << endl;
            print_array(bin_num, BINARY_BITS);
            Solution2().decimal2binary(dec_num, bin_num, BINARY_BITS);
            cout << "Solution2 output:" << endl;
            print_array(bin_num, BINARY_BITS);
        }
    }

    return 0;
}
