/**
 * @file: PointerToStruct.cpp
 * @description: 指向结构体的指针
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

void fun()
{
    student mike = {123, {'m', 'i', 'k', 'e', '\0'}};
    student *one = &mike;
    cout << (*one).id_num << " " << (*one).name << endl;
    cout << one->id_num << " " << one->name << endl;    // '->' 为指向运算符

    // error: member reference type 'student' is not a pointer;
    // cout << mike->id_num << " " << mike->name << endl;
}

void renew(student *one)
{
    one->id_num = 20130000 + one->id_num;
    for (int i = 0; one->name[i] != '\0'; i++) {
        one->name[i] = toupper(one->name[i]);
    }
}

int main(int argc, char const *argv[]) {
    fun();

    student mike = {123, {'m', 'i', 'k', 'e', '\0'}};
    renew(&mike);
    cout << mike.id_num << " " << mike.name << endl;
    return 0;
}
