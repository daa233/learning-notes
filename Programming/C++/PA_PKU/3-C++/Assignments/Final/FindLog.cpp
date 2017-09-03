/**
 *  2017程序设计夏季学期练习题 编程题＃8 计算对数
 *
 * @file: FindLog.cpp
 * @description: 给定两个正整数 a（a>1)和 b。可以知道一定存在整数 x，使得 x <= log_a b < x + 1 或者
                a^x <= b < a^(x+1)。请计算 x。
 * @input: 两行，第一行是 a，第二行是 b。每个整数均不超过 100 位。
 * @output: 一行，即对应的 x。输入数据保证 x 不大于 20。
 * @sample_input:
    10000
    1000000000001
 * @sample_output:
    3
 *
 * @author: Du Ang
 * @date: Sep. 3rd, 2017
 */

#include <iostream>
#include <vector>
#include <cstdlib>      // for atoi()

using namespace std;

class BigInt {
private:
    vector<int> digit;
    bool sign;  // the sign digit, true for positive, false for negative
public:
    BigInt();
    BigInt(string s);
    BigInt(const BigInt &bi);
    ~BigInt();
    BigInt &operator=(const BigInt &bi);
    BigInt operator+(const BigInt &a);
    BigInt operator*(const BigInt &a);
    int compareWith(const BigInt &a);   // 1 for >, 0 for ==, -1 for <
};

BigInt::BigInt() : sign(true) {
    digit.clear();
}

BigInt::BigInt(string s) : sign(true) {
    digit.clear();
    for (int i = s.size() - 1; i >= 0; i--) {
        const char *tmp = (s.substr(i, 1)).c_str();
        int n = atoi(tmp);
        digit.push_back(n);
    }
}

BigInt::BigInt(const BigInt &bi) {
    digit = bi.digit;
    sign = bi.sign;
}

BigInt::~BigInt() {
    digit.clear();
}

BigInt &BigInt::operator=(const BigInt &bi) {
    digit.clear();
    digit = bi.digit;
    sign = bi.sign;
    return *this;
}


BigInt BigInt::operator+(const BigInt &a) {
    BigInt result;
    int i = 0;
    int carry = 0;
    int tempSum = 0;
    for (i = 0; i < digit.size() && i < a.digit.size(); i++) {
        tempSum = digit[i] + a.digit[i] + carry;
        if (tempSum >= 10) {
            result.digit.push_back(tempSum % 10);
            carry = 1;
        } else {
            result.digit.push_back(tempSum);
            carry = 0;
        }
    }
    if (i < digit.size()) { // *this has more digits
        for ( ; i < digit.size(); i++) {
            tempSum = digit[i] + carry;
            if (tempSum >= 10) {
                result.digit.push_back(tempSum % 10);
                carry = 1;
            } else {
                result.digit.push_back(tempSum);
                carry = 0;
            }
        }
    } else if (i < a.digit.size()) {    // a has more digits
        for ( ; i < a.digit.size(); i++) {
            tempSum = a.digit[i] + carry;
            if (tempSum >= 10) {
                result.digit.push_back(tempSum % 10);
                carry = 1;
            } else {
                result.digit.push_back(tempSum);
                carry = 0;
            }
        }
    } else {}   // *this and a has the same digits
    if (carry > 0) {
        result.digit.push_back(carry);
    }
    return result;
}

BigInt BigInt::operator*(const BigInt &a) {
    BigInt result;
    // for  one multiplicator is 1 or 0, return quickly
    if (digit.size() == 1) {
        if (digit[0] == 0) {
            result.digit.push_back(0);
            return result;
        } else if (digit[0] == 1) {
            result = a;
            return result;
        }
    }
    if (a.digit.size() == 1) {
        if (a.digit[0] == 0) {
            result.digit.push_back(0);
            return result;
        } else if (a.digit[0] == 1) {
            result = *this;
            return result;
        }
    }

    // for common cases
    int n = a.digit.size();
    result.digit.clear();
    result.digit.push_back(0);
    for (int i = 0; i < n; i++) {
        BigInt tempProduct; // for {digit[0]...digit[n]} * a.digit[i]
        int tempSingleDigitProduct = 0; // for digit[j] * a.digit[i]
        int carry = 0;
        for (int j = 0; j < digit.size(); j++) {
            tempSingleDigitProduct = digit[j] * a.digit[i] + carry;
            if (tempSingleDigitProduct >= 10) {
                tempProduct.digit.push_back(tempSingleDigitProduct % 10);
                carry = tempSingleDigitProduct / 10;
            } else {
                tempProduct.digit.push_back(tempSingleDigitProduct);
                carry = 0;
            }
        }
        if (carry > 0) {
            tempProduct.digit.push_back(carry);
        }
        // insert zeros to low-order for 10x, like 123 -> 1230
        for (int k = 0; k < i; k++) {
            if (tempProduct.digit.size() == 1 && tempProduct.digit[0] == 0) {
                continue;   // if tempProduct is 0
            }
            tempProduct.digit.insert(tempProduct.digit.begin(), 0);
        }
        result = result + tempProduct;
    }
    return result;
}

int BigInt::compareWith(const BigInt &a) {
    if (digit.size() > a.digit.size()) {
        return 1;
    } else if (digit.size() < a.digit.size()) {
        return -1;
    } else {    // same length
        for (int i = digit.size() - 1; i >= 0; i--) {
            if (digit[i] > a.digit[i]) {
                return 1;
                break;
            } else if (digit[i] < a.digit[i]) {
                return -1;
                break;
            } else {
                if (i == 0) {   // equal
                    return 0;
                } else {
                    continue;
                }
            }
        }
        exit(-1);
    }
}

int main(int argc, char const *argv[]) {
    string strA, strB;
    cin >> strA;
    cin >> strB;
    BigInt a(strA);
    BigInt b(strB);
    BigInt p = a;       // to store a^x
    int x = 0;
    int compareCode = p.compareWith(b);
    if (compareCode == 1) {
        x = 0;
        p = p * a;
    } else if (compareCode == 0) {
        x = 1;
        p = p * a;
    } else {
        x = 1;
        while (compareCode == -1 || compareCode == 0) {
            p = p * a;
            x++;
            compareCode = p.compareWith(b);
        }
        x--;
    }
    if (p.compareWith(b) == 1) {
        cout << x << endl;
    } else {
        cerr << "Something is wrong" << endl;
    }
    return 0;
}
