/** 
 * @problem: 2. Add Two Numbers
 * @file: add-two-numbers.cpp
 * @url: https://leetcode-cn.com/problems/add-two-numbers
 * @description: 
 * 
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order and each of their
 * nodes contain a single digit. Add the two numbers and return it as a
 * linked list.
 * You may assume the two numbers do not contain any leading zero, except
 * the number 0 itself.
 * Example:
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 * Explanation: 342 + 465 = 807.
 * 
 * @author: Du Ang
 * @date: Mar 28, 2019
 */

#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution1 {
   public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *result = new ListNode(0);
        ListNode *pl1 = l1, *pl2 = l2, *pr = result;
        int sum = 0, carry = 0;
        while (pl1 != NULL or pl2 != NULL) {
            sum = 0;
            if (pl1 != NULL) {
                sum += pl1->val;
                pl1 = pl1->next;
            }
            if (pl2 != NULL) {
                sum += pl2->val;
                pl2 = pl2->next;
            }
            sum += carry;
            pr->val = sum % 10;
            carry = sum / 10;
            if (pl1 == NULL && pl2 == NULL) {
                if (carry > 0) {
                    pr->next = new ListNode(carry);
                }
            } else {
                pr->next = new ListNode(0);
                pr = pr->next;
            }
        }
        return result;
    }
};

class Solution {
   public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode *pl1 = l1, *pl2 = l2;
        int sum = 0, carry = 0;
        while (pl2->next != NULL) {
            sum = pl1->val + pl2->val + carry;
            carry = sum / 10;
            pl1->val = sum % 10;
            if (pl1->next == NULL) {
                pl1->next = new ListNode(0);
            }
            pl1 = pl1->next;
            pl2 = pl2->next;
        }

        sum = pl1->val + pl2->val + carry;
        carry = sum / 10;
        pl1->val = sum % 10;
        
        while (carry > 0) {
            if (pl1->next == NULL) {
                pl1->next = new ListNode(carry);
                break;
            } else {
                pl1 = pl1->next;
                sum = pl1->val + carry;
                carry = sum / 10;
                pl1->val = sum % 10;
            }
        }
        return l1;
    }
};

ListNode *create_list(vector<int> v)
{
    if (v.size() > 0) {
        ListNode *head = new ListNode(v[0]);
        ListNode *p = head;
        for (int i = 1; i < v.size(); i++) {
            p->next = new ListNode(v[i]);
            p = p->next;
        }
        return head;
    } else {
        return NULL;
    }
    
}

void print_list(ListNode *head)
{
    ListNode *p = head;
    while (p != NULL) {
        cout << p->val; 
        if (p->next == NULL) {
            cout << endl;
        } else {
            cout << " -> ";
        }
        p = p->next;
    }
}

void destruct_list(ListNode *head)
{
    ListNode *p = head;
    while (head != NULL) {
        head = head->next;
        delete p;
        p = head;
    }
}

void test(Solution s, vector<int> v1, vector<int> v2)
{
    ListNode *l1 = create_list(v1), *l2 = create_list(v2);
    cout << "Input:" << endl;
    print_list(l1);
    print_list(l2);
    ListNode *result = s.addTwoNumbers(l1, l2);
    cout << "Output:" << endl;
    print_list(result);
    if (l1 == result) {
        destruct_list(l1);
    } else {
        destruct_list(l1);
        destruct_list(result);
    }
    destruct_list(l2);
}

int main(int argc, char *argv[])
{
    vector<int> v1 = {2, 4, 3}, v2 = {5, 6, 4}, v3 = {9, 8}, v4 = {1}, v5 = {9};
    Solution s;
    test(s, v1, v2);
    test(s, v1, v3);
    test(s, v3, v4);
    test(s, v3, v1);
    test(s, v4, v5);
    return 0;
}
