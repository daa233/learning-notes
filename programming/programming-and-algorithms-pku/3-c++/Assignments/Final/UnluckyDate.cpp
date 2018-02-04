/**
 *  2017程序设计夏季学期练习题 编程题＃9 不吉利日期
 *
 * @file: UnluckyDate.cpp
 * @description: 在国外，每月的 13 号和每周的星期 5 都是不吉利的。特别是当 13 号那天恰好是星期 5 时，更不吉利。已
                知某年的一月一日是星期 w，并且这一年一定不是闰年，求出这一年所有 13 号那天是星期 5 的月份，按从小
                到大的顺序输出月份数字。（w = 1..7）
 * @input: 输入有一行，即一月一日星期几（w）。（1 <= w <= 7）
 * @output: 输出有一到多行，每行一个月份，表示该月的 13 日是星期五。
 * @sample_input:
    7
 * @sample_output:
    1
    10
 * @hint:
    1、3、5、7、8、10、12月各有31天
    4、6、9、11月各有30天
    2月有28天
 *
 * @author: Du Ang
 * @date: Sep. 2nd, 2017
 */

#include <iostream>

using namespace std;

int getNextStartDay(int daysOfMonth[12], int month, int startDay) {
    int nextStartDay = (daysOfMonth[month] + startDay) % 7;
    return nextStartDay;
}

int main(int argc, char const *argv[]) {
    int daysOfThisMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int startDay;
    cin >> startDay;
    startDay--;
    for (int i = 0; i < 12; i++) {
        if ((startDay + 12) % 7 == 4) {
            cout << i + 1 << endl;
        }
        startDay = getNextStartDay(daysOfThisMonth, i, startDay);
    }
    return 0;
}
