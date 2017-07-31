/** 习题课一：枚举、模拟与递归 编程题 #2
 * @file: DoublyRecurrence.cpp
 * @description: 双递归：F(x+1) = G(x) + 1; G(x+1) = F(x) + 1
                自然数奇数偶数的定义（递归的思想）：0是偶数；如果x是偶数，那么x+1是奇数；如果x是奇数，那么x+1是偶数。
                用双递归的思想判断一个数是否为偶数。
 * 样例输入
    第一组
    2
    第二组
    5
 * 样例输出
    第一组
    true
    第二组
    false
 *
 * @author: Du Ang
 * @date: Apr. 19th, 2017
 */

#include <iostream>

using namespace std;

bool isEven(int x);
bool isOdd(int x);

bool isOdd(int x)
{
    return ((x != 0) && isEven(x-1)); // x为0，则x一定不为奇数。如果x前面的数为偶数，则x为奇数；否则，x为偶数
}

bool isEven(int x)
{
    return ((x == 0) || isOdd(x-1));  // 如果x为0，或者x前面的数为奇数，则x为偶数；否则，x不是偶数
}

int main(int argc, char const *argv[]) {
    int x;
    cin >> x;
    if (isEven(x)) cout << "true" << endl;
    else cout << "false" << endl;
    return 0;
}
