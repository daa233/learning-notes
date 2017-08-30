/**
 * @file: FunctionObjectSample.cpp
 * @description: 函数对象示例
                利用 accumulate 求一组数的幂和
                greater 的应用
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 29th, 2017
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
#include <list>

using namespace std;

class CMyAverage {
public:
    double operator()(int a1, int a2, int a3) {
        return (double)(a1 + a2 + a3) / 3;
    }
};

int sumSquares(int total, int value) {  // compute total + value ^ 2
    return total + value * value;
}

template <class T>
void printInterval(T first, T last) {
    // print elements range [first, last)
    for ( ; first != last; ++first) {
        cout << *first << " ";
    }
    cout << endl;
};

template <class T>
class SumPowers {
private:
    int power;
public:
    SumPowers(int p) : power(p) {}
    // compute total + value ^ power
    const T operator()(const T &total, const T &value) {
        T v  = value;
        // compute (v ^ power)
        for (int i = 0; i < power -  1; ++i) {
            v = v * value;
        }
        return total + v;
    }
};

class MyLess {
public:
    // here a number is samller because its single digit is small
    bool operator()(const int &c1, const int &c2) {
        return (c1 % 10) < (c2 % 10);
    }
};

template <class T>
void print(T first, T last) {
    for ( ; first != last; ++first) {
        cout << *first << ", ";
    }
}

int main(int argc, char const *argv[]) {
    CMyAverage average;
    cout << average(3, 2, 3) << endl;   // average.operator()(3, 2, 3)
    // 2.66667

    const int SIZE = 10;
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> v(a1, a1 + SIZE);
    cout << "1) ";
    printInterval(v.begin(), v.end());
    // 1) 1 2 3 4 5 6 7 8 9 10
    int result = accumulate(v.begin(), v.end(), 0, sumSquares);
    cout << "2) Sum of square: " << result << endl;
    // 2) Sum of square: 385
    result = accumulate(v.begin(), v.end(), 0, SumPowers<int>(3));
    cout << "3) Sum of cube: " << result << endl;
    // 3) Sum of cube: 3025
    result = accumulate(v.begin(), v.end(), 0, SumPowers<int>(4));
    cout << "4) Sum of quartic: " << result << endl;
    // 4) Sum of quartic: 25333

    const int SIZE_B = 5;
    int a[SIZE_B] = {5, 21, 14, 2, 3};
    list<int> lst(a, a + SIZE_B);
    lst.sort(MyLess()); // MyLess() constructs a temporary object without arguments
    print(lst.begin(), lst.end());
    // 21, 2, 3, 14, 5,
    cout << endl;
    lst.sort(greater<int>());   // greater<int> constructs a temporary object
    print(lst.begin(), lst.end());
    // 21, 14, 5, 3, 2,
    cout << endl;
    return 0;
}
