/**
 * @file: StructAsReturn.cpp
 * @description: 结构体做函数返回值
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

student newOne()
{
    student one = {20130123, {'M', 'I', 'K', 'E', '\0'}};
    return one;
}

int main(int argc, char const *argv[]) {
    student mike = newOne();
    cout << mike.id_num << " " << mike.name << endl;
    return 0;
}
