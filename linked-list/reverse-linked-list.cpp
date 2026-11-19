//==============================================================================
// LeetCode #206 / NeetCode: Reverse Linked List
// Strategy: In-Place Iterative Three-Pointer Rewiring (O(1) Auxiliary Space)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N is the number of nodes in the list.
      - Single linear traversal visiting each node once with O(1) pointer writes.
    - Auxiliary Space: O(1) strictly three pointer variables in CPU registers.
      - Eliminates O(N) call-stack frames from recursion and O(N) heap buffers.

    Algorithmic & Hardware Invariants:
    1. Zero Memory Allocation:
       - Mutates existing node 'next' links directly in-place without constructing
         or destroying heap nodes.
    2. Forward Link Preservation:
       - Caching curr->next prior to overwriting curr->next = prev prevents
         orphaning the unvisited suffix of the linked list.
    3. Termination State:
       - Loop terminates when curr == nullptr; prev holds the new list head.
*/
struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* reverseList(ListNode* head)
{
    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr != nullptr)
    {
        // Save the forward link before overwriting curr->next
        ListNode* nextTemp = curr->next;

        // Reverse the link to point backward to prev
        curr->next = prev;

        // Advance both prev and curr one step forward
        prev = curr;
        curr = nextTemp;
    }

    // When curr reaches nullptr, prev sits on the new head (former tail)
    return prev;
}