/**
 * 结构体课堂练习 编程题＃1：生日相同
 *
 * @file: SameBirthday.cpp
 * @description: 在一个有 180 人的大班级中，存在两个人生日相同的概率非常大，现给出每个学生的学号，出生月日。试找出
                所有生日相同的学生。
 * @input: 第一行为整数 n，表示有 n个学生，n < 100。此后每行包含一个字符串和两个整数，分别表示学生的学号（字符串长
        度小于 10）和出生月(1 <= m <= 12)日(1 <= d <= 31)。学号、月、日之间用一个空格分隔。
 * @output: 对每组生日相同的学生，输出一行，其中前两个数字表示月和日，后面跟着所有在当天出生的学生的学号，数字、学号
        之间都用一个空格分隔。对所有的输出，要求按日期从前到后的顺序输出。对生日相同的学号，按输入的顺序输出。
 * @sample_input:
    5
    00508192 3 2
    00508153 4 5
    00508172 3 2
    00508023 4 5
    00509122 4 5
 * @sample_output:
    3 2 00508192 00508172
    4 5 00508153 00508023 00509122
 * @hint: 生日没有相同的不用输出
 *
 * @author: Du Ang
 * @date: Aug. 9th, 2017
 */

#include <iostream>

using namespace std;

struct student {
    char id[10];
    int birthMonth;
    int birthDay;
};  // Attention the ;

// Sort the struct array student* (number n) by the birthday
void sortByBirthday(student *s, int n)
{
    // sort by birth month
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (s[j].birthMonth > s[j+1].birthMonth) {
                student temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }

    // In the same month, sort by birthday
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if ((s[j].birthMonth == s[j+1].birthMonth) && (s[j].birthDay > s[j+1].birthDay)) {
                student temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }
}

bool birthdayIsSame(student a, student b) {
    if ((a.birthMonth == b.birthMonth) && (a.birthDay == b.birthDay))
        return true;
    else
        return false;
}

// My own solution
void solutionA()
{
    int n;
    cin >> n;
    student s[n];
    for (int i = 0; i < n; i++) {
        cin >> s[i].id >> s[i].birthMonth >> s[i].birthDay;
    }

    sortByBirthday(s, n);
    if (n > 1) {
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                if (birthdayIsSame(s[i], s[i+1])) {
                    cout << s[i].birthMonth << " " << s[i].birthDay << " " << s[i].id;
                }
            } else if (i == n - 1) {
                if (birthdayIsSame(s[i], s[i-1])) {
                    cout << " " << s[i].id;
                }
                cout << endl;
            } else {
                if (birthdayIsSame(s[i], s[i-1])) {
                    cout << " " << s[i].id;
                    if (!birthdayIsSame(s[i], s[i+1])) {    // the right way to add endl
                        cout << endl;
                    }
                } else if (birthdayIsSame(s[i], s[i+1])) {
                    // cout << endl;    // Presentation Error.
                    cout << s[i].birthMonth << " " << s[i].birthDay << " " << s[i].id;
                }
            }
        }
    }
}

// Copied from class example
void solutionB()
{
    int i, j, k, n, flag, count[100] = {0};
    cin >> n;
    student stu[n];
    for (int i = 0; i < n; i++) {
        cin >> stu[i].id >> stu[i].birthMonth >> stu[i].birthDay;
    }

    for (int m = 1; m <= 12; m++) {
        for (int d = 1; d <= 31; d++) {
            flag = 0;
            j = 0;
            for (int i = 0; i < n; i++) {
                if (stu[i].birthMonth == m && stu[i].birthDay == d) {
                    count[++j] = i;
                    flag++;
                }
            }
            if (flag > 1) {
                cout << m << " " << d << " ";
                for (k = 1; k <= j; k++) {
                    if (k == j) {
                        cout << stu[count[k]].id << endl;
                    } else {
                        cout << stu[count[k]].id << " ";
                    }
                }
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    solutionA();
    // solutionB();
    return 0;
}
