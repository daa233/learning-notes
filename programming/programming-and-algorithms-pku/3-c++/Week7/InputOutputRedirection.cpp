/**
 * @file: InputOutputRedirection.cpp
 * @description: 输入输出重定向
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 25th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    double f;
    int n;
    freopen("in.txt", "r", stdin);      // redirect stdin
    cin >> f >> n;
    freopen("out.txt", "w", stdout);    // redirect stdout
    if (n == 0) {
        cerr << "error" << endl;        // won't print to "out.txt"
    }
    else {
        cout << f / n << endl;
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}
