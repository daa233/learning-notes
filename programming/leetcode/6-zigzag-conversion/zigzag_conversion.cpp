/** 
 * @problem: 6. ZigZag Conversion
 * @file: zigzag-conversion.cpp
 * @url: https://leetcode-cn.com/problems/zigzag-conversion
 * @description: 
 * 
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given
 * number of rows like this: (you may want to display this pattern in a
 * fixed font for better legibility)
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * 
 * And then read line by line: "PAHNAPLSIIGYIR"
 * Write the code that will take a string and make this conversion given
 * a number of rows:
 * string convert(string s, int numRows);
 * Example 1:
 * Input: s = "PAYPALISHIRING", numRows = 3
 * Output: "PAHNAPLSIIGYIR"
 * 
 * Example 2:
 * Input: s = "PAYPALISHIRING", numRows = 4
 * Output: "PINALSIGYAHRPI"
 * Explanation:
 * P     I    N
 * A   L S  I G
 * Y A   H R
 * P     I
 * 
 * @author: Du Ang
 * @date: Apr 09, 2019
 */

#include <iostream>
#include <vector>

using namespace std;


class Solution1 {
public:
    string convert(string s, int numRows) {
        if (numRows <= 1) {
            return s;
        }
        vector<char> v[numRows];
        string result = "";
        for (int i = 0; i < s.size(); i++) {
            if (numRows == 2) {
                int mod = i % numRows;
                v[mod].push_back(s[i]);
            } else {
                int mod = i % (numRows * 2 - 2);
                if (mod <= numRows - 1) {
                    v[mod].push_back(s[i]);
                } else {
                    int index = (numRows - 1) - (mod - (numRows - 1));
                    v[index].push_back(s[i]);
                }
            }
        }
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < v[i].size(); j++) {
                result.push_back(v[i][j]);
            }
        }
        return result;
    }
};

class Solution {
   public:
    string convert(string s, int numRows) {
        if (numRows <= 1) {
            return s;
        }
        string result = "";
        int len = s.size();
        for (int n = 0; n < numRows; n++) {
            int i = n;
            while (i < len) {
                result.push_back(s[i]);
                int index = i + 2 * (numRows - 1 - n);
                if (index < len && n > 0 && i != index) {
                    result.push_back(s[index]);
                }
                i = i + (numRows * 2 - 2);
            }
        }
        return result;
    }
};

int main (int argc, char *argv[])
{
    Solution s;
    cout << s.convert("PAYPALISHIRING", 2) << endl;
    cout << s.convert("PAYPALISHIRING", 3) << endl;
    cout << s.convert("PAYPALISHIRING", 4) << endl;
    return 0;
}
