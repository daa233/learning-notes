/**
 * @file: Fab.cpp
 * @description: 求斐波那契数列的第n个数
 *
 * @author: Du Ang
 * @date: Apr. 17th, 2017
 */

#include <iostream>

using namespace std;

// f(n) = f(n-1) + f(n-2)
// f(1) = f(2) = 1
int f(int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 1;
    else
        return (f(n-1) + f(n-2));
}

int main(int argc, char *argv[])
{
    int n;
    cin >> n;
    cout << f(n) << endl;
    return 0;
}
