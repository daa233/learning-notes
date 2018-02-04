/**
 * @file: ValueChangingAlgorithms.cpp
 * @description: STL 中 的变值算法示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 30th, 2017
 */

#include <iostream>
#include <vector>
#include <numeric>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std;

class CLessThen9 {
public:
    bool operator()(int n) {
        return n < 9;
    }
};

void outputSquare(int value) {
    cout << value * value << " ";
}

int calculateCube(int value) {
    return value * value * value;
}

int main(int argc, char const *argv[]) {
    const int SIZE = 10;
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int a2[] = {100, 2, 8, 1, 50, 3, 8, 9, 10, 2};
    vector<int> v(a1, a1 + SIZE);
    // output can print integers with a space behind each of them
    ostream_iterator<int> output(cout, " ");
    // shuffle the array
    random_shuffle(v.begin(), v.end());
    cout << "1) ";
    // output will print the content copied to it
    copy(v.begin(), v.end(), output);
    // 1) 7 1 4 6 8 9 5 2 3 10
    // v is bigger than SIZE
    copy(a2, a2 + SIZE, v.begin());
    cout << endl << "2) ";
    cout << count(v.begin(), v.end(), 8);
    // 2) 2
    cout << endl << "3) ";
    // count the elements that are less than 9
    cout << count_if(v.begin(), v.end(), CLessThen9());
    // 3) 6
    cout << endl << "4) ";
    cout << *(min_element(v.begin(), v.end()));
    // 4) 1
    cout << endl << "5) ";
    cout << *(max_element(v.begin(), v.end()));
    // 5) 100
    cout << endl << "6) ";
    cout << accumulate(v.begin(), v.end(), 0);
    // 6) 193
    cout << endl << "7) ";
    for_each(v.begin(), v.end(), outputSquare);
    // 7) 10000 4 64 1 2500 9 64 81 100 4
    vector<int> cubes(SIZE);
    transform(a1, a1 + SIZE, cubes.begin(), calculateCube);
    cout << endl << "8) ";
    copy(cubes.begin(), cubes.end(), output);
    // 8) 1 8 27 64 125 216 343 512 729 1000
    cout << endl;
    return 0;
}
