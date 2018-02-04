/**
 * 感性认识计算机程序  编程题 #3：奇偶排序（2）
 *
 * @file: OddEvenSorting.cpp
 * @description: 与（1）一样，输入十个整数，将十个整数按升序排列输出，并且奇数在前，偶数在后。另一种方法实现。
 * 样例输入
    10 9 8 7 6 5 4 3 2 1
 * 样例输出
    1 3 5 7 9 2 4 6 8 10
 * @author: PKU
 * @date: copied on Apr. 3rd, 2017
 */

#include <iostream>
using namespace std;

int main() {
    int a[10];
    for (int i = 0; i < 10; i++) {
        cin >> a[i];
    }
    // 冒泡，不断比较相邻的两个数，如果顺序错了，那么就交换
    for (int i = 0; i < 9; i++) {
        for (int j = 1; j < 10 - i; j++) {
            // 与刚才的冒泡排序不同，我们不只是通过较数字的大小决定顺序
            // 如果左边的为偶数，右边的为奇数，那么顺序也需要颠倒
            bool leftIsEven = a[j - 1] % 2 == 0;
            bool rightIsEven = a[j] % 2 == 0;
            if ((leftIsEven && !rightIsEven) ||
                (leftIsEven == rightIsEven && a[j - 1] > a[j])) {
                int temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
        }
    }
    for (int i = 0; i < 10; i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
    
    return 0;
}
