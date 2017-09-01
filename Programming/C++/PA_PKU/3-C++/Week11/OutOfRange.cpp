/**
 * @file: OutOfRange.cpp
 * @description: out_of_range 异常示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 1st, 2017
 */

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char const *argv[]) {
    vector<int> v(10);
    try {
        v.at(100) = 100;                // throw out_of_range exception
    } catch (out_of_range &e) {
        cerr << e.what() << endl;      // vector
    }
    string s = "hello";
    try {
        char c = s.at(100);
    } catch (out_of_range &e) {
        cerr << e.what() << endl;      // basic_string
    }
    return 0;
}
