/**
 * 综合编程练习（1）编程题 #3：发票统计
 *
 * @file: InvoicesStatistics.cpp
 * @description: 有一个小型的报账系统，它有如下功能：
                （1）统计每个人所报发票的总钱数
                （2）统计每类发票的总钱数
                将此系统简化为如下：假设发票类别共有A、B、C三种;一共有三个人，ID分别为1、2、3。
 * @input: 系统输入包含三行，每行第一个数为人员ID（整型，1或2或3），第二个数为发票总张数(张数不超过100)，之后是多个发票类别（字符型，
            A或B或C）和相应发票金额（单进度浮点型,不超过1000.0）。
 * @output: 输出包含六行，前三行为每人（按ID由小到大输出）所报发票总钱数（保留两位小数），后三行为每类发票的总钱数（保留两位小数）。
 * 样例输入
    1 5 A 1.0 A 2.0 C 1.0 B 1.0 C 1
    3 3 B 1 C 2 C 1
    2 4 B 1 A 1 C 1 A 1
 * 样例输出
    1 6.00
    2 4.00
    3 4.00
    A 5.00
    B 3.00
    C 6.00
 *
 * @author: Du Ang
 * @date: Apr. 16th, 2017
 */

#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    float totalMoney[3] = {0};
    float totalInvoices[3] = {0};
    for (int i = 0; i < 3; i++) {
        int id, num; char type; float price;
        cin >> id >> num;
        for (int j = 0; j < num; j++) {
            cin >> type >> price;
            switch (type) {
                case 'A':
                    totalInvoices[0] += price;
                    break;
                case 'B':
                    totalInvoices[1] += price;
                    break;
                case 'C':
                    totalInvoices[2] += price;
                    break;
                default:
                    break;
            }
            totalMoney[id-1] += price;
        }
    }
    for (int i = 0; i < 3; i++) {
        cout << i+1 << " " << fixed << setprecision(2) << totalMoney[i] << endl;
    }
    cout << 'A' << " " << fixed << setprecision(2) << totalInvoices[0] << endl;
    cout << 'B' << " " << fixed << setprecision(2) << totalInvoices[1] << endl;
    cout << 'C' << " " << fixed << setprecision(2) << totalInvoices[2] << endl;
    return 0;
}
