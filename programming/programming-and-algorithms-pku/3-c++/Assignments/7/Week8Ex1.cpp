/**
 *  标准模板库 STL-1 编程题＃1
 *
 * @file: Week8Ex1.cpp
 * @description: 程序填空
                下面的程序输出结果是:
                    1 2 6 7 8 9
 * @sample_input:
    none
 * @sample_output:
    1 2 6 7 8 9
 *
 * @author: Du Ang
 * @date: Aug. 30th, 2017
 */

#include <iostream>
#include <iterator>
#include <set>

using namespace std;

int main() {
    int a[] = {8, 7, 8, 9, 6, 2, 1};
    // 在此处补充你的代码
    set<int> v(a, a + 7);
    ostream_iterator<int> o(cout, " ");
    copy(v.begin(), v.end(), o);
    return 0;
}
