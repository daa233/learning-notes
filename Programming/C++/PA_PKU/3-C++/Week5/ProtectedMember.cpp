/**
 * @file: ProtectedMember.cpp
 * @description: 访问范围说明符 protected
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 22nd, 2017
 */

#include <iostream>

class Father {
private:
    int nPrivate;
public:
    int nPublic;
protected:
    int nProtected;
};

class Son : public Father {
    void AccessFather() {
        nPublic = 1;        // OK
        // nPrivate = 1;       // error: 'nPrivate' is a private member of 'Father'
        nProtected = 1;     // OK
        Son f;              // f is not the object of AccessFather() function
        // f.nProtected = 1;   // error: 'nPrivate' is a private member of 'Father'
    }
};

int main(int argc, char const *argv[]) {
    Father f;
    Son s;
    f.nPublic = 1;  // OK
    s.nPublic = 1;  // OK
    // f.nProtected = 1;   // error: 'nPrivate' is a private member of 'Father'
    // f.nPrivate = 1;     // error: 'nPrivate' is a private member of 'Father'
    // s.nProtected = 1;   // error: 'nPrivate' is a private member of 'Father'
    // s.nPrivate = 1;     // error: 'nPrivate' is a private member of 'Father'
    return 0;
}
