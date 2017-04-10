/**
 * 期末编程测试 编程题 #2：能被3、5、7整除的数
 *
 * @file: DivisableBy357.cpp
 * @description: 输入一个整数，判断它能否被3，5，7整除，并输出以下信息：
                1、能同时被3，5，7整除（直接输出3 5 7，每个数中间一个空格）；
                2、能被其中两个数整除（输出两个数，小的在前，大的在后。例如：3 5或者 3 7或者5 7,中间用空格分隔）
                3、能被其中一个数整除（输出这个除数）
                4、不能被任何数整除；（输出小写字符'n',不包括单引号)
 * @input: 一个数字
 * @output: 一行数字,从小到大排列,包含3,5,7中为该输入的除数的数字,数字中间用空格隔开
 * 样例输入
    第一组
    0
    第二组
    5
    第三组
    15
    第四组
    105
    第五组
    1
 * 样例输出
    第一组
    3 5 7
    第二组
    5
    第三组
    3 5
    第四组
    3 5 7
    第五组
    n
 * @hint: 因为有多组测试数据,程序通过下面方式读入n
            int n;
            while(cin>>n)
            {
                //你的代码
            }
            good luck:)
 *
 * @author: Du Ang
 * @date: Apr. 10th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int n;
    while (cin >> n) {
        if (n % 3 == 0) {
            if (n % 5 == 0) {
                // 既能被3整除，也能被5整除
                if (n % 7 == 0) {
                    cout << "3 5 7" << endl;
                } else {
                    cout << "3 5" << endl;
                }
            } else {
                // 能被3整除，但不能被5整除
                if (n % 7 == 0) {
                    cout << "3 7" << endl;
                } else {
                    cout << "3" << endl;
                }
            }
        } else if (n % 5 == 0) {
            // 不能被3整除，但能被5整除
            if (n % 7 == 0) {
                // 能被5和7整除
                cout << "5 7" << endl;
            } else {
                cout << "5" << endl;
            }
        } else if (n % 7 == 0) {
            cout << "7" << endl;    // 只能被7整除
        } else {
            cout << "n" << endl;    // 不能被3或5或7整除
        }
    }
    return 0;
}
