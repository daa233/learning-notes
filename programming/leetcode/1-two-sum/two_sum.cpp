/** 
 * @problem: 1. Two Sum
 * @file: two-sum.cpp
 * @url: https://leetcode-cn.com/problems/two-sum
 * @description: 
 * 
 * Given an array of integers, return indices of the two numbers such
 * that they add up to a specific target.
 * You may assume that each input would have exactly one solution, and
 * you may not use the same element twice.
 * Example:
 * Given nums = [2, 7, 11, 15], target = 9,
 * Because nums[0] + nums[1] = 2 + 7 = 9,
 * return [0, 1].
 * 
 * @author: Du Ang
 * @date: Mar 07, 2019
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Solution 1: For each element nums[i], find another element nums[j] which
// satisifires nums[i] + nums[j] == target.
// Time: O(n^2)
// Space: O(1)
class Solution1 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    result.push_back(i);
                    result.push_back(j);
                    return result;
                }
            }
        }
        return result;
    }
};

// Solution 2: Use a Hash Table.
// Time: O(n)
// Space: O(n)
class Solution2 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        unordered_map<int,int> map;
        for (int i = 0; i < nums.size(); i++) {
            map[nums[i]] = i;
        }
        unordered_map<int,int>::const_iterator got;
        for (int i = 0; i < nums.size(); i++) {
            got = map.find(target - nums[i]);
            if (got != map.end()) {
                if (got->second == i) {  // same element add twice
                    continue;
                } else {
                    result.push_back(i);
                    result.push_back(got->second);
                    break;
                }
            }
        }
        return result;
    }
};

// Solution 3: Use a Hash Table and optimize it.
// Time: O(n)
// Space: O(n)
class Solution {
   public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        unordered_map<int, int> map;
        unordered_map<int, int>::const_iterator got;
        for (int i = 0; i < nums.size(); i++) {
            got = map.find(target - nums[i]);
            if (got != map.end()) {
                if (got->second == i) { // same element add twice
                   continue; 
                } else {
                    result.push_back(got->second);
                    result.push_back(i);
                    break;
                }
            }
            map[nums[i]] = i;
        }
        return result;
    }
};

int main (int argc, char *argv[])
{
    Solution s;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = s.twoSum(nums, target);
    
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}
