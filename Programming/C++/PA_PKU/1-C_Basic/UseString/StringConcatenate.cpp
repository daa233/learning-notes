/**
 * @file: StringConcatenate.cpp
 * @description: 输入两个字符串，将其中较短的串接到较长的串的后面。要求不使用系统函数 strcat，每个输入的串的长度不超过20。
 *
 * @author: Du Ang
 * @date: Apr. 10th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    char str1[40], str2[40];
    cout << "Enter the first string: ";
    cin.getline(str1, 20);
    cout << "Enter the second string: ";
    cin.getline(str2, 20);
    int len1 = 0, len2 = 0;
    // 分别计算两个字符串的长度len1和len2
    for (len1 = 0; str1[len1] != '\0'; len1++);
    for (len2 = 0; str2[len2] != '\0'; len2++);
    // cout << "len1 = " << len1 << endl;
    // cout << "len2 = " << len2 << endl;
    if (len1 >= len2) {
        for (int i = len1; i < len1+len2; i++) {
            str1[i] = str2[i-len1];
        }
        str1[len1+len2] = '\0';     // 注意：一定要保证拼接后的字符串最后一位为'\0'
        cout << "Result: " << str1 << endl;
    } else {
        for (int i = len2; i < len1+len2; i++) {
            str2[i] = str1[i-len2];
        }
        str2[len1+len2] = '\0';     // 注意：一定要保证拼接后的字符串最后一位为'\0'
        cout << "Result: " << str2 << endl;
    }


    return 0;
}
