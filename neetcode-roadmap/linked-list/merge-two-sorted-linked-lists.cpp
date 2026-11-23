//==============================================================================
// LeetCode #21 / NeetCode: Merge Two Sorted Lists
// Strategy: Stack-Sentinel Dummy Node with In-Place Pointer Splicing (O(1) Space)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N + M) where N and M are the lengths of list1 and list2.
      - Visits nodes only up to min(N, M) comparisons; attaches remaining tail in O(1).
    - Auxiliary Space: O(1) strictly stack-resident sentinel and tail pointer.
      - Zero dynamic heap allocations (no 'new' calls) and zero memory leaks.

    Algorithmic & Hardware Invariants:
    1. Stack Sentinel Elimination of Null-Head Branching:
       - Declaring 'ListNode dummy' on the stack provides a valid initial 'tail'
         pointer, avoiding special-case checks for the first inserted node and
         requiring no cleanup upon return.
    2. Direct Node Splicing:
       - Mutates existing 'next' links directly without copying integer payloads
         or allocating duplicate ListNode structs.
    3. O(1) Tail Remainder Attachment:
       - When one list exhausts, the remaining sorted suffix is already internally
         linked and attaches via a single pointer assignment.
*/
struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
{
    // Stack-allocated sentinel node: avoids heap allocation and head == nullptr branching
    ListNode dummy;
    ListNode* tail = &dummy;

    while (list1 != nullptr && list2 != nullptr)
    {
        if (list1->val <= list2->val)
        {
            tail->next = list1;
            list1 = list1->next;
        }
        else
        {
            tail->next = list2;
            list2 = list2->next;
        }

        tail = tail->next;
    }

    // Attach the remaining non-empty sorted list in O(1) without looping
    tail->next = (list1 != nullptr) ? list1 : list2;

    return dummy.next;
}

ListNode* mergeTwoListsDeepCopy(const ListNode* list1, const ListNode* list2)
{
    ListNode dummy;
    ListNode* tail = &dummy;

    while (list1 != nullptr && list2 != nullptr)
    {
        if (list1->val <= list2->val)
        {
            tail->next = new ListNode(list1->val);
            list1 = list1->next;
        }
        else
        {
            tail->next = new ListNode(list2->val);
            list2 = list2->next;
        }

        tail = tail->next;
    }

    const ListNode* rem = (list1 != nullptr) ? list1 : list2;
    while (rem != nullptr)
    {
        tail->next = new ListNode(rem->val);
        tail = tail->next;
        rem = rem->next;
    }

    return dummy.next;
}

// ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
// {
//     ListNode *l1 = list1;
//     ListNode *l2 = list2;

//     while (l1 != nullptr && l2 != nullptr)
//     {
//         int val1 = l1->val;
//         int val2 = l2->val;

//         if (val1 < val2)
//         {
//             l1 = l1->next;
//         }
//         else if (val1 > val2)
//         {
//             l2 = l2->next;
//         }
//         else // if (val1 == val2)
//         {
//             l1 = l1->next;
//             l2 = l2->next;
//         }
//     }

//     while (l1 != nullptr)
//     {
//         int val1 = l1->val;
//         l1 = l1->next;
//     }

//     while (l2 != nullptr)
//     {
//         int val2 = l2->val;
//         l2 = l2->next;
//     }

//     return nullptr;
// }