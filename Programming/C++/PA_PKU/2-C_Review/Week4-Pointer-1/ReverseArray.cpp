/**
 * @file: ReverseArray.cpp
 * @description: 倒置数组元素
 * @input: 1 2 3 4 5 6 7 8 9 0
 * @output: 9 8 7 6 5 4 3 2 1 0
 *
 * @author: Du Ang
 * @date: Aug. 3rd, 2017
 */

 #include <iostream>
 #include <iomanip>

 using namespace std;

 int main(int argc, char const *argv[]) {
     int a[10], *p = NULL, *q  = NULL, temp;
     for (p = a; p < a + 10; p++) {
         cin >> *p;
     }
     for (p = a, q = a + 9; p < q; p++, q--) {
         temp = *p;
         *p = *q;
         *q = temp;
     }
     for (p = a; p < a + 10; p++) {
         cout << setw(3) << *p;
     }
     cout << endl;
     return 0;
 }
