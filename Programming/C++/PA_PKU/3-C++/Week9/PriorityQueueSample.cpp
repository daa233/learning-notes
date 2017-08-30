/**
 * @file: PriorityQueueSample.cpp
 * @description: STL 中 priority_queue 的用法示例
 * @input:
 * @output:
 *
 * @author: Du Ang
 * @date: Aug. 30th, 2017
 */

#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char const *argv[]) {
    priority_queue<double> priorities;
    priorities.push(3.2);
    priorities.push(9.8);
    priorities.push(5.4);
    while (!priorities.empty()) {
        cout << priorities.top() << " ";
        priorities.pop();
    }
    cout << endl;
    return 0;
}
