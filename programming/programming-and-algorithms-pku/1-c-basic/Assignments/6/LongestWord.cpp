/**
 * C程序中的数组 数组应用练习 编程题 #3：最长单词2
 *
 * @file: LongestWord.cpp
 * @description: 一个以'.'结尾的简单英文句子，单词之间用空格分隔，没有缩写形式和其它特殊形式，求其中最长的单词。
 * @input: 一个以'.'结尾的简单英文句子（长度不超过500），单词之间用空格分隔，没有缩写形式和其它特殊形式
 * @output: 该句子中最长的单词。如果多于一个，则输出第一个
 * 样例输入
    第一组
    I am a student of Peking University.
    第二组
    Hello world.
 * 样例输出
    第一组
    University
    第二组
    Hello
 *
 * @author: Du Ang
 * @date: Apr. 7th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    const int counts = 500;     // 输入字符串的最大长度
    char s[counts] = "";        // 存储输入的字符串
    int maxLeftIndex = 0, maxLen = 0;   // 最长单词的左侧下标索引及长度
    int tempLen = 0, tempLeftIndex = 0; // 临时单词的左侧下标索引及长度
    int i = 0;
    cin.getline(s, counts);     // 输入句子

    while (s[i] != '.') {
        if (s[i] != ' ') {
            tempLen++;
        } else {
            if (maxLen == 0) {
                maxLen = tempLen;   // maxLen中还未存储单词长度时，先把首个tempLen赋给maxLen
            } else {
                if (maxLen < tempLen) {
                    // 新的单词比之前的max长，更新最长单词索引及长度
                    maxLen = tempLen;
                    maxLeftIndex = tempLeftIndex;
                }
            }
            tempLeftIndex = i + 1;
            tempLen = 0;
        }
        i++;
    }

    if (maxLen < tempLen) {
        // 最后一个单词比之前的max长，更新最长单词索引及长度
        maxLen = tempLen;
        maxLeftIndex = tempLeftIndex;
    }

    for (i = maxLeftIndex; i < maxLeftIndex + maxLen; i++) {
        cout << s[i];
    }
    cout << endl;

    return 0;
}
