/*
    2. Add Two Numbers (Medium)

    You are given two non-empty linked lists representing two non-negative integers. The digits 
    are stored in reverse order, and each of their nodes contains a single digit. Add the two
    and return the sum as a linked lisst.

    Example 1

    Input: l1 = [2,4,3], l2 = [5,6,4]
    Output: [7,0,8]
    Explanation: 342 + 465 = 807.
*/

#include <iostream>
#include <vector>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int val) : val(val), next(nullptr) {}
    ListNode(int val, ListNode *next) : val(val), next(next) {}
};

class LinkedList {
    public:
        ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
            ListNode *dummy = new ListNode(0);
            ListNode *current = dummy;
            int carry = 0;

            while (l1 != nullptr || l2 != nullptr || carry != 0) {
                int sum = carry;
                if (l1 != nullptr) {
                    sum += l1->val;
                    l1 = l1->next;
                }

                if (l2 != nullptr) {
                    sum += l2->val;
                    l2 = l2->next;
                }

                carry = sum / 10;
                current->next = new ListNode(sum % 10);
                current = current->next;
            }
            return dummy->next;
        } 

        ListNode* createLinkedList(const std::vector<int>& arr) {
            ListNode *dummy = new ListNode(0);
            ListNode *current = dummy;
            for (int num : arr) {
                current->next = new ListNode(num);
                current = current->next;
            }
            return dummy->next;
        }

        void printLinkedList(ListNode *head) {
            while (head != nullptr) {
                std::cout << head->val;
                if (head->next != nullptr) {
                    std::cout << " -> ";
                }
                head = head->next;
            }
            std::cout << std::endl;
        }
};

int main() {

    std::cout << "Add Two Numbers : ";
    LinkedList link;
    ListNode *l1 = link.createLinkedList({2, 4, 3});
    ListNode *l2 = link.createLinkedList({5, 6, 4});

    ListNode *result = link.addTwoNumbers(l1, l2);

    std::cout << "\nOutput: ";
    link.printLinkedList(result);

    delete l1;
    delete l2; 
    delete result;

    return 0;
}