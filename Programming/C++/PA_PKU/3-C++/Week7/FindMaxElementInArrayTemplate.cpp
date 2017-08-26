/**
 * @file: FindMaxElementInArrayTemplate.cpp
 * @description: 编写一个 getMax() 函数的模板，用于返回一个数组中的最大值
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 24th, 2017
 */

#include <iostream>

using namespace std;

template <class T>
T getMax(T a[], int size) {
    T tmpMax = a[0];
    for (int i = 1; i < size; ++i) {
        if (tmpMax < a[i]) {
            tmpMax = a[i];
        }
    }
    return tmpMax;
}

int main(int argc, char const *argv[]) {
    int a[5] = {1, 8, 9, 23, 15};
    cout << "Max element in array a: " << getMax(a, 5) << endl;
    double b[8] = {1.2, 3.13, 4.23, 8.34, 5.3, 9.8, 9.343, 7.66};
    cout << "Max element in array b: " << getMax(b, 8) << endl;
    return 0;
}
