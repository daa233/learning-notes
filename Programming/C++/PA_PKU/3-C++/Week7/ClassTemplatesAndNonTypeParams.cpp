/**
 * @file: ClassTemplatesAndNonTypeParams.cpp
 * @description: 类模板与非类型参数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 25th, 2017
 */

#include <iostream>

using namespace std;

template <class T, int size>
class CArray {
public:
    T array[size];
    void print() {
        for (int i = 0; i < size; ++i) {
            cout << array[i] << endl;
        }
    }
};

int main(int argc, char const *argv[]) {
    CArray<double, 10> a1;
    CArray<int, 20> a2;

    for (int i = 0; i < 10; ++i) {
        a1.array[i] = i + 2.8;
    }

    for (int i = 0; i < 20; ++i) {
        a2.array[i] = i;
    }

    a1.print();
    a2.print();

    return 0;
}
