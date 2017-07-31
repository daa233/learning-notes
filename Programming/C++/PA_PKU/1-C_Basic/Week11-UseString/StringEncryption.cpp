/**
 * @file: StringEncryption.cpp
 * @description: 输入一个字符串，把每个字符变成它后续字符，如果是‘Z’或者‘z’，则变成’A’或’a’.空格则不变。
                然后将变换后的字符串输出；要求能够接受连续输入。
 *
 * @author: Du Ang
 * @date: Apr. 10th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    char str[200];

    // 由于空格不做处理，所以这里采用cin.getline()方法输入
    while (cin.getline(str, 200)) {
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] == 'Z') {
                str[i] = 'A';
            } else if (str[i] == 'z') {
                str[i] = 'a';
            } else if (str[i] == ' '){
                continue;
            } else {
                str[i]++;
            }
        }
        cout << str << endl;
    }

    return 0;
}
