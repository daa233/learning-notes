/**
 * @file: FindPrimeNumbers.cpp
 * @description: 输入正整数n（n>2），输出所有小于n的素数
 * @solution: 典型解决方法：循环（i从2至n），设置一个标识p = 0；循环（j从2至i-1)，如果i mod j为0，将标识p置1。
            最后，如果p为0，则i为素数。
              另个一思路——埃拉托斯特尼法：筛出2到n之间所有的合数。将数组所有元素设置为0；筛出所有合数，分别计算2，3，4，...，n-1
            多次自我相加的值；每次计算得到的结果都是一个合数，在数组中标记该数字被“筛掉”；最后根据标记输出没有被筛掉的数字。
              上个思路的优化：1. 不需要从2一直到n-1自我相加，只需要从2到n的开方就行了。 2. 如果一个数已经被标定过了，那么它的倍数
            就不需要再被标定了。
 *
 * @author: Du Ang
 * @date: Apr. 7th, 2017
 */

#include <iostream>
#include <cmath>    // 为了使用sqrt()函数

using namespace std;

int main(int argc, char *argv[])
{
    int n;
    cin >> n;
    int sum, a[n] = {0};
    for (int i = 2; i < sqrt((double)n); i++) {
        sum = i;
        if (a[sum] == 0) {
            while (sum < n) {
                sum = sum + i;
                if (sum < n) a[sum] = 1;
            }
        }
    }
    // 根据标志位，打印输出没有被筛掉的素数
    for (int i = 2; i < n; i++) {
        if (a[i] == 0) cout << i << " ";
    }
    cout << endl;
    return 0;
}
