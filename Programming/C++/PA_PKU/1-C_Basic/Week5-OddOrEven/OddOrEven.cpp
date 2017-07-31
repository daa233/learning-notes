/**
 * @file: OddOrEven.cpp
 * @description: 从键盘输入10个整数，将其中的奇数和偶数分别放入不同的数组，并输出。
 * @solution: 从命令行参数输入10个数，依次模2判断，结果存入两个长度为10的数组。
 *
 * @author: Du Ang
 * @date: Apr. 3rd, 2017
 */

#include <iostream>
#include <cstdlib>      // 为了使用atoi函数，把char转成int

using namespace std;

int main(int argc, char *argv[])
{
    int odd[10], even[10];  // odd[]存放奇数， even[]存放偶数
    int idxOdd = 0, idxEven = 0;    // 用于索引odd[], even[]的当前位置

    if (argc <= 1) {
        // 没有从命令行参数中输入数
        cout << "Error！ Please input some numbers as arguments." << endl;
        cout << "Usage: ./OddOrEven [num1] [num2] ..." << endl;
        return -1;
    } else if (argc > 11) {
        cout << "Error! Too many numbers, 10 at most." << endl;
        return -1;
    } else {
        // 有数从命令行参数中输入，且不超过10个
        for (int i = 1; i < argc; i++) {
            if (atoi(argv[i]) % 2 == 0) {
                even[idxEven] = atoi(argv[i]);    // 可以被2整除，偶数，存入even[]
                idxEven++;
            } else {
                odd[idxOdd] = atoi(argv[i]);      // 不可以被2整除，奇数，存入odd[]
                idxOdd++;
            }
        }

        cout << " Odd Numbers: ";
        for (int i = 0; i < idxOdd; i++) {
            cout << odd[i] << "\t";
        }
        cout << "\nEven Numbers: ";
        for (int i = 0; i < idxEven; i++) {
            cout << even[i] << "\t";
        }
        cout << endl;
    }
    return 0;
}
