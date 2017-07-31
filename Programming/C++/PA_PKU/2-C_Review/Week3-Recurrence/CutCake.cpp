/**
 * @file: CutCake.cpp
 * @description: 用n刀会把一张饼切成多少块？
 *
 * @author: Du Ang
 * @date: Apr. 17th, 2017
 */

#include <iostream>

using namespace std;

// q(n) = q(n-1) + n
// q(0) = 1
int q(int n) {
    if (n == 0)
        return 1;
    else
        return (n + q(n-1));
}

int main(int argc, char *argv[])
{
    int n;
    cin >> n;
    cout << q(n) << endl;
    return 0;
}
