/**
 * 综合编程练习（1）编程题 #1：寻找下标
 *
 * @file: FindSubsript.cpp
 * @description: 已知一个整数数组x[],其中的元素彼此都不相同。找出给定的数组中是否有一个元素满足x[i]=i的关系，数组下标从0开始。
                举例而言，如果x[]={-2,-1,7,3,0,8},则x[3] = 3,因此3就是答案。
 * @input: 第一行包含一个整数n (0 < n < 100)，表示数组中元素的个数。第二行包含n个整数，依次表示数组中的元素。
 * @output: 输出为一个整数，即满足x[i]=i的元素，若有多个元素满足，输出第一个满足的元素。若没有元素满足，则输出“N”。
 * 样例输入
    第一组
    6
    -2 -1 7 3 4 8
    第二组
    6
    9 9 9 9 9 9
 * 样例输出
    第一组
    3
    第二组
    N
 *
 * @author: Du Ang
 * @date: Apr. 16th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int n;
    int x[n];
    cin >> n;
    int i;
    for (i = 0; i < n; i++) {
        cin >> x[i];
        if (x[i] == i) {
            cout << x[i] << endl;
            break;
        }
    }
    if (i == n) {
        cout << "N" << endl;
    }
    return 0;
}
