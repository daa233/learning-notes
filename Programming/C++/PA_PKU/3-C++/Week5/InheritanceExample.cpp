/**
 * @file: InheritanceExample.cpp
 * @description: 继承与派生的实例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 22nd, 2017
 */

#include <iostream>
#include <string>

using namespace std;

class CStudent {
private:
    string name;
    string id;
    char gender;    // 'F' for female, 'M' for male
    int age;
public:
    void printInfo();
    void setInfo(const string &name_, const string &id_, int age_, char gender_);
    string getName() {return name;}
};

class CUndergraduateStudent : public CStudent {
private:
    string department;
public:
    void qualifiedForBaoyan() {
        cout << "qualified for baoyan" << endl;
    }
    void printInfo() {  // override
        CStudent::printInfo();  // call printInfo() in the base class
        cout << "Department: " << department << endl;
    }
    void setInfo(const string &name_, const string &id_, int age_, char gender_,
        const string &department_) {
        CStudent::setInfo(name_, id_, age_, gender_);   // call setInfo() in the base class
        department = department_;
    }
};

void CStudent::printInfo() {
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Age: " << age << endl;
    cout << "Gender: " << gender << endl;
}

void CStudent::setInfo(const string &name_, const string &id_, int age_, char gender_) {
    name = name_;
    id = id_;
    age = age_;
    gender = gender_;
}

int main(int argc, char const *argv[]) {
    CUndergraduateStudent s2;
    s2.setInfo("Harry Potter", "118829234", 19, 'M', "Computer Science");
    cout << s2.getName() << " ";
    s2.qualifiedForBaoyan();
    s2.printInfo();
    return 0;
}
