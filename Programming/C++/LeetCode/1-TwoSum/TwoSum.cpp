/**
 * LeetCode Problems 1. Two Sum
 *
 * @file: TwoSum.cpp
 * @description: Given an array of integers, return indices of the two numbers such that they add
                up to a specific target.
                You may assume that each input would have exactly one solution, and you may not use
                the same element twice.
 * @example: Given nums = [2, 7, 11, 15], target = 9,
    Because nums[0] + nums[1] = 2 + 7 = 9, return [0, 1].
 *
 * @author: Du Ang
 * @date: July 31st, 2017
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    vector<int> result;
                    result.push_back(i);
                    result.push_back(j);
                    return result;
                }
            }
        }
        exit(-1);
    }
};

int main(int argc, char const *argv[]) {
    Solution s;
    vector<int> v;
    v.push_back(2);
    v.push_back(7);
    v.push_back(11);
    v.push_back(15);
    int target = 9;
    vector<int> result;
    result = s.twoSum(v, target);
    cout << result[0] << ", " << result[1] << endl;
    return 0;
}
