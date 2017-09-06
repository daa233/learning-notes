/**
 * LeetCode Problems 461. Hamming Distance
 *
 * @file: HammingDistance.cpp
 * @description: The Hamming distance between two integers is the number of positions at which the
                corresponding bits are different.
                Given two integers x and y, calculate the Hamming distance.
                Note: 0 <= x, y <= 2^31.
 * @sample_input:
    x = 1, y = 4
 * @sample_output:
    2
 *
 * @author: Du Ang
 * @date: Sep. 6th, 2017
 */

#include <iostream>

using namespace std;

class Solution {
public:
    int hammingDistance(int x, int y) {
        int distance = 0;
        int i = 0;
        while (i < 32) {
            if (x % 2 != y % 2) {
                distance++;
            }
            x = x / 2;
            y = y / 2;
            i++;
        }
        return distance;
    }
};

int main(int argc, char const *argv[]) {
    int x, y;
    cin >> x >> y;
    Solution s;
    cout << s.hammingDistance(x, y) << endl;
    return 0;
}
