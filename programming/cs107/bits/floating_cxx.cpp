#include <iostream>
#include <bitset>

using std::cout;
using std::endl;
using std::bitset;

int main()
{
    int a = 37;
    bitset<32> x(a);
    cout << "int " << a << " (" << x << ")" << endl;
    // NOTE: the float points are represented as
    // |+/-|----exp----|------------frac--------------|
    // +/- 1.frac * 2^exp
    float f = *(float *)&a; // interpret the memory of int as float
    cout << "int " << a << " -> float " << f << endl;      // 5.1848e-44

    f = 7.34;
    x = *(int *)&f;
    cout << "float " << f << " (" << x << ")" << endl;

    short s = *(short *)&f; // interpret the memory of float as short
    bitset<16> y(s);
    cout << "float " << f << " -> short " << s << " (" << y << ")" << endl;

    return 0;
}

// Output:
// int 37 (00000000000000000000000000100101)
// int 37 -> float 5.1848e-44
// float 7.34 (01000000111010101110000101001000)
// float 7.34 -> short -7864 (1110000101001000)