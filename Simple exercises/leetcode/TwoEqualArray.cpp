#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *middleNode(ListNode *head)
{
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast)
    {
        if(fast->next) fast = fast->next->next;
        else fast = fast->next;
        slow = slow->next;
    }
    return slow;
}

int main()
{
    ListNode *head = new ListNode(1);
    ListNode *cur = head;
    for (int i = 2; i < 6; i++)
    {
        cur->next = new ListNode(i);
        cur = cur->next;
    }
    ListNode *mid = middleNode(head);
    while (mid)
    {
        cout << mid->val << " ";
        mid = mid->next;
    }
    return 0;
}

auto init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();