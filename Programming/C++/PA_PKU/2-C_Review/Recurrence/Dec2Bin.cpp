/**
 * @file: Dec2Bin.cpp
 * @description: 将一个十进制正整数转化为相应的二进制数
 *
 * @author: Du Ang
 * @date: Apr. 17th, 2017
 */

#include <iostream>

using namespace std;

void convert(int x)
{
    if ((x / 2) != 0) {
        convert(x / 2);
        cout << x % 2;  // 将输出放在递归调用之后，刚好可以完成逆序输出
    } else {
        cout << x;
    }
}

int main(int argc, char const *argv[]) {
    int n;
    cin >> n;
    convert(n);
    cout << endl;
    return 0;
}
