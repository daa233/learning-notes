/**
 * @file: CalendarProblem.cpp
 * @description: 给定从公元2000 年1月1日（星期六）开始逝去的天数，请编写程序给出这一天是哪年哪月哪日星期几。
                ●注意闰年：闰年被定义为能被4整除的年份，但是能被100整除而不能被400 整除的年是例外，它们不是闰年。
                例如：1700, 1800, 1900和2100不是闰年，而1600, 2000 和2400是闰年。可以假设结果的年份不
                会超过9999。
                ●注意每个月的天数不一样
 * @input: 输入多组数据，每组一个正整数，表示从2000年1月1日开始已经过去的天数。输入最后一行是-1，退出程序。
 * @output: 对输入的每个天数，输出一行，该行包含对应的日期和星期几。格式为："YYYY-MM-DD DayOfWeek“
            其中 "DayOfWeek"必须是：Sunday, Monday, Tuesday, Wednesday, Thursday,
             Friday and Saturday。
 * @author: Du Ang
 * @date: Apr. 16th, 2017
 */

#include <iostream>

using namespace std;

int days;   // 全局变量，应尽量避免使用
int getDayOfWeek();
int getYear();
int getMonth(bool isLeapYear);

int main(int argc, char *argv[])
{
    int year, month, dayOfWeek;
    bool isLeapYear;
    char week[7][10] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday",
     "Thursday", "Friday"};
    while (cin >> days && days != -1) {
        dayOfWeek = getDayOfWeek();
        year = getYear();
        isLeapYear = (year % 4 == 0 && year % 100 != 0 || year % 400 == 0);
        month = getMonth(isLeapYear);
        cout << year << "-" << month << "-" << ++days << " " << week[dayOfWeek];
        cout << endl;
    }
    return 0;
}

int getDayOfWeek()
{
    int dayOfWeek;
    dayOfWeek = days % 7;
    return dayOfWeek;
}

int getYear()
{
    int i = 2000;
    bool isLeapYear;
    while (true) {
        isLeapYear = (i % 4 == 0 && i % 100 != 0 || i % 400 == 0);
        if (isLeapYear && days >= 366) {
            days = days - 366;
            i++;
            continue;
        } else if (!isLeapYear && days >= 365) {
            days = days - 365;
            i++;
            continue;
        } else
            break;
    }
    return i;
}

int getMonth(bool isLeapYear)
{
    int pmonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int rmonth[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int j = 0;
    while (true) {
        if (isLeapYear && days >= rmonth[j]) {
            days = days - rmonth[j];
            j++;
        } else if (!isLeapYear && days >= pmonth[j]) {
            days = days - pmonth[j];
            j++;
        } else {
            break;
        }
    }
    return ++j;
}
