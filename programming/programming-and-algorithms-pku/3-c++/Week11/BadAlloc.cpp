/**
 * @file: BadAlloc.cpp
 * @description: bad_alloc 示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 1st, 2017
 */

#include <iostream>
#include <stdexcept>

using namespace std;

int main(int argc, char const *argv[]) {
    try {
        char *p = new char[0x7fffffffffffff];
        delete[] p;
    } catch (bad_alloc &e) {
        cerr << e.what() << endl;   // std::bad_alloc
    }
    return 0;
}
