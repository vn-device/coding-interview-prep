//==============================================================================
// LeetCode #141 / NeetCode: Linked List Cycle Detection
// Strategy: Floyd's Tortoise and Hare (Two-Pointer Memory Address Convergence)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N is the number of nodes in the list.
      - Acyclic list: 'fast' hits nullptr in ceil(N / 2) steps.
      - Cyclic list: Once 'slow' enters a cycle of length C, 'fast' closes the
        gap by 1 node per iteration, guaranteeing pointer equality within <= C steps.
    - Auxiliary Space: O(1) strictly two pointer registers (slow, fast).
      - Avoids O(N) heap allocations from std::unordered_set<ListNode*>.

    Algorithmic & Hardware Invariants:
    1. Two-Step Lookahead Null Guard:
       - Checking (fast != nullptr && fast->next != nullptr) prior to advancing
         ensures fast->next->next never dereferences nullptr on empty, 1-node,
         or odd-length acyclic lists.
    2. Address Identity Equality (slow == fast):
       - Compares 64-bit virtual memory addresses directly rather than node
         payloads (val), eliminating false positives on duplicate values.
*/
struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

bool hasCycle(ListNode* head)
{
    ListNode* fast = head;
    ListNode* slow = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;

        if (fast == slow)
        {
            return true;
        }
    }

    return false;
}

// bool hasCycle(ListNode* head)
// {
//     ListNode* curr = head;
//     int mask = 0;

//     while (curr != nullptr)
//     {
//         mask ^= curr->val;

//         if (mask == 0)
//         {
//             return true;
//         }

//         curr = curr->next;
//     }

//     return false;
// }

// bool hasCycle(ListNode* head)
// {
//     ListNode* fast = head;
//     ListNode* slow = head;

//     while (fast != nullptr && slow != nullptr)
//     {
//         fast = fast->next;
//         if (fast->next == nullptr)
//         {
//             return false;
//         }
//         fast = fast->next;

//         slow = slow->next;

//         if (fast->val == slow->val)
//         {
//             return true;
//         }
//     }

//     return false;
// }