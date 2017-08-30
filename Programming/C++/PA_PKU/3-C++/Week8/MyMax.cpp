/**
 * @file: MyMax.cpp
 * @description: 函数对象示例
                写出 MyMax 模板，使得其通过 MyLess 进行比较时，输出个位数最大的数；通过 MyCompare 比较时，输出
                个位数最小的数。
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 30th, 2017
 */

#include <iostream>
#include <iterator>

using namespace std;

class MyLess {
public:
    bool operator()(int a1, int a2) {
        if ((a1 % 10) < (a2 % 10)) {
            return true;
        } else {
            return false;
        }
    }
};

bool MyCompare(int a1, int a2) {
    if ((a1 % 10) < (a2 % 10)) {
        return false;
    } else {
        return true;
    }
}

template <class T, class BinaryOperation>
T MyMax(T first, T last, BinaryOperation op) {
    T maxIndex = first;
    first++;
    for ( ; first != last; first++) {
        if (op(*maxIndex, *first)) {
            maxIndex = first;
        }
    }
    return maxIndex;
}


int main(int argc, char const *argv[]) {
    int a[] = {35, 7, 13, 19, 12};
    cout << *MyMax(a, a + 5, MyLess()) << endl;
    cout << *MyMax(a, a + 5, MyCompare) << endl;
    return 0;
}
