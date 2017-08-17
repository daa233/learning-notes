/**
 * LeetCode Problems 2. Add Two Numbers
 *
 * @file: AddTwoNumbers.cpp
 * @description: You are given two non-empty linked lists representing two non-negative integers.
                The digits are stored in reverse order and each of their nodes contain a single
                digit. Add the two numbers and return it as a linked list.
                You may assume the two numbers do not contain any leading zero, except the number
                0 itself.
 * @input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * @output: 7 -> 0 -> 8
 *
 * @author: Du Ang
 * @date: Aug. 17th, 2017
 */

#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNubmers(ListNode* l1, ListNode* l2) {
        ListNode* p = new ListNode(0);
        bool carryFlag = false;
        int sum = l1->val + l2->val;
        if (sum >= 10) {
            p->val = sum % 10;
            carryFlag = true;
        } else {
            p->val = sum;
        }
        ListNode* temp = p;
        ListNode* templ1 = l1->next;
        ListNode* templ2 = l2->next;

        if (templ1 == NULL && templ2 == NULL) {
            // l1 and l2 each contains only one element
            int carry = (int)carryFlag;
            if (carry > 0) {
                temp->next = new ListNode((int)carryFlag);
            }
        } else {
            while (templ1 != NULL || templ2 != NULL) {
                temp->next = new ListNode(0);
                temp = temp->next;
                sum = 0;
                if (templ1 == NULL) {
                    sum = templ2->val + (int)carryFlag;
                    templ2 = templ2->next;
                } else if (templ2 == NULL) {
                    sum = templ1->val + (int)carryFlag;
                    templ1 = templ1->next;
                } else {
                    sum = templ1->val + templ2->val + (int)carryFlag;
                    templ1 = templ1->next;
                    templ2 = templ2->next;
                }

                if (sum >= 10) {
                    temp->val = sum % 10;
                    carryFlag = true;
                } else {
                    temp->val = sum;
                    carryFlag = false;
                }
            }
            // if the carry is not 0, create a new ListNode
            if (carryFlag) {
                temp->next = new ListNode((int)carryFlag);
            }
        }
        return p;
    }
};

void printList(ListNode* p) {
    ListNode* temp = p;
    while (temp->next != NULL) {
        std::cout << temp->val << " -> ";
        temp = temp->next;
    }
    std::cout << temp->val << std::endl;
}

ListNode* createList() {
    int n;
    std::cin >> n;
    if (n == -1) {
        std::cout << "Error: The linked list can't be empty!" << std::endl;
        exit(-1);
    } else {
        ListNode* p = new ListNode(n);
        ListNode* temp = p;
        while (true) {
            std::cin >> n;
            if (n == -1) {
                break;
            }
            temp->next = new ListNode(n);
            temp = temp->next;
        }
        return p;
    }
}

int main(int argc, char const *argv[]) {
    ListNode* p1 = createList();
    ListNode* p2 = createList();
    printList(p1);
    printList(p2);
    Solution s;
    ListNode *p = s.addTwoNubmers(p1, p2);
    printList(p);
    return 0;
}
