/**
 * 理性认识C程序  编程题 #5：分离整数的各个数位
 *
 * @file: DigitsSplit.cpp
 * @description: 从键盘输入一个任意的三位整数，要求正确地分离出它的百位、十位和个位数，并分别在屏幕上输出，输出采用每行输出一个数的方式，不
                带其它符号。
 * @input: 一个任意的三位整数
 * @output: 一个任意的三位整数，三行三个数位
 * 样例输入
    123
 * 样例输出
    1
    2
    3
 *
 * @author: Du Ang
 * @date: Apr. 4th, 2017
 */

 #include <iostream>

 using namespace std;

 int main(int argc, char *argv[])
 {
     int n;         // 用户输入的数
     int a, b, c;   // 百位、十位、个位
     cin >> n;
     a = n / 100;
     b = (n - a * 100) / 10;
     c = (n - a * 100 - b * 10);
     cout << a << endl;
     cout << b << endl;
     cout << c << endl;
     
     return 0;
 }
