/**
 * @file: FileCopy.cpp
 * @description: 编写一个 mycopy 程序，实现文件的拷贝
                usage: mycopy src.dat dst.dat
                即将 src.dat 拷贝到 dst.dat，如果 dst.dat 原来就有，则覆盖原来的文件
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 24th, 2017
 */

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        cout << "File name missing!" << endl;
        return 0;
    }
    ifstream inFile(argv[1], ios::binary | ios::in);    // open source file to read
    if (!inFile) {
        cout << "Source file open error." << endl;
        return 0;
    }
    ofstream outFile(argv[2], ios::binary | ios::out);  // open destination file
    if (!outFile) {
        cout << "Destination file open error." << endl;
        inFile.close();     // the opened file must be closed!
        return 0;
    }
    char c;
    while (inFile.get(c)) { // read one char each time
        outFile.put(c);     // write one char each time
    }
    outFile.close();
    inFile.close();
    return 0;
}
