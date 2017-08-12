/**
 * @filename: CEmployee.cpp
 * @description: 类的访问范围
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 12th, 2017
 */

#include <iostream>

using namespace std;

class CEmployee {
private:
    char szName[30];
public:
    int salary;
    void SetName(char *name);
    void GetName(char *name);
    void AverageSalary(CEmployee e1, CEmployee e2);
};

void CEmployee::SetName(char *name) {
    strcpy(szName, name);
}

void CEmployee::GetName(char *name) {
    strcpy(name, szName);
}

void CEmployee::AverageSalary(CEmployee e1, CEmployee e2) {
    salary = (e1.salary + e2.salary) / 2;
}

int main(int argc, char const *argv[]) {
    CEmployee e;
    // strcpy(e.szName, "Tom123"); // error: 'szName' is a private member of 'CEmployee'
    e.SetName("Tom");   // OK, warning: conversion from string literal to 'char *' is deprecated
    e.salary = 5000;
    return 0;
}
