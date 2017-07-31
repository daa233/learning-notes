/**
 * @file: OddEvenSort.cpp
 * @description: 从键盘输入10个整数(0~100)，彼此空格分隔，重新排序后输出。要求：
 *              1.先输出其中的奇数，并按从大到小排列；2.然后输出其中的偶数，并按从小到大排列。
 * @solution: 先判断奇偶，分别存入两个数组；再分别对这两个数组进行排序。
 *
 * @author: Du Ang
 * @date: Apr. 3rd, 2017
 */

#include <iostream>
#include <cstdlib>      // 为了使用atoi函数，把char转成int

using namespace std;

// 定义子函数，将数组numbers[]从大到小或从小到大排列，然后打印输出。
void sort(int numbers[], int length, bool flag);

int main(int argc, char *argv[])
{
    int numbers[10];    // 方便起见，把命令行中的数存储在int型数组number[]里
    int count = argc-1; // 输入数的总个数（虽然要求10个，但我想小于10个也支持）
    int odd[10], even[10];  // odd[]存放奇数， even[]存放偶数
    int idxOdd = 0, idxEven = 0;    // 用于索引odd[], even[]的当前位置

    int const ODD = true;   // 用于排序前判断奇偶，奇数为true，偶数为false
    int const EVEN = false;

    if (argc <= 1) {
        // 没有从命令行参数中输入数
        cout << "Error！ Please input some numbers as arguments." << endl;
        cout << "Usage: ./OddEvenSort [num1] [num2] ..." << endl;
        return -1;
    } else if (argc > 11) {
        cout << "Error! Too many numbers, 10 at most." << endl;
        return -1;
    } else {
        // 有数从命令行参数中输入，且不超过10个
        for (int i = 1; i < argc; i++) {
            numbers[i-1] = atoi(argv[i]);   // 将argv[]里的值赋给numbers[]
        }
        // 判断奇偶性，奇数存放于odd[]，偶数存放于even[]
        for (int i = 0; i < count; i++) {
            if (numbers[i] % 2 == 0) {
                even[idxEven] = numbers[i];    // 可以被2整除，偶数，存入even[]
                idxEven++;
            } else {
                odd[idxOdd] = numbers[i];      // 不可以被2整除，奇数，存入odd[]
                idxOdd++;
            }
        }

        // 对奇偶数组分别进行排序，输出
        cout << " Odd Numbers: ";
        sort(odd, idxOdd, ODD);
        cout << "Even Numbers: ";
        sort(even, idxEven, EVEN);
    }
    return 0;
}

/*
 * 定义子函数sort（参考../SortNumbers/SortNumbers.cpp）
 * @param int numbers[]: 输入的待排序整型数组
 * @param int length: 数组的有效长度
 * @param bool flag: 为true时，从大到小排列；为false时从小到大排列
 */
void sort(int numbers[], int length, bool flag)
{
    for (int i = 0; i < length; i++) {
        int ref = numbers[i];   // 定义参考值ref，并初始化为最开始的数
        for (int j = i+1; j < length; j++) {
            if (flag) {
                // 如果flag为true，则从大到小排列
                if (ref < numbers[j]) {  // 如果ref比numbers[j]的值小，交换位置
                    int temp = ref;
                    ref = numbers[j];
                    numbers[j] = temp;
                }
                numbers[i] = ref;   // 把最大值写在开始处
            } else {
                // 如果flag为false，则从小到大排列
                if (ref > numbers[j]) {  // 如果ref比numbers[j]的值大，交换位置
                    int temp = ref;
                    ref = numbers[j];
                    numbers[j] = temp;
                }
                numbers[i] = ref;   // 把最小值写在开始处
            }

        }
    }
    // 输出结果
    for (int i = 0; i < length; i++) {
        cout << numbers[i] << "\t";
    }
    cout << endl;
}
