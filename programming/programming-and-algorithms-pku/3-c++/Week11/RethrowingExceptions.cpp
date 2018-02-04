/**
 * @file: RethrowingExceptions.cpp
 * @description: 异常的再抛出
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Sep. 1st, 2017
 */

#include <iostream>
#include <string>

using namespace std;

class CException {
public:
    string msg;
    CException(string s) : msg(s) {}
};

double divide(double x, double y) {
    if (y == 0) {
        throw CException("divided by zero");    // the exception is not handled here
    }
    cout << "in divide" << endl;
    return x / y;
}

int countTax(int salary) {
    try {
        if (salary < 0) {
            throw -1;
        }
        cout << "counting tax" << endl;
    } catch (int) {
        cout << "salary < 0" << endl;
    }
    cout << "tax counted" << endl;
    return salary * 0.15;
}

int main(int argc, char const *argv[]) {
    double f = 1.2;
    try {
        countTax(-1);       // handle the exception in countTax() function
        // salary < 0
        // tax counted
        f = divide(3, 0);   // handle the exception out of divide() function
        cout << "end of try block" << endl; // not printed
    } catch (CException e) {
        cout << e.msg << endl;
        // divided by zero
    }
    cout << "f = " << f << endl;
    cout << "finished" << endl;
    return 0;
}
