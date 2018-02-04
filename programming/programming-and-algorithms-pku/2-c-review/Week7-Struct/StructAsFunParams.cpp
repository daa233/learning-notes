/**
 * @file: StructAsFunParams.cpp
 * @description: 结构体做函数参数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 9th, 2017
 */

#include <iostream>

using namespace std;

struct student {
    int id_num;
    char name[10];
};

void renew(student one)
{
    one.id_num = 201300000 + one.id_num;
    for (int i = 0; one.name[i] != '\0'; i++) {
        one.name[i] = toupper(one.name[i]);
    }
    cout << one.id_num << " " << one.name << endl;
}

int main(int argc, char const *argv[]) {
    student mike = {123, {'m', 'i', 'k', 'e', '\0'}};
    renew(mike);
    cout << mike.id_num << " " << mike.name << endl;
    return 0;
}
