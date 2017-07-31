/**
 * @file: TestRecur.cpp
 * @description: 输入“abc'\n'”，会出现什么结果？
 *
 * @author: Du Ang
 * @date: Apr. 17th, 2017
 */

#include <iostream>

using namespace std;

int recur()
{
    char c;
    c = cin.get();  // cin.get()会从输入缓存区读取一个字符，能读取空格字符和回车字符。
    if (c != '\n') {
        recur();
    }
    cout << c;
    return 0;
}

int main(int argc, char *argv[])
{
    recur();    // 输入“abc'\n'”，会打印“‘\n’cba”，完成字符串的逆序输出
    return 0;
}
