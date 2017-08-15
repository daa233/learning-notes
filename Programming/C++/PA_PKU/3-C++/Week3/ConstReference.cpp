/**
 * @file: ConstReference.cpp
 * @description: 常引用
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 15th, 2017
 */

#include <iostream>

class Date {
private:
    int m_year;
    int m_month;
    int m_day;
public:
    Date(int year, int month, int day) {
        setDate(year, month, day);
    }

    void setDate(int year, int month, int day) {
        m_year = year;
        m_month = month;
        m_day = day;
    }

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};

void printDate(const Date &date) {
    std::cout << date.getYear() << "/" << date.getMonth() << "/" << date.getDay() << std::endl;
}

int main(int argc, char const *argv[]) {
    Date date(2017, 8, 15);
    printDate(date);

    return 0;
}
