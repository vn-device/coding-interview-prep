#include <vector>
#include <algorithm>
#include <set>

//==============================================================================
// LeetCode #480: Sliding Window Median
// Strategy: Dual Priority Queues (Max/Min Heap) with Hash-Based Lazy Deletion
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log K) where N = nums.size() and K is the sliding window size.
      - Inserting and erasing elements into the balanced heap pair takes amortized O(log K).
      - Lazy removal cleanup executes in amortized O(1) across stream operations.
    - Auxiliary Space: O(N) auxiliary heap memory.
      - Dual heaps and delayed hash map hold at most N total elements across execution.

    Algorithmic Invariants & State Design:
    1. Heap Balance Invariant:
       - Maintains lowerSize - upperSize in {0, 1} through dynamic rebalancing.
    2. Lazy Invalidation Invariant:
       - Outgoing elements from sliding window boundaries are marked in delayed map;
         they are popped only when they surface at the top of either heap.
    3. 64-Bit Float Promotion:
       - Casts heap root integers to double before addition, eliminating int32 overflow.
*/
class DualHeapWindow
{
private:
    std::priority_queue<int> lowerHalf;
    std::priority_queue<int, std::vector<int>, std::greater<int>> upperHalf;
    std::unordered_map<int, int> delayed;
    size_t k;
    size_t lowerSize = 0;
    size_t upperSize = 0;

    template <typename HeapType>
    void prune(HeapType& heap)
    {
        while (!heap.empty())
        {
            int num = heap.top();
            auto it = delayed.find(num);
            if (it != delayed.end())
            {
                if (--it->second == 0)
                {
                    delayed.erase(it);
                }
                heap.pop();
            }
            else
            {
                break;
            }
        }
    }

    void balance()
    {
        if (lowerSize > upperSize + 1)
        {
            upperHalf.push(lowerHalf.top());
            lowerHalf.pop();
            --lowerSize;
            ++upperSize;
            prune(lowerHalf);
        }
        else if (lowerSize < upperSize)
        {
            lowerHalf.push(upperHalf.top());
            upperHalf.pop();
            ++lowerSize;
            --upperSize;
            prune(upperHalf);
        }
    }

public:
    explicit DualHeapWindow(size_t windowSize)
        : k(windowSize)
    {
    }

    void insert(int num)
    {
        if (lowerHalf.empty() || num <= lowerHalf.top())
        {
            lowerHalf.push(num);
            ++lowerSize;
        }
        else
        {
            upperHalf.push(num);
            ++upperSize;
        }
        balance();
    }

    void erase(int num)
    {
        ++delayed[num];
        if (num <= lowerHalf.top())
        {
            --lowerSize;
            if (num == lowerHalf.top())
            {
                prune(lowerHalf);
            }
        }
        else
        {
            --upperSize;
            if (num == upperHalf.top())
            {
                prune(upperHalf);
            }
        }
        balance();
    }

    double getMedian()
    {
        if (k % 2 == 1)
        {
            return static_cast<double>(lowerHalf.top());
        }

        return (static_cast<double>(lowerHalf.top()) + upperHalf.top()) / 2.0;
    }
};

std::vector<double> medianSlidingWindow(const std::vector<int>& nums, int k)
{
    DualHeapWindow dh(static_cast<size_t>(k));
    for (int i = 0; i < k; ++i)
    {
        dh.insert(nums[i]);
    }

    std::vector<double> result;
    result.reserve(nums.size() - k + 1);
    result.push_back(dh.getMedian());

    for (size_t i = k; i < nums.size(); ++i)
    {
        dh.insert(nums[i]);
        dh.erase(nums[i - k]);
        result.push_back(dh.getMedian());
    }

    return result;
}

// std::vector<double> medianSlidingWindow(const std::vector<int>& nums, int k)
// {
//     std::multiset<int> window(nums.begin(), nums.begin() + k);
//     auto mid = std::next(window.begin(), k / 2);

//     std::vector<double> result;
//     result.reserve(nums.size() - k + 1);

//     auto computeMedian = [&]() -> double
//     {
//         if (k % 2 == 1)
//         {
//             return static_cast<double>(*mid);
//         }
//         return (static_cast<double>(*mid) + *std::prev(mid)) / 2.0;
//     };

//     result.push_back(computeMedian());

//     for (size_t i = k; i < nums.size(); ++i)
//     {
//         window.insert(nums[i]);
//         if (nums[i] < *mid)
//         {
//             --mid;
//         }

