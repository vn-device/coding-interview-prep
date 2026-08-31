#include <vector>
#include <queue>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//==============================================================================
// LeetCode #23: Merge k Sorted Lists
// Strategy: K-Way Stream Merge via Priority Queue with Custom Functor
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log K) where N is total node count across all lists,
      and K = lists.size() is the number of linked lists.
      - Heap initialization takes O(K log K) to push list heads.
      - Each of the N nodes is popped and pushed into the heap at most once in O(log K).
    - Auxiliary Space: O(K) auxiliary heap memory.
      - minHeap holds at most K node pointers simultaneously.
      - Rearranges input linked list nodes in-place via pointer splicing with O(1) extra nodes.

    Algorithmic Invariants:
    1. K-Candidate Boundary Invariant:
       - minHeap contains at most one node per list (the unmerged head of each list).
       - Because each list is sorted, min(minHeap) is guaranteed to be the global minimum 
         across all unmerged list nodes.
    2. Zero-Copy Pointer Splicing:
       - Re-links existing ListNode pointers using a stack-allocated dummy head, eliminating 
         heap allocations and memory leaks.
*/
struct CompareNode
{
    bool operator()(const ListNode *a, const ListNode *b) const
    {
        return a->val > b->val;
    }
};

ListNode *mergeKLists(const std::vector<ListNode *> &lists)
{
    std::priority_queue<ListNode *, std::vector<ListNode *>, CompareNode> minHeap;

    for (ListNode *node : lists)
    {
        if (node != nullptr)
        {
            minHeap.push(node);
        }
    }

    ListNode temp(0);
    ListNode *current = &temp;

    while (!minHeap.empty())
    {
        ListNode *node = minHeap.top();
        minHeap.pop();

        current->next = node;
        current = current->next;

        if (node->next != nullptr)
        {
            minHeap.push(node->next);
        }
    }

    current->next = nullptr;
    return temp.next;
}

//==============================================================================
// LeetCode #23: Merge k Sorted Lists
// Strategy: Value Min-Heap Ingestion with Stack Dummy-Head Construction
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log N) where N is the total node count across all lists.
      - Traverses every list node and pushes its scalar value into minHeap: O(N log N).
      - Extracts all N elements sequentially from minHeap: O(N log N).
    - Auxiliary Space: O(N) auxiliary heap memory.
      - minHeap stores all N node scalar values simultaneously.
      - Allocates N new ListNode instances on the heap.

    Algorithmic Improvements & Invariants:
    1. Null / Empty Safety Guard:
       - Checks minHeap.empty() to safely handle empty lists or vectors containing 
         only null pointers without triggering undefined behavior.
    2. Stack-Allocated Dummy Head Pattern:
       - Replaces manual dangling pointer arithmetic with a dummy sentinel node,
         ensuring robust O(1) tail pointer advancement and zero memory leaks.
    3. Trade-off Note:
       - While fully functional, this approach re-allocates memory and operates in 
         O(N log N) time, whereas a pointer-based K-way merge achieves O(N log K) 
         time and O(K) space.
*/
// ListNode *mergeKLists(const std::vector<ListNode *> &lists)
// {
//     std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
//     for (ListNode *node : lists)
//     {
//         ListNode *current = node;
//         while (current != nullptr)
//         {
//             minHeap.push(current->val);
//             current = current->next;
//         }
//     }

//     ListNode temp;
//     ListNode *current = &temp;

//     while (!minHeap.empty())
//     {
//         current->next = new ListNode(minHeap.top());
//         minHeap.pop();

//         current = current->next;
//     }

//     return temp.next;
// }

//==============================================================================
// LeetCode #23: Merge k Sorted Lists
// Implementation: Full Value Extraction & Node Re-allocation (Memory Leak / Crash)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log N) where N is the total node count across all lists.
      - Traverses every list node and pushes its scalar value into minHeap: O(N log N).
      - Pops all N elements sequentially from minHeap: O(N log N).
    - Auxiliary Space: O(N) auxiliary heap memory.
      - minHeap stores all N integers simultaneously.
      - Allocates N brand-new ListNode objects on the heap instead of splicing existing nodes.

    Defects & Failure Modes:
    1. Empty Stream Undefined Behavior:
       - If lists is empty or contains only nullptrs, minHeap remains empty. Accessing 
         minHeap.top() outside the loop triggers undefined behavior / segmentation fault.
    2. Broken Pointer Linking & Memory Leak:
       - The trailing current = new ListNode(minHeap.top()) overwrites the local pointer 
         variable rather than linking to current->next, causing an orphaned node and memory leak.
    3. Ignored Sorted List Preconditions:
       - Ingests all N elements into a flat heap instead of performing an O(N log K) 
         K-way stream merge that leverages the pre-sorted nature of individual lists.
*/
// ListNode *mergeKLists(const std::vector<ListNode *> &lists)
// {
//     // Iterate array to get all list node values
//     std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
//     for (ListNode *node : lists)
//     {
//         ListNode *current = node;
//         while (current != nullptr)
//         {
//             minHeap.push(current->val);
//             current = current->next;
//         }
//     }

//     // Iterate thru min heap to get values
//     ListNode *current = new ListNode();
//     ListNode *head = current;

//     while (minHeap.size() > 1)
//     {
//         current->val = minHeap.top();
//         current->next = new ListNode();
//         current = current->next;
//         minHeap.pop();
//     }

//     current = new ListNode(minHeap.top());

//     return head;
// }