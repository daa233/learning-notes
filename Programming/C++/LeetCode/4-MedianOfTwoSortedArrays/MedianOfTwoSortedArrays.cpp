/**
 * LeetCode Problems 4. Median of Two Sorted Arrays
 *
 * @file: MedianOfTwoSortedArrays.cpp
 * @description: There are two sorted arrays nums1 and nums2 of size m and n respectively.
                Find the median of the two sorted arrays. The overall run time complexity should be
                O(log (m+n)).
 * @sample_input:
    Case 1:
    nums1 = [1, 3]
    nums2 = [2]
    Case 2:
    nums1 = [1, 2]
    nums2 = [3, 4]
 * @sample_output:
    Case 1:
    2.0
    Case 2:
    2.5
 *
 * @author: Du Ang
 * @date: Aug. 17th, 2017
 */

#include <iostream>
#include <vector>

using namespace std;

void printArray(vector<int> myvector);

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        double median = 0;
        int totalNumber = nums1.size() + nums2.size();
        // cout << "totalNumber = " << totalNumber << endl;
        int popCount = 0;
        if (totalNumber % 2 == 0) {
            while (popCount < totalNumber / 2 - 1) {
                popOneElement(nums1, nums2);
                popCount++;
            }
            // cout << "popCount = " << popCount << endl;
            double m = popOneElement(nums1, nums2);
            // printArray(nums1);
            // printArray(nums2);
            double n = popOneElement(nums1, nums2);
            cout << "m = " << m << " n = " << n << endl;
            median = (m + n) / 2;
        } else {
            while (popCount < totalNumber / 2) {
                popOneElement(nums1, nums2);
                popCount++;
            }
            // cout << "popCount = " << popCount << endl;
            median = popOneElement(nums1, nums2);
        }
        return median;
    }

    int popOneElement(vector<int>& nums1, vector<int>& nums2) {
        int n;
        if (nums1.empty()) {
            n = *(nums2.end() - 1);
            nums2.pop_back();
        } else if (nums2.empty()) {
            n = *(nums1.end() - 1);
            nums1.pop_back();
        } else {
            if (*(nums1.end() - 1) > *(nums2.end() - 1)) {
                n = *(nums1.end() - 1);
                nums1.pop_back();
            } else {
                n = *(nums2.end() - 1);
                nums2.pop_back();
            }
        }
        return n;
    }
};

void createSortedArray(vector<int> &array) {
    int n;
    cin >> n;
    if (n == -1) {
        std::cout << "Error: The array can't be empty!" << std::endl;
        exit(-1);
    } else {
        array.push_back(n);
        while (true) {
            std::cin >> n;
            if (n == -1) {
                break;
            }
            array.push_back(n);
        }
    }
}

void printArray(vector<int> myvector) {
    for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
        cout << ' ' << *it;
    cout << endl;
}

int main(int argc, char const *argv[]) {
    vector<int> a, b;
    createSortedArray(a);
    createSortedArray(b);
    printArray(a);
    printArray(b);
    Solution s;
    double median = s.findMedianSortedArrays(a, b);
    cout << "median = " << median << endl;
    return 0;
}
