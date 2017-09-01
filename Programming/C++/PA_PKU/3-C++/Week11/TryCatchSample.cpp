/**
 * @file: TryCatchSample.cpp
 * @description: 用 try、catch 处理异常
 * @input: 9 0
 * @output:
    before dividing.
    catch(int) -1
    finished
 *
 * @author: Du Ang
 * @date: Sep. 1st, 2017
 */

#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    double m, n;
    cin >> m >> n;
    try {
        cout << "before dividing." << endl;
        if (n == 0) {
            throw -1;
        } else {
            cout << m / n << endl;
        }
        cout << "after dividing" << endl;
    } catch (double d) {
        cout << "catch(double) " << d << endl;
    } catch (int e) {
        cout << "catch(int) " << e << endl;
    }
    cout << "finished" << endl;
    return 0;
}
