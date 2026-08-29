#include <vector>
#include <queue>
#include <algorithm>

//==============================================================================
// LeetCode #215: Kth Largest Element in an Array
// Strategy: Introselect In-Place Partitioning (std::nth_element)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) average time, O(N) worst-case.
      - Introselect partitions the array in-place around the (k - 1)-th pivot.
    - Auxiliary Space: O(1) auxiliary memory.
      - Rearranges the input buffer in-place with zero heap allocations.

    Algorithmic Invariants:
    1. Partial Partition Invariant:
       - After std::nth_element with std::greater<int> at index k - 1:
         all elements in [begin, begin + k - 1) are >= nums[k - 1],
         and all elements in (begin + k - 1, end) are <= nums[k - 1].
    2. Direct Element Access:
       - The element residing at nums[k - 1] is strictly the k-th largest element.
*/
int findKthLargest(const std::vector<int> &nums, int k)
{
    // // The k-th largest element corresponds to index (k - 1) in descending order
    // auto targetIt = nums.begin() + (k - 1);
    // std::nth_element(nums.begin(), targetIt, nums.end(), std::greater<int>());

    // return *targetIt;

    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    const size_t kLimit = static_cast<size_t>(k);

    for (int num : nums)
    {
        if (minHeap.size() < kLimit)
        {
            minHeap.push(num);
        }
        else if (num > minHeap.top())
        {
            minHeap.pop();
            minHeap.push(num);
        }
    }

    return minHeap.top();  
}

//==============================================================================
// LeetCode #215: Kth Largest Element in an Array
// Implementation: Full Max-Heap Ingestion & Sequential Pop (50 ms / Beats 19.46%)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log N + k log N) where N = nums.size().
      - Ingests all N elements into priority queue individually: O(N log N).
      - Executes k - 1 pop() operations: O(k log N).
    - Auxiliary Space: O(N) auxiliary heap memory.
      - std::priority_queue holds all N integers simultaneously.

    Defects & Bottlenecks:
    1. Unbounded Priority Queue Size:
       - Holds all N elements instead of bounding capacity to size K.
    2. Missing Selection Algorithm:
       - Misses in-place partitioning (Introselect via std::nth_element) to achieve O(N) time.
*/
// int findKthLargest(const std::vector<int> &nums, int k)
// {
//     std::priority_queue<int> maxElements;
//     for (size_t i = 0; i < nums.size(); i++)
//     {
//         maxElements.push(nums[i]);
//     }

//     for (int i = 0; i < k - 1; i++)
//     {
//         maxElements.pop();
//     }

//     return maxElements.top();
// }