//         if (nums[i - k] <= *mid)
//         {
//             auto eraseIt = window.lower_bound(nums[i - k]);
//             if (eraseIt == mid)
//             {
//                 mid = std::next(mid);
//             }
//             window.erase(eraseIt);
//         }
//         else
//         {
//             window.erase(window.lower_bound(nums[i - k]));
//         }

//         result.push_back(computeMedian());
//     }

//     return result;
// }

//==============================================================================
// LeetCode #480: Sliding Window Median
// Strategy: Sorted Vector Window via Binary Search (std::lower_bound)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N * K) where N = nums.size() and K is the window size.
      - Initial window sort: O(K log K).
      - For each of the N - K sliding steps:
        - std::lower_bound binary search: O(log K).
        - std::vector::erase / insert memory shift: O(K).
        - Direct median calculation: O(1).
      - Total runtime: O(K log K + N * K).
    - Auxiliary Space: O(K) auxiliary buffer memory.
      - Holds strictly K contiguous elements in a flat vector buffer.

    Algorithmic Invariants & Hardware Advantages:
    1. Contiguous Cache Locality:
       - Operates on a single contiguous std::vector, avoiding node-allocation 
         overhead and pointer chasing present in tree-based structures.
    2. 64-Bit Float Promotion:
       - Uses (window[k / 2] + window[(k - 1) / 2]) / 2.0 with static_cast<double>,
         safely handling odd/even lengths and preventing 32-bit signed integer overflow.
*/
// std::vector<double> medianSlidingWindow(const std::vector<int>& nums, int k)
// {
//     std::vector<double> result;
//     result.reserve(nums.size() - k + 1);

//     // Initial sorted window of size K
//     std::vector<int> window(nums.begin(), nums.begin() + k);
//     std::sort(window.begin(), window.end());

//     auto computeMedian = [&]() -> double
//     {
//         // Cast to double / int64_t before addition to avoid 32-bit integer overflow
//         return (static_cast<double>(window[k / 2]) + window[(k - 1) / 2]) / 2.0;
//     };

//     result.push_back(computeMedian());

//     for (size_t i = k; i < nums.size(); ++i)
//     {
//         // 1. Remove outgoing element via binary search lookup
//         auto eraseIt = std::lower_bound(window.begin(), window.end(), nums[i - k]);
//         window.erase(eraseIt);

//         // 2. Insert incoming element at its sorted position
//         auto insertIt = std::lower_bound(window.begin(), window.end(), nums[i]);
//         window.insert(insertIt, nums[i]);

//         // 3. O(1) direct median calculation
//         result.push_back(computeMedian());
//     }

//     return result;
// }

//==============================================================================
// LeetCode #480: Sliding Window Median
// Implementation: Naive Window Vector Re-sort (Integer Overflow & TLE)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N * K log K) where N = nums.size() and K is the window size.
      - Allocates and copies K elements per sliding step: O(K).
      - Executes std::sort on the window buffer: O(K log K).
      - Repeated for N - K + 1 window iterations.
    - Auxiliary Space: O(K) auxiliary buffer memory.
      - window vector allocates dynamic capacity for K integers.

    Defects & Failure Modes:
    1. 32-Bit Signed Integer Overflow:
       - Evaluating (window[k / 2] + window[(k / 2) - 1]) overflows int32_t when elements 
         approach INT_MAX (e.g., [2147483647, 2147483647]), yielding UB and negative results.
    2. Redundant Ingestion & Sort Overhead:
       - Completely rebuilds and re-sorts the entire window buffer on every shift instead 
         of updating incrementally in O(log K).
*/
std::vector<double> medianSlidingWindow(const std::vector<int> &nums, int k)
{
    const size_t numsSize = nums.size();
    std::vector<double> result;
    result.reserve(numsSize);

    std::vector<int> window;
    window.reserve(k);

    for (size_t i = 0; i < numsSize - k + 1; i++)
    {
        size_t pos = i;
        for (int j = 0; j < k; j++)
        {
            window.push_back(nums[pos++]);
        }

        std::sort(window.begin(), window.end());
        if (k % 2 == 1)
        {
            result.push_back(static_cast<double>(window[k / 2]));
        }
        else
        {
            double median = (window[k / 2] + window[(k / 2) - 1]) / 2.0;
            result.push_back(median);
        }

        window.clear();
    }

    return result;
}