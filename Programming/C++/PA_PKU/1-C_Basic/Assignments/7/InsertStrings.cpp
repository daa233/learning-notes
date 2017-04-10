/**
 * 期末编程测试 编程题 #5：字符串插入
 *
 * @file: InsertStrings.cpp
 * @description: 有两个字符串str和substr，str的字符个数不超过10，substr的字符个数为3。（字符个数不包括字符串结尾处
                的'\0'。）将substr插入到str中ASCII码最大的那个字符后面，若有多个最大则只考虑第一个。
 * @input: 输入包括若干行，每一行为一组测试数据，格式为str substr
 * @output: 对于每一组测试数据，输出插入之后的字符串。
 * 样例输入
    abcab eee
    12343 555
 * 样例输出
    abceeeab
    12345553
 *
 * @author: Du Ang
 * @date: Apr. 10th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    char str[13], substr[3];
    while (cin >> str >> substr) {
        int maxIndex = 0;   // 记录str[]中ASSCI码最大的字符的索引
        int max;            // 记录str[]中ASSCI码最大的字符的ASSCI值
        int len = 0;        // str[]的长度
        for (int i = 0; str[i] != '\0'; i++) {
            if (i == 0) {
                max = str[i];
                maxIndex = 0;
            } else if (max < str[i]) {
                max = str[i];
                maxIndex = i;
            }
            len++;
        }
        for (int i = len+3; i > maxIndex+3; i--) {
            str[i] = str[i-3];
        }
        for (int i = 0; i < 3; i++) {
            str[maxIndex+i+1] = substr[i];
        }
        cout << str << endl;
    }
    return 0;
}
