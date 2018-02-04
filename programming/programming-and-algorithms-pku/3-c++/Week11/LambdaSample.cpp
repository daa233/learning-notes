/**
 * @file: LambdaSample.cpp
 * @description: C++11 新特性，Lambda 表达式使用示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 4th, 2017
 */

#include <iostream>
#include <vector>
#include <algorithm>    // sort()

using namespace std;

int main(int argc, char const *argv[]) {
    int x = 100, y = 200, z = 300;
    cout << [](double a, double b) { return a + b; } (1.2, 2.5) << endl;    // 3.7
    auto ff = [=, &y, &z](int n) {
        cout << x << endl;              // 100
        y++;
        z++;
        return n * n;
    };
    cout << ff(15) << endl;             // 225
    cout << y << ", " << z << endl;     // 201, 301

    int a[4] = {4, 2, 11, 33};
    sort(a, a + 4, [](int x, int y) -> bool { return x % 10 < y % 10; });
    for_each(a, a + 4, [](int x) {cout << x << " ";});  // 11 2 33 4
    cout << endl;

    int n = 0;
    int b[] = {1, 2, 3, 4};
    for_each(b, b + 4, [&](int e) { ++e; n += e; });
    cout << n << ", " << b[2] << endl;  // 14, 3

    vector<int> c{1, 2, 3, 4};
    int total = 0;
    for_each(c.begin(), c.end(), [&](int &x) { total += x; x *= 2; });
    cout << total << endl;              // 10
    for_each(c.begin(), c.end(), [](int x) {cout << x << " ";});    // 2 4 6 8
    cout << endl;

    // use lambda function to find the nth item of Fibonacci Sequence
    function<int(int)> fib = [&fib](int n) {
        return n <= 2 ? 1 : fib(n - 1) + fib(n - 2);
    };
    cout << fib(5) << endl;             // 5

    return 0;
}
