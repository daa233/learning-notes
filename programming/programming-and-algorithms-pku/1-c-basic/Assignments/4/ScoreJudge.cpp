/**
 * C语言中的数据成分 综合练习（1）编程题 #2：成绩判断
 *
 * @file: ScoreJudge.cpp
 * @description: 输入一个0--100的分数，判断分数代表什么等级。
                    95<=分数<=100，输出1
                    90<=分数<95，输出2
                    85<=分数<90，输出3
                    80<=分数<85，输出4
                    70<=分数<80，输出5
                    60<=分数<70，输出6
                    分数 < 60，输出7.
 * @input: n
 * @output: m
 * 样例输入
    87
 * 样例输出
    3
 *
 * @author: Du Ang
 * @date: Apr. 5th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int score;      // 成绩（0--100）
    cin >> score;   // 用户输入成绩
    if (score >= 95 && score <= 100) {
        cout << "1" << endl;
    } else if (score >= 90 && score < 95) {
        cout << "2" << endl;
    } else if (score >= 85 && score < 90) {
        cout << "3" << endl;
    } else if (score >= 80 && score < 85) {
        cout << "4" << endl;
    } else if (score >= 70 && score < 80) {
        cout << "5" << endl;
    } else if (score >= 60 && score < 70) {
        cout << "6" << endl;
    } else if (score < 60) {
        cout << "7" << endl;
    } else {
        return -1;
    }
    return 0;
}
