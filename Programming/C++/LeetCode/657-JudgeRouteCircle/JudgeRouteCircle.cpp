/**
 * LeetCode Problems 657. Judge Route Circle
 *
 * @file: JudgeRouteCircle.cpp
 * @description: Initially, there is a Robot at position (0, 0). Given a sequence of its moves,
                judge if this robot makes a circle, which means it moves back to the original place.
                The move sequence is represented by a string. And each move is represent by a
                character. The valid robot moves are R (Right), L (Left), U (Up) and D (down).
                The output should be true or false representing whether the robot makes a circle.
 * @sample_input:
    Case 1:
        "UD"
    Case 2:
        "LL"
 * @sample_output:
    Case 1:
        true
    Case 2:
        false
 *
 * @author: Du Ang
 * @date: Sep. 6th, 2017
 */

#include <iostream>

using namespace std;

class Solution {
public:
    bool judgeCircle(string moves) {
        int direction[2] = {0};
        for (int i = 0; i < moves.size(); i++) {
            switch (moves[i]) {
                case 'U':
                    direction[0]++;
                    break;
                case 'D':
                    direction[0]--;
                    break;
                case 'L':
                    direction[1]++;
                    break;
                case 'R':
                    direction[1]--;
                    break;
                default:
                    break;
            }
        }
        if (direction[0] == 0 && direction[1] == 0) {
            return true;
        } else {
            return false;
        }
    }
};

int main(int argc, char const *argv[]) {
    string moves;
    cin >> moves;
    Solution s;
    cout << (s.judgeCircle(moves) ? "true" : "false") << endl;
    return 0;
}
