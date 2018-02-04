/**
 * C++初探 编程题＃1：简单的学生信息处理程序实现
 *
 * @file: SimpleStudentsInfoProcess.cpp
 * @description: 在一个学生信息处理程序中，要求实现一个代表学生的类，并且所有成员变量都应该是私有的。
            （注：评测系统无法自动判断变量是否私有。我们会在结束之后统一对作业进行检查，请同学们严格按照题目要求完成，
            否则可能会影响作业成绩。）
 * @input: 姓名，年龄，学号，第一学年平均成绩，第二学年平均成绩，第三学年平均成绩，第四学年平均成绩。
        其中姓名、学号为字符串，不含空格和逗号；年龄为正整数；成绩为非负整数。各部分内容之间均用单个英文逗号","隔开，
        无多余空格。
 * @output: 一行，按顺序输出：姓名，年龄，学号，四年平均成绩（向下取整）。
        各部分内容之间均用单个英文逗号","隔开，无多余空格。
 * @sample_input:
    Tom,18,7817,80,80,90,70
 * @sample_output:
    Tom,18,7817,80
 *
 * @author: Du Ang
 * @date: Aug. 13th, 2017
 */

#include <iostream>

using namespace std;

class Student {
private:
    char name[20];
    unsigned int age;
    char stu_id[20];
    unsigned int first_year_score;
    unsigned int second_year_score;
    unsigned int third_year_score;
    unsigned int fourth_year_score;

public:
    void get_input() {
        char dummy;
        cin.getline(name, 20, ',');
        cin >> age >> dummy;
        cin.getline(stu_id, 20, ',');
        cin >> first_year_score >> dummy >> second_year_score >> dummy >> third_year_score \
            >> dummy >> fourth_year_score;
    }

    void print_output() {
        unsigned int average_score;
        average_score = (first_year_score + second_year_score + third_year_score \
                        + fourth_year_score) / 4;
        cout << name << "," << age << "," << stu_id << "," << average_score << endl;
    }
};

int main(int argc, char const *argv[]) {
    Student student;
    student.get_input();
    student.print_output();
    return 0;
}
