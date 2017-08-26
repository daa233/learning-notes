/**
 * @file: EndOfTheInputStream.cpp
 * @description: 判断输入流是否结束
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 25th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    int x;
    char buf[100];
    cin >> x;
    cin.getline(buf, 90);
    cout << buf << endl;

    // if input "12 abcd", it will output " abcd"
    // if input "12'\n'", it will terminate immediately//
    // because once geline() read '\n' in the input stream, it will return

    return 0;
}
