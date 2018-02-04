/**
 * @file: InputString.cpp
 * @description: 读取字符串
 *
 * @author: Du Ang
 * @date: Apr. 10th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    /* 输入字符串的三种方法：
        1. cin
        2. cin.get(ch[], length, end_char)
        3. cin.getline(ch[], length, end_char)  // end_char 默认是'\n'
    */
    char str[10];

    cout << "Choose one way to input strings: " << endl;
    int opt = 0;
    cout << "1. cin" << endl;
    cout << "2. cin.get(ch[], length, end_char)" << endl;
    cout << "3. cin.getline(ch[], length, end_char)" << endl;
    cin >> opt;
    cin.get();  // 吃掉回车
    cout << "Enter a sentence:" << endl;
    if (opt == 1) {
        /* 选择cin的方式输入
           cin 会把空格作为不同数据的区分
            输入：abc def g
            输出：abc
                 def
                 g          */
        while (cin >> str)
            cout << str << endl;
    } else if (opt == 2) {
        /* 选择cin.get()的方式输入
           输入：We are good friends.
           输出：We are g      */
        cin.get(str, 10, 'o');  // 指定终止符为'o'，不指定时，默认为'\n'
        cout << str << endl;
    } else if (opt == 3) {
        /* 选择cin.getline()的方式输入
        输入：We are good friends.
        输出：We are g      */
        cin.getline(str, 10, 'o');  // 指定终止符为'o'，不指定时，默认为'\n'
        cout << str << endl;        // 输出与cin.get()方法相同
    } else {
        cout << "Error input." << endl;
        return -1;
    }
    // 注意：cin.get()和cin.getline()的区别
    // getline遇到终止标志字符时结束，缓冲区指针移到终止标志字符之后；
    // get遇到终止字符是停止读取，指针不移动。

    return 0;
}
