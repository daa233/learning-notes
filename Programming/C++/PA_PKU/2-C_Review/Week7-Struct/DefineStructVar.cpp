/**
 * @file: DefineStructVar.cpp
 * @description: 定义结构体类型的变量
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

int main(int argc, char const *argv[]) {
    student mike = {123, {'m', 'i', 'k', 'e', '\0'}};
    mike.id_num = 201300000 + mike.id_num;
    for (int i = 0; mike.name[i] != '\0'; i++) {
        mike.name[i] = toupper(mike.name[i]);   // convert lowercase letter to uppercase
    }
    cout << mike.id_num << " " << mike.name << endl;
    return 0;
}
