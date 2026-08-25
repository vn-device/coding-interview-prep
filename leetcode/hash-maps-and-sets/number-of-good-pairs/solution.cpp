#include <vector>
#include <array>

//==============================================================================
// LeetCode #1512: Number of Good Pairs
// Strategy: Online Frequency Hashing & Incremental Pair Aggregation
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - Single-pass linear scan across contiguous input buffer.
      - Zero post-processing reduction loops.
    - Auxiliary Space: O(1) auxiliary stack space.
      - std::array<uint8_t, 101> uses 101 bytes on the stack, fitting inside 2 cache lines.
      - Zero dynamic memory allocation overhead.

    Mathematical Invariants:
    1. Handshake / Combinatorial Invariant:
       - If an element has appeared `k` times previously, encountering it an additional 
         time creates exactly `k` new valid pairs with all prior instances:
         Sum_{k=0}^{C-1} k = C * (C - 1) / 2.
    2. Online Accumulation:
       - Incrementing `goodPairs += freq[val]++` maintains the running sum without 
         requiring multiplication or division instructions.
*/
int numIdenticalPairs(const std::vector<int>& nums)
{
    // Direct-mapped histogram for values in range [1, 100]
    std::array<uint8_t, 101> freq{};
    int goodPairs = 0;

    // Single-pass online pair accumulation
    for (int val : nums)
    {
        goodPairs += freq[val]++;
    }

    return goodPairs;
}

//==============================================================================
// LeetCode #1512: Number of Good Pairs
// Implementation: Direct Histogram with Two-Pass Combinatorial Reduction (0 ms)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - O(N) pass to populate frequency counts in numsFreq.
      - Fixed O(M) = O(100) = O(1) pass evaluating combinatorial pairs (freq * (freq - 1)) / 2.
    - Auxiliary Space: O(1) auxiliary stack space.
      - Allocates a fixed 100-element std::array<int, 100> (400 bytes) on the call stack.
      - 0 dynamic heap memory allocations.

    Implementation Notes:
    1. Direct-Offset Mapping:
       - Uses (val - 1) 0-indexed offset mapping matching constraint 1 <= nums[i] <= 100.
    2. Two-Pass Execution:
       - Populates the table first, then iterates over all 100 buckets to sum combinations.
       - Can be optimized to a single pass via online accumulation (`pairs += freq[val]++`).
*/
// int numIdenticalPairs(const std::vector<int> &nums)
// {
//     std::array<int, 100> numsFreq{};
//     for (const int &val : nums)
//     {
//         numsFreq[val - 1]++;
//     }

//     int pairs = 0;
//     for (int i = 0; i < 100; i++)
//     {
//         int freq = numsFreq[i];
//         if (freq > 1)
//         {
//             pairs += (freq * (freq - 1)) / 2;
//         }
//     }

//     return pairs;
// }