#include <vector>
#include <algorithm>
#include <queue>

//==============================================================================
// HackerRank: Find the Running Median
// Strategy: Dual Priority Queue (Max-Heap / Min-Heap) Dynamic Stream Balancing
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log N) where N = a.size().
      - Each incoming value is pushed and balanced across heaps in O(log N) time.
      - Median queries evaluate via O(1) top() lookups.
    - Auxiliary Space: O(N) auxiliary heap memory.
      - lowerHeap and upperHeap store a combined total of N elements across the stream.

    Mathematical Invariants:
    1. Stream Value Partition Invariant:
       - lowerHeap (max-heap) holds elements in the lower half (<= median).
       - upperHeap (min-heap) holds elements in the upper half (>= median).
       - Invariant maintained: max(lowerHeap) <= min(upperHeap).
    2. Dynamic Size Invariant:
       - Preserves |lowerHeap| - |upperHeap| in {0, 1} on every stream element.
       - If total stream count is odd, median = lowerHeap.top().
       - If total stream count is even, median = (lowerHeap.top() + upperHeap.top()) / 2.0.
*/
std::vector<double> runningMedian(const std::vector<int> &a)
{
    std::priority_queue<int> lowerHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> upperHeap;
    std::vector<double> medians;
    medians.reserve(a.size());

    for (size_t i = 0; i < a.size(); i++)
    {
        // Access and sort incoming element into either queue
        if (lowerHeap.empty() || a[i] <= lowerHeap.top())
        {
            lowerHeap.push(a[i]);
        }
        else
        {
            upperHeap.push(a[i]);
        }

        // Adjust queues if size discrepancy
        if (lowerHeap.size() > upperHeap.size() + 1)
        {
            upperHeap.push(lowerHeap.top());
            lowerHeap.pop();
        }
        else if (upperHeap.size() > lowerHeap.size())
        {
            lowerHeap.push(upperHeap.top());
            upperHeap.pop();
        }

        // Now determine and push median
        size_t heapSize = lowerHeap.size() + upperHeap.size();
        if (heapSize % 2 == 1)
        {
            medians.push_back(static_cast<double>(lowerHeap.top()));
        }
        else
        {
            double median = (lowerHeap.top() + upperHeap.top()) / 2.0;
            medians.push_back(median);
        }
    }

    return medians;
}

//==============================================================================
// HackerRank: Find the Running Median
// Implementation: Repeated Vector Insertion & Full Sorting (O(N^2 log N) - TLE)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N^2 log N) where N = a.size().
      - For each iteration k from 1 to N, std::sort runs in O(k log k).
      - Total operations: Sum_{k=1}^N (k log k) = O(N^2 log N), timing out on large streams.
    - Auxiliary Space: O(N) auxiliary heap memory.
      - Stores up to N integers in dynamic vector buffer.

    Defects & Bottlenecks:
    1. Redundant Sorting:
       - Fails to leverage previously sorted data, resorting from scratch on every stream insertion.
    2. Missing Dynamic Heap Invariants:
       - Does not utilize dual-heap streaming balance to achieve O(log N) insertion.
*/
// std::vector<double> runningMedian(const std::vector<int> &a)
// {
//     const size_t aSize = a.size();

//     std::vector<int> minHeap;
//     minHeap.reserve(aSize);
//     std::vector<double> medians;
//     medians.reserve(aSize);

//     for (size_t i = 0; i < aSize; i++)
//     {
//         minHeap.push_back(a[i]);
//         std::sort(minHeap.begin(), minHeap.end());

//         size_t heapSize = minHeap.size();
//         if (heapSize == 1)
//         {
//             medians.push_back(static_cast<double>(minHeap[0]));
//         }
//         else
//         {
//             if (heapSize % 2 == 1)
//             {
//                 int pos = static_cast<int>(heapSize) / 2;
//                 medians.push_back(static_cast<double>(minHeap[pos]));
//             }
//             else
//             {
//                 int pos = static_cast<int>(heapSize) / 2;
//                 double newMedian = (minHeap[pos] + minHeap[pos - 1]) / 2.0;
//                 medians.push_back(newMedian);
//             }
//         }
//     }

//     return medians;
// }