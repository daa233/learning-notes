/**
 * @file: StructArray.cpp
 * @description: 结构体数组
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
    student myClass[3] = {
        123, {'m', 'i', 'k', 'e', '\0'},
        133, {'t', 'o', 'm', '\0'},
        143, {'j', 'a', 'c', 'k', '\0'}
    };
    student *one = myClass;
    cout << one->id_num << " " << one->name << endl;
    one++;
    cout << one->id_num << " " << one->name << endl;
    return 0;
}
