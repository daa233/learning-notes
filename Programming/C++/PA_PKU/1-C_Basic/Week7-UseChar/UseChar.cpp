/**
 * @file: UseChar.cpp
 * @description: char型使用须知
 *
 * @author: Du Ang
 * @date: Apr. 5th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    char a = 64;
    int b = 'Z';
    int c = b - a;
    char d = 6;         // ubuntu的终端没能打印出这个字符
    char e = 64 + 256;  // warning: overflow in implicit constant conversion
    cout << a << " " << b << " " << c << " " << d << " " << e << endl;

    // 转义字符
    cout << "This is the first line!\n";    // \n表示换行
    cout << '\a' << '\\' << '\n';           // |a表示响铃（我的Dell小本本啥声音都木有），\\表示反斜线
    return 0;
}
