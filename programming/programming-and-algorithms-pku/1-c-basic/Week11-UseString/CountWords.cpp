/**
 * @file: CountWords.cpp
 * @description: 输入一个英文句子（不超过80个字母），统计其中有多少个单词，单词之间用空格分开。
 *
 * @author: Du Ang
 * @date: Apr. 10th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    char str[80];
    int num = 0;    // 统计的单词数目
    bool flag = false;  // 用于标志前一位是不是空格，是空格为false，不是为true
    cin.getline(str, 80);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            // 读到的当前字符为0
            flag = false;
        } else if (!flag) {
            // 读到的当前字符不是0
            flag = true;
            num++;
        }
    }
    cout << "Total words: " << num << endl;
    return 0;
}
