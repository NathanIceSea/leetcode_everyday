// 2->4->3=342 + 5->6->4=465 = 7->0->8=807

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// dummy_head.next 为个位
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy_head;
        ListNode *curr_digit = &dummy_head;
        int carry = 0;
        while (l1 != nullptr || l2 != nullptr) {
            int curr_l1_val = l1 != nullptr ? l1->val : 0;
            int curr_l2_val = l2 != nullptr ? l2->val : 0;
            int curr_dig_sum = carry + curr_l1_val + curr_l2_val;
            carry = curr_dig_sum / 10;
            curr_digit->next = new ListNode(curr_dig_sum % 10);
            curr_digit = curr_digit->next;
            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }
        if (carry != 0)
            curr_digit->next = new ListNode(carry);
        return dummy_head.next;
    }
};

int main() {
    ListNode* n1 = new ListNode(2, new ListNode(4, new ListNode(3)));
    ListNode *n2 = new ListNode(5, new ListNode(6, new ListNode(4)));
    Solution s;
    ListNode* ret = s.addTwoNumbers(n1, n2);
}