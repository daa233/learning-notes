/**
 *  标准模板库 STL-2 编程题＃6 priority_queue 练习题
 *
 * @file: PriorityQueue.cpp
 * @description: 我们定义一个正整数 a 比正整数 b 优先的含义是：
                    - a 的质因数数目（不包括自身）比 b 的质因数数目多；
                    - 当两者质因数数目相等时，数值较大者优先级高。
                现在给定一个容器，初始元素数目为 0，之后每次往里面添加 10 个元素，每次添加之后，要求输出优先级最高
                与最低的元素，并把该两元素从容器中删除。
 * @input: 第一行: num (添加元素次数，num <= 30)
        下面 10*num 行，每行一个正整数 n（n < 10000000).
 * @output: 每次输入 10 个整数后，输出容器中优先级最高与最低的元素，两者用空格间隔。
 * @sample_input:
    1
    10 7 66 4 5 30 91 100 8 9
 * @sample_output:
    66 5
 *
 * @author: Du Ang
 * @date: Sep. 1st, 2017
 */

#include <iostream>
#include <set>
#include <math.h>   // double sqrt(double x);

using namespace std;

bool isPrime(int x) {
    if (x < 2) {
        return false;
    } else if (x == 2) {
        return true;
    } else {
        for (int i = 2; i <= sqrt((double)x); i++) {
            if (x % i == 0) {
                return false;
            }
        }
    }
    return true;
}

int countPrimeFactors(int m) {
    set<int> primeFactors;
    if (m == 1 || m == 2) {
        return 0;
    } else if (isPrime(m)) {
        return 0;
    } else {
        for (int i = 2; i <= m; ) {
            if (m % i == 0 && isPrime(i)) {
                primeFactors.insert(i);
                m = m / i;
                if (m <= 2) {
                    break;
                }
            } else {
                i++;
            }
        }
        return primeFactors.size();
    }

}

// refered to http://www.cplusplus.com/reference/queue/priority_queue/priority_queue/
// if a is before (under, not prior to) b, MyCompare(a, b) returns true
class MyCompare {
public:
    bool operator()(const int &a, const int &b) const {
        int npa = countPrimeFactors(a);
        int npb = countPrimeFactors(b);
        if (npa < npb) {
            return true;
        } else if (npa == npb){
            return a < b;
        } else {
            return false;
        }
    }
};

int main(int argc, char const *argv[]) {
    int caseNum;
    const int SIZE = 10;
    set<int, MyCompare> pq;
    cin >> caseNum;
    set<int, MyCompare>::iterator b;
    set<int, MyCompare>::iterator e;
    while (caseNum--) {
        int n = SIZE;
        while (n--) {
            int x;
            cin >> x;
            pq.insert(x);
        }
        b = pq.begin();
        e = pq.end(); e--;
        cout << *e << " ";
        cout << *b << endl;
        pq.erase(e);
        pq.erase(b);
    }
    return 0;
}
