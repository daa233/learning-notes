/**
 * LeetCode Problems 476. Number Complement
 *
 * @file: NumberComplement.cpp
 * @description: Given a positive integer, output its complement number. The complement strategy is
                to flip the bits of its binary representation.
                Note:
                The given integer is guaranteed to fit within the range of a 32-bit signed integer.
                You could assume no leading zero bit in the integer’s binary representation.
 * @sample_input:
    Case 1:
    5
    Case 2:
    1
 * @sample_output:
    Case 1:
    2
    (Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement
    is 010. So you need to output 2.)
    Case 2:
    0
    (Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is
    0. So you need to output 0.)
 *
 * @author: Du Ang
 * @date: Sep. 11th, 2017
 */

 #include <iostream>
 #include <vector>
 #include <math.h>   // double pow (double base, double exponent);

 using namespace std;

 class Solution {
 public:
     int findComplement(int num) {
         vector<int> binary;
         int result = 0;
         while (true) {
             if (num % 2 == 1) {
                 binary.push_back(0);
             } else {
                 binary.push_back(1);
             }
             num = num / 2;
             if (num == 0) {
                 break;
             }
         }
         for (int i = 0; i < binary.size(); i++) {
             result = result + (int)(binary[i] * pow(2, i));
         }
         return result;
     }
 };

 int main(int argc, char const *argv[]) {
     Solution s;
     int num;
     while (true) {
         cin >> num;
         cout << s.findComplement(num) << endl;
     }
     return 0;
 }
