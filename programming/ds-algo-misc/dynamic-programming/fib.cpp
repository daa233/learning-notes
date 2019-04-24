/**
 * Solutions for Fibonacci Numbers
 * This is used as an introduction to Dynamic Programming
 * Reference: https://www.geeksforgeeks.org/dynamic-programming/
 *
 * For Fibonacci numbers:
 * Fn = Fn-1 + Fn-2,
 * F0 = 0 and F1 = 1.
 *
 * April 2nd, 2019.
 */

#include <iostream>

using namespace std;

// Recursion
int fib_rcs(int n)
{
    if (n <= 1) {
        return n;
    } else {
        return fib_rcs(n-1) + fib_rcs(n-2);
    }
}

// Dynamic Programming, Memoization (Top Down)
#define MAX 100
#define NIL -1

int lookup[MAX];
void _initialize()
{
    memset(lookup, NIL, MAX);    // initialize lookup table with NIL
}

int fib_dp_memoization(int n)
{
    if (lookup[n] == NIL) {
        if (n <= 1)
            lookup[n] = n;
        else
            lookup[n] = fib_dp_memoization(n-1) + fib_dp_memoization(n-2);
    }
    return lookup[n];
}


// Dynamic Programming, Tabulation (Bottom Up)
int fib_dp_tabulation(int n)
{
    int f[n+1];
    int i;
    f[0] = 0; f[1] = 1;
    for (i = 2; i <= n; i++)
        f[i] = f[i-1] + f[i-2];
    return f[n];
}

// Dynamic Programming, Tabulation (Bottom Up), Optimized
int fib_dp_tabulation_opt(int n) {
    int i, a = 0, b = 1, c;
    for (i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int main(int argc, char *argv[])
{
    // Recursion
    // int (*f)(int) = fib_rcs;

    // Dynamic Programming, Memoization
    // _initialize();
    // int (*f)(int) = fib_dp_memoization;

    // Dynamic Programming, Tabulation
    // int (*f)(int) = fib_dp_tabulation;
    int (*f)(int) = fib_dp_tabulation_opt;
    
    cout << f(4) << endl;
    return 0;
}
