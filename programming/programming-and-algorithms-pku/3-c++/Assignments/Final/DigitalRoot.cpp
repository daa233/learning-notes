/**
 *  2017程序设计夏季学期练习题 编程题＃7 数根
 *
 * @file: DigitalRoot.cpp
 * @description: 数根可以通过把一个数的各个位上的数字加起来得到。如果得到的数是一位数，那么这个数就是数根。如果结果
                是两位数或者包括更多位的数字，那么再把这些数字加起来。如此进行下去，直到得到是一位数为止。
                比如，对于 24 来说，把 2 和 4 相加得到 6，由于 6 是一位数，因此 6 是 24 的数根。再比如 39，把
                3 和 9 加起来得到 12，由于 12 不是一位数，因此还得把 1 和 2 加起来，最后得到 3，这是一个一位数，
                因此 3 是 39 的数根。
 * @input: 一个正整数(小于10^1000)。
 * @output: 一个数字，即输入数字的数根。
 * @sample_input:
    24
 * @sample_output:
    6
 *
 * @author: Du Ang
 * @date: Sep. 2nd, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    string num;
    cin >> num;
    while (num.size() > 1) {
        int sum = 0;
        for (int i = 0; i < num.size(); i++) {
            sum = sum + (int)num[i] - 48;
        }
        num = to_string(sum);
    }
    cout << num << endl;
    return 0;
}
