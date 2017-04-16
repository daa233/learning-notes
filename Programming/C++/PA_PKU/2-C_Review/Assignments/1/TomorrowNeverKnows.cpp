/**
 * 综合编程练习（1）编程题 #4：Tomorrow never knows?
 *
 * @file: TomorrowNeverKnows.cpp
 * @description: 甲壳虫的《A day in the life》和《Tomorrow never knows》脍炙人口，如果告诉你
                a day in the life,真的会是tomorrow never knows?相信学了计概之后这个不会是难题，现在就来
                实现吧。
                读入一个格式为yyyy-mm-dd的日期（即年－月－日），输出这个日期下一天的日期。可以假定输入的日期不早于
                1600-01-01，也不晚于2999-12-30。
 * @input: 输入仅一行，格式为yyyy-mm-dd的日期。
 * @output: 输出也仅一行，格式为yyyy-mm-dd的日期
 * 样例输入
    2010-07-05
 * 样例输出
    2010-07-06
 * @hint: 闰年的标准：
        (1)普通年能被4整除且不能被100整除的为闰年。（如2004年就是闰年,1901年不是闰年）
        (2)世纪年能被400整除的是闰年。(如2000年是闰年，1100年不是闰年)
        可以利用一个字符变量吃掉输入的短横线（减号），输出时请活用setfill和setw 控制符。
 *
 * @author: Du Ang
 * @date: Apr. 16th, 2017
 */

#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    int currentYear, currentMonth, currentDay;
    char dummy;
    cin >> currentYear >> dummy >> currentMonth >> dummy >> currentDay;
    bool isLeapYear = false;
    int pmonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int rmonth[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (currentMonth == 12) {
        if (currentDay == pmonth[11]) {  // 当前是一年中的最后一天，下一天是新年第一天
            currentYear++;
            currentMonth = 1;
            currentDay = 1;
        } else {
            currentDay++;   // 12月的普通一天
        }
    } else if (currentMonth == 2) { // 这个月是2月
        if (currentDay == 29) { // 当前是闰年2月的最后一天
            currentMonth++;
            currentDay = 1;
        } else if (currentDay == 28) {  // 当前是2月28号
            isLeapYear = (currentYear % 4 == 0 && currentYear % 100 != 0
                            || currentYear % 400 == 0);
            if (isLeapYear) {
                currentDay++;
            } else {
                currentMonth++; currentDay = 1;
            }
        } else {
            currentDay++;
        }
    } else {
        if (currentDay == pmonth[currentMonth-1]) { // 当前是本月最后一天
            currentMonth++; currentDay = 1;
        } else {
            currentDay++;
        }
    }
    cout << currentYear << "-";
    cout << setfill('0') << setw(2) << currentMonth << "-";
    cout << setfill('0') << setw(2) << currentDay << endl;

    return 0;
}
