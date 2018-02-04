/**
 * @file: BinaryFileIO.cpp
 * @description: 二进制文件读写示例
                希望能从键盘输入几个学生的姓名的成绩，并以二进制文件的形式存起来。
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 24th, 2017
 */

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class CStudent {
public:
    char szName[20];
    int nScore;
};

int main(int argc, char const *argv[]) {
    CStudent s;
    cout << "Input the number of the operation which you want to take: " << endl;
    cout << "1. write binary data to 'students.dat'" << endl;
    cout << "2. read the binary data of 'stduents.dat'" << endl;
    cout << "3. modify the binary data of 'stduents.dat'" << endl;
    int option;
    cin >> option;

    switch (option) {
    // error: cannot jump from switch statement to this case label
    // https://stackoverflow.com/questions/92396/why-cant-variables-be-declared-in-a-switch-statement
    // use {} to prevent the error
    case 1: {
        ofstream outFile("students.dat", ios::out | ios::binary);
        while (cin >> s.szName >> s.nScore) {
            if (strcmp(s.szName, "exit") == 0)
                break;
            outFile.write((char *)&s, sizeof(s));
        }
        outFile.close();
        break;
    }
    case 2: {
        ifstream inFile("students.dat", ios::in | ios::binary);
        if (!inFile) {
            cout << "Error to read the file!" << endl;
            return 0;
        }
        while (inFile.read((char *)&s, sizeof(s))) {
            int nReadedBytes = inFile.gcount(); // get the bytes of readed
            cout << s.szName << " " << s.nScore << endl;
        }
        inFile.close();
        break;
    }
    case 3: {
        fstream iofile("students.dat", ios::in | ios::out | ios::binary);
        if (!iofile) {
            cout << "Error to read the file!" << endl;
            return 0;
        }
        iofile.seekp(2 * sizeof(s), ios::beg);  // locate the 3rd record
        iofile.write("Mike", strlen("Mike") + 1);
        iofile.seekg(0, ios::beg);              // locate the beginning
        while (iofile.read((char *)&s, sizeof(s))) {
            cout << s.szName << " " << s.nScore << endl;
        }
        iofile.close();
        break;
    }
    default:
        break;
    }
    return 0;
}
