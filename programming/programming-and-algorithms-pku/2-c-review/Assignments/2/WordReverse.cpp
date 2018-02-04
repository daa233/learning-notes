/**
 * 递归编程练习 编程题 #1：单词翻转
 *
 * @file: WordReverse.cpp
 * @description: 输入一个句子（一行），将句子中的每一个单词翻转后输出。
 * @input: 只有一行，为一个字符串，不超过500个字符。单词之间以空格隔开。所谓单词指的是所有不包含空格的连续的字符。
        这道题请用cin.getline输入一行后再逐个单词递归处理。
 * @output: 翻转每一个单词后的字符串，单词之间的空格需与原文一致。
 * 样例输入
    hello   world.
 * 样例输出
    olleh   .dlrow
 *
 * @author: Du Ang
 * @date: Apr. 20th, 2017
 */

#include <iostream>

using namespace std;

void reverse(char str[], int start);

void reverse(char str[], int start)
{
    if (str[start] == '\0') {   // 已经遍历到字符串结尾，打印回车后退出
        cout << endl;
        return;
    } else {
        if (str[start] == ' ') {    // 起始处为空格，打印出来，遍历下一位置
            cout << ' ';
            return reverse(str, start+1);
        } else {    // 起始处不为空格，将这个单词翻转后的结果打印出来，然后继续从这个单词后开始遍历
            int i = start; int nextStart;
            for ( ; str[i] != ' ' && str[i] != '\0'; i++) {} nextStart = i;
            for (i = i - 1; i >= start; i--) cout << str[i];
            return reverse(str, nextStart);
        }
    }
}

int main(int argc, char const *argv[]) {
    char str[500];
    cin.getline(str, 500);
    reverse(str, 0);
    return 0;
}
