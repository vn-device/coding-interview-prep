#include <vector>
#include <unordered_map>
#include <array>

//==============================================================================
// LeetCode #347 / NeetCode: Top K Frequent Elements
// Strategy: Bucket Sort Indexed by Frequency with Dynamic Horizon Allocation
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) linear sweep across all stages.
      - Counting frequencies takes O(N).
      - Populating buckets takes O(U) where U <= N is unique elements.
      - Draining buckets takes O(k) elements from the tail.
    - Auxiliary Space: O(N) bounded memory for frequency table and buckets.

    Algorithmic & Hardware Invariants:
    1. Dynamic Stack Protection:
       - Sizing freqBuckets to nums.size() + 1 eliminates hardcoded limits (10001)
         and prevents stack frame explosion (240 KB -> heap-allocated).
    2. Elimination of O(N log k) Heap Bottlenecks:
       - Uses direct array-indexed bucket distribution rather than std::priority_queue,
         avoiding pointer/node rebalancing overhead.
    3. Early Loop Termination:
       - Short-circuits immediately when result reaches size k, skipping empty buckets.
*/
std::vector<int> topKFrequent(const std::vector<int>& nums, int k)
{
    const size_t len = nums.size();
    std::unordered_map<int, int> numsFreq;
    numsFreq.reserve(len);

    int topFreq = 0;
    for (const int val : nums)
    {
        const int count = ++numsFreq[val];
        topFreq = std::max(topFreq, count);
    }

    // Dynamic bucket allocation indexed by frequency [1 ... len]
    std::vector<std::vector<int>> freqBuckets(topFreq + 1);
    for (const auto& pair : numsFreq)
    {
        freqBuckets[pair.second].push_back(pair.first);
    }

    std::vector<int> kFrequent;
    kFrequent.reserve(k);

    for (int i = topFreq; i >= 1; --i)
    {
        for (const int val : freqBuckets[i])
        {
            kFrequent.push_back(val);
            if (static_cast<int>(kFrequent.size()) == k)
            {
                return kFrequent;
            }
        }
    }

    return kFrequent;
}

// std::vector<int> topKFrequent(const std::vector<int> &nums, int k)
// {
//     std::unordered_map<int, int> numsFreq;
//     numsFreq.reserve(nums.size());
//     int topFreq = 0;

//     for (int val : nums)
//     {
//         ++numsFreq[val];
//         topFreq = std::max(topFreq, numsFreq[val]);
//     }

//     std::array<std::vector<int>, 10001> freqBuckets;
//     for (auto &iter : numsFreq)
//     {
//         freqBuckets[iter.second].push_back(iter.first);
//     }

//     std::vector<int> kFrequent;
//     kFrequent.reserve(k);

//     for (int i = topFreq; i >= 0; --i)
//     {
//         int bucketSize = static_cast<int>(freqBuckets[i].size());
//         int j = 0;

//         while (k > 0 && j < bucketSize)
//         {
//             kFrequent.push_back(freqBuckets[i][j]);
//             ++j;
//             --k;
//         }
//     }

//     return kFrequent;
// }