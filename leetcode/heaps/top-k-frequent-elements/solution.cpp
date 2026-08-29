#include <vector>
#include <unordered_map>
#include <queue>

//==============================================================================
// LeetCode #347: Top K Frequent Elements
// Strategy: Linear Bucket Sort via Direct Frequency Inversion
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - Frequency map population takes O(N) linear time.
      - Inverting into frequency buckets takes O(U) where U <= N unique elements.
      - Collecting top-k elements scans at most N bucket slots and stops in O(K).
    - Auxiliary Space: O(N) auxiliary memory.
      - numsFreq hash map stores up to N distinct key-frequency pairs.
      - buckets vector allocates N + 1 slots containing U total elements.

    Algorithmic Invariants:
    1. Maximum Frequency Bounding:
       - No element can appear more than N times, bounding bucket array bounds to [0, N].
    2. Monotonic Frequency Scan:
       - Scanning buckets descending from index N guarantees elements with strictly 
         higher frequencies are aggregated before lower ones without comparison sorting.
*/
std::vector<int> topKFrequent(const std::vector<int>& nums, int k)
{
    std::unordered_map<int, int> numsFreq;
    numsFreq.reserve(nums.size());

    for (int val : nums)
    {
        numsFreq[val]++;
    }

    std::vector<std::vector<int>> buckets(nums.size() + 1);
    for (const auto& [val, freq] : numsFreq)
    {
        buckets[freq].push_back(val);
    }

    std::vector<int> topFreq;
    topFreq.reserve(static_cast<size_t>(k));

    for (size_t i = nums.size(); i > 0 && topFreq.size() < static_cast<size_t>(k); --i)
    {
        for (int val : buckets[i])
        {
            topFreq.push_back(val);
            if (topFreq.size() == static_cast<size_t>(k))
            {
                break;
            }
        }
    }

    return topFreq;
}

//==============================================================================
// LeetCode #347: Top K Frequent Elements
// Strategy: Frequency Hash Map with Bounded Min-Heap (Size K)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log K) where N = nums.size() and K = target count.
      - Frequency aggregation runs in O(N).
      - Ingesting U unique elements into bounded heap takes O(U log K).
    - Auxiliary Space: O(N + K) auxiliary heap memory.
      - Hash table stores U <= N unique key-value pairs.
      - Priority queue strictly maintains at most K elements.

    Algorithmic Invariants:
    1. Bounded K-Capacity Invariant:
       - minHeap contains the K highest-frequency pairs seen so far.
    2. Pair Comparator Ordering:
       - std::greater<std::pair<int, int>> orders by pair.first (frequency), ensuring 
         minHeap.top() always exposes the lowest frequency in the top-K working set.
*/
// std::vector<int> topKFrequentHeap(const std::vector<int>& nums, int k)
// {
//     std::unordered_map<int, int> numsFreq;
//     numsFreq.reserve(nums.size());

//     for (int val : nums)
//     {
//         numsFreq[val]++;
//     }

//     // Min-heap storing pair<frequency, value>
//     using FreqPair = std::pair<int, int>;
//     std::priority_queue<FreqPair, std::vector<FreqPair>, std::greater<FreqPair>> minHeap;

//     const size_t kLimit = static_cast<size_t>(k);

//     for (const auto& [val, freq] : numsFreq)
//     {
//         if (minHeap.size() < kLimit)
//         {
//             minHeap.emplace(freq, val);
//         }
//         else if (freq > minHeap.top().first)
//         {
//             minHeap.pop();
//             minHeap.emplace(freq, val);
//         }
//     }

//     std::vector<int> result;
//     result.reserve(kLimit);

//     while (!minHeap.empty())
//     {
//         result.push_back(minHeap.top().second);
//         minHeap.pop();
//     }

//     return result;
// }

//==============================================================================
// LeetCode #347: Top K Frequent Elements
// Strategy: Linear Bucket Sort via Direct Frequency Inversion
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - Frequency map population takes O(N) linear time.
      - Inverting into frequency buckets takes O(U) where U <= N unique elements.
      - Collecting top-k elements scans at most N bucket slots and stops in O(K).
    - Auxiliary Space: O(N) auxiliary memory.
      - numsFreq hash map stores up to N distinct key-frequency pairs.
      - buckets vector allocates N + 1 slots containing U total elements.

    Algorithmic Invariants:
    1. Maximum Frequency Bounding:
       - No element can appear more than N times, bounding bucket array bounds to [0, N].
    2. Monotonic Frequency Scan:
       - Scanning buckets descending from index N guarantees elements with strictly 
         higher frequencies are aggregated before lower ones without comparison sorting.
*/
// std::vector<int> topKFrequent(const std::vector<int> &nums, int k)
// {
//     // Find frequencies of all nums elements
//     std::unordered_map<int, int> numsFreq;
//     numsFreq.reserve(nums.size());

//     for (const int &val : nums)
//     {
//         numsFreq[val]++;
//     }

//     // Map out buckets where index = frequency count + element = value w/ that frequency count
//     std::vector<std::vector<int>> buckets(nums.size() + 1);
//     for (const auto &pair : numsFreq)
//     {
//         buckets[pair.second].push_back(pair.first);
//     }

//     std::vector<int> topFreq;
//     topFreq.reserve(k);

//     for (int i = buckets.size() - 1; i >= 0; i--)
//     {
//         if (buckets[i].size() > 0)
//         {
//             for (size_t j = 0; j < buckets[i].size(); j++)
//             {
//                 if (k-- > 0)
//                 {
//                     topFreq.push_back(buckets[i][j]);
//                 }
//             }
//         }
//     }

//     return topFreq;
// }