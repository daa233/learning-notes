/**
 * @file: CmdArguments.cpp
 * @description: 打印命令行参数
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 11th, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << " ";
    }
    cout << endl;
    return 0;
}
