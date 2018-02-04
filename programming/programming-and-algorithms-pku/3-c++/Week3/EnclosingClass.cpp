/**
 * @file: EnclosingClass.cpp
 * @description:
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 14th, 2017
 */

#include <iostream>

using namespace std;

class CTyre {
private:
    int radius;
    int width;
public:
    // Member initializer lists. radius = r; width = w;
    CTyre(int r, int w) : radius(r), width(w) {
        cout << "CTyre constructor is called." << endl;
    }
    ~CTyre() {
        cout << "CTyre destructor is called." << endl;
    }
};

class CEngine {
public:
    CEngine() {
        cout << "CEngine constructor is called." << endl;
    }
    ~CEngine() {
        cout << "CEngine destructor is called." << endl;
    }
};

class CCar {    // enclosing class
private:
    int price;
    CTyre tyre;
    CEngine engine;
public:
    CCar(int p, int tr, int tw);
    ~CCar() {
        cout << "CCar destructor is called."  << endl;
    }
};

CCar::CCar(int p, int tr, int tw) : price(p), tyre(tr, tw) {
    cout << "CCar constructor is called." << endl;
}


int main(int argc, char const *argv[]) {
    CCar car(1, 2, 3);
    // CTyre constructor is called.
    // CEngine constructor is called.
    // CCar constructor is called.
    // CCar destructor is called.
    // CEngine destructor is called.
    // CTyre destructor is called.
    return 0;
}
