#include <queue>

//==============================================================================
// LeetCode #295: Find Median from Data Stream
// Strategy: Dual Priority Queue (Max-Heap / Min-Heap) Dynamic Stream Balancing
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - addNum(): O(log N) where N is the total number of inserted stream elements.
        - Heap insertion and dynamic rebalancing each take O(log N) worst-case.
      - findMedian(): O(1) direct root inspection.
    - Auxiliary Space: O(N) auxiliary heap memory.
      - lowerHalf and upperHalf hold a combined total of N elements across the stream.

    Mathematical Invariants:
    1. Value Partition Invariant:
       - lowerHalf (max-heap) holds elements in the lower half (<= median).
       - upperHalf (min-heap) holds elements in the upper half (>= median).
       - Invariant maintained: max(lowerHalf) <= min(upperHalf).
    2. Dynamic Size Invariant:
       - Preserves |lowerHalf| - |upperHalf| in {0, 1} on every stream element.
       - If stream size is odd, median = lowerHalf.top().
       - If stream size is even, median = (lowerHalf.top() + upperHalf.top()) / 2.0.
*/
class MedianFinder
{
private:
    std::priority_queue<int> lowerHalf;                                       // Max-heap: holds smaller half
    std::priority_queue<int, std::vector<int>, std::greater<int>> upperHalf;  // Min-heap: holds larger half

public:
    MedianFinder() = default;

    void addNum(int num)
    {
        // 1. Value routing invariant
        if (lowerHalf.empty() || num <= lowerHalf.top())
        {
            lowerHalf.push(num);
        }
        else
        {
            upperHalf.push(num);
        }

        // 2. Dynamic size rebalancing invariant (|lowerHalf| - |upperHalf| in {0, 1})
        if (lowerHalf.size() > upperHalf.size() + 1)
        {
            upperHalf.push(lowerHalf.top());
            lowerHalf.pop();
        }
        else if (upperHalf.size() > lowerHalf.size())
        {
            lowerHalf.push(upperHalf.top());
            upperHalf.pop();
        }
    }

    double findMedian() const
    {
        if (lowerHalf.size() == upperHalf.size())
        {
            return (static_cast<double>(lowerHalf.top()) + upperHalf.top()) / 2.0;
        }

        return static_cast<double>(lowerHalf.top());
    }
};

//==============================================================================
// LeetCode #295: Find Median from Data Stream
// Strategy: Dual Priority Queue (Max-Heap / Min-Heap) with Explicit Size Tracking
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - addNum(): O(log N) where N is the total number of ingested stream elements.
        - Pushes to either lowerHalf or upperHalf in O(log N).
        - Dynamic balancing transfers at most one element in O(log N).
      - findMedian(): O(1) direct root lookup and scalar arithmetic.
    - Auxiliary Space: O(N) auxiliary heap memory.
      - lowerHalf and upperHalf store a combined total of N elements across the stream.

    Algorithmic Invariants & State Design:
    1. Value Partition Invariant:
       - lowerHalf (max-heap) retains elements <= median.
       - upperHalf (min-heap) retains elements >= median.
       - Invariant maintained: max(lowerHalf) <= min(upperHalf).
    2. Dynamic Size Invariant:
       - Maintains |lowerHalf| - |upperHalf| in {0, 1}.
       - Explicit heapSize member updates on each insertion to determine odd/even median parity.
*/
class MedianFinder
{
private:
    size_t heapSize;
    std::priority_queue<int> lowerHalf;
    std::priority_queue<int, std::vector<int>, std::greater<int>> upperHalf;

public:
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        if (lowerHalf.empty() || num <= lowerHalf.top())
        {
            lowerHalf.push(num);
        }
        else
        {
            upperHalf.push(num);
        }

        if (lowerHalf.size() > upperHalf.size() + 1)
        {
            upperHalf.push(lowerHalf.top());
            lowerHalf.pop();
        }
        else if (upperHalf.size() > lowerHalf.size())
        {
            lowerHalf.push(upperHalf.top());
            upperHalf.pop();
        }

        heapSize = lowerHalf.size() + upperHalf.size();
    }

    double findMedian()
    {
        if (heapSize % 2 == 1)
        {
            return static_cast<double>(lowerHalf.top());
        }
        else
        {
            double result = (lowerHalf.top() + upperHalf.top()) / 2.0;
            return result;
        }
    }
};