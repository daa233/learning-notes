/**
 * 指针与二维数组练习 编程题＃3：文字排版
 *
 * @file: TextTypeset.cpp
 * @description: 给一段英文短文，单词之间以空格分隔（每个单词包括其前后紧邻的标点符号）。请将短文重新排版，要求如下：
                每行不超过80个字符；每个单词居于同一行上；在同一行的单词之间以一个空格分隔；行首和行尾都没有空格。
 * @input: 第一行是一个整数n，表示英文短文中单词的数目. 其后是n个以空格分隔的英文单词（单词包括其前后紧邻的标点符号，
        且每个单词长度都不大于40个字母）。
 * @output: 排版后的多行文本，每行文本字符数最多80个字符，单词之间以一个空格分隔，每行文本首尾都没有空格。
 * @sample_input:
    84
    One sweltering day, I was scooping ice cream into cones and told my four children they could "buy" a cone from me for a hug. Almost immediately, the kids lined up to make their purchases. The three youngest each gave me a quick hug, grabbed their cones and raced back outside. But when my teenage son at the end of the line finally got his turn to "buy" his ice cream, he gave me two hugs. "Keep the changes," he said with a smile.
 * @sample_output:
    One sweltering day, I was scooping ice cream into cones and told my fo
    urchildren they could "buy" a cone from me for a hug. Almost immediate
    ly, the kidslined up to make their purchases. The three youngest each
    gave me a quick hug,grabbed their cones and raced back outside. But wh
    en my teenage son at the endof the line finally got his turn to "buy"
    his ice cream, he gave me two hugs."Keep the changes," he said with a
    smile.
 *
 * @author: Du Ang
 * @date: Aug. 8th, 2017
 */

#include <iostream>

using namespace std;

// Given a chars array, return the characters it contains
int countWordChars(char *words)
{
    int counts = 0;
    for (int i = 0; words[i] != '\0'; i++) {
        counts++;
    }
    return counts;
}

int main(int argc, char const *argv[]) {
    int n;
    cin >> n;
    char words[n][40];
    int charsLimitNum = 80;    // the limit number of chars in each line
    int lineCharsNum = 0;     // the number of chars in current line

    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }

    for (int i = 0; i < n; i++) {
        int wordCharsNum = countWordChars(words[i]);
        if (lineCharsNum + wordCharsNum > 80) {
            cout << endl;
            lineCharsNum = 0;
            i--;
        } else {
            cout << words[i] << " ";
            lineCharsNum = lineCharsNum + wordCharsNum + 1;
        }

    }
    cout << endl;
    return 0;
}
