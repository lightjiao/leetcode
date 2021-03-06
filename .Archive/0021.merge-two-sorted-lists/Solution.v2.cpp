#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do
                           // this in one cpp file
#include "../ListNode.cpp"
#include "../catch.hpp"

#include "limits.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    /**
     * 递归的写法，会占用更多的栈内存
     */
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        ListNode* dummy   = new ListNode(0);
        ListNode* curNode = dummy;

        _merge(curNode, l1, l2);

        return dummy->next;
    }

    ListNode* _merge(ListNode* curNode, ListNode* l1, ListNode* l2)
    {
        if (l1 == NULL && l2 == NULL)
        {
            return curNode;
        }

        if (l1 != NULL && l2 == NULL)
        {
            curNode->next = l1;
            return curNode;
        }
        if (l1 == NULL && l2 != NULL)
        {
            curNode->next = l2;
            return curNode;
        }

        if (l1->val > l2->val)
        {
            curNode->next = l2;
            return _merge(l2, l1, l2->next);
        }
        else
        {
            curNode->next = l1;
            return _merge(l1, l1->next, l2);
        }
    }
};

void test(vector<int> l1, vector<int> l2, vector<int> expect)
{
    Solution  s;
    ListNode* head;

    head = s.mergeTwoLists(ListNode::Create(l1), ListNode::Create(l2));
    REQUIRE(ListNode::ToVector(head) == expect);
}

TEST_CASE("test")
{
    test({1, 2, 4}, {1, 3, 4}, {1, 1, 2, 3, 4, 4});
}
