/**
 * @file: SortNumbers.cpp
 * @description: 从键盘输入10个整数，按照从大到小的顺序排列，并输出。
 * @solution: 这里采用选择排序算法
 *
 * @author: Du Ang
 * @date: Apr. 3rd, 2017
 */

#include <iostream>
#include <cstdlib>     // 为了使用atoi函数，把char转成int

using namespace std;

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        // 没有从命令行参数中输入数
        cout << "Error！ Please input some numbers as arguments." << endl;
        cout << "Usage: ./SortNumbers [num1] [num2] ..." << endl;
        return -1;
    } else if (argc > 11) {
        cout << "Error! Too many numbers, 10 at most." << endl;
        return -1;
    } else {
        // 有数从命令行参数中输入，且不超过10个
        int numbers[10];    // 方便起见，把命令行中的数存储在int型数组number[]里
        for (int i = 1; i < argc; i++) {
            numbers[i-1] = atoi(argv[i]);
        }
        // 开始排序
        for (int i = 0; i < argc-1; i++) {
            int max = numbers[i];   // 初始化为最开始的数
            for (int j = i+1; j < argc-1; j++) {
                if (max < numbers[j]) {  // 如果max比numbers[j]的值小，交换位置
                    int temp = max;
                    max = numbers[j];
                    numbers[j] = temp;
                }
                numbers[i] = max;   // 把最大值写在开始处
            }
        }
        // 输出结果
        for (int i = 0; i < argc-1; i++) {
            cout << numbers[i] << "\t";
        }
        cout << endl;
    }

    return 0;
}
