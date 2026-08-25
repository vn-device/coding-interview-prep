#include <vector>
#include <unordered_map>
#include <array>

//==============================================================================
// LeetCode #2006: Count Number of Pairs With Absolute Difference K
// Strategy: Direct-Mapped Histogram with Online Bidirectional Complement Accumulation
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - Single linear pass processing each element in O(1) deterministic time.
    - Auxiliary Space: O(1) auxiliary stack space.
      - std::array<uint8_t, 101> uses 101 bytes on the stack with 0 heap allocations.

    Mathematical Invariants:
    1. Absolute Difference Relation:
       - |nums[i] - nums[j]| = k implies nums[i] = nums[j] - k or nums[i] = nums[j] + k.
    2. Online Prefix Lookup:
       - Querying both complements (val - k and val + k) among previously seen elements 
         guarantees that every ordered pair (i, j) with i < j is counted exactly once.
*/
int countKDifference(std::vector<int>& nums, int k)
{
    // Direct-mapped histogram for value range [1, 100]
    std::array<uint8_t, 101> freq{};
    int pairs = 0;

    for (int val : nums)
    {
        // Query prior occurrences of complements within bounds
        if (val - k >= 1)
        {
            pairs += freq[val - k];
        }
        if (val + k <= 100)
        {
            pairs += freq[val + k];
        }

        freq[val]++;
    }

    return pairs;
}

//==============================================================================
// LeetCode #2006: Count Number of Pairs With Absolute Difference K
// Implementation: Two-Pass Hash Map with Redundant Subscript Lookup (7 ms)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - Pass 1: O(N) to populate element frequencies in numsFreq.
      - Pass 2: O(N) searching for target complement (val + k).
      - Hash table lookup and insertion take O(1) amortized time.
    - Auxiliary Space: O(N) auxiliary heap memory.
      - std::unordered_map allocates dynamically on the heap for up to N elements.

    Defects & Bottlenecks:
    1. Redundant Map Lookups:
       - Calls find(target) and then queries operator[](target), executing two bucket hashes.
    2. Dynamic Memory Overhead:
       - Uses std::unordered_map instead of exploiting the tight value bounds (nums[i] <= 100).
*/
// int countKDifference(std::vector<int> &nums, int k)
// {
//     const int n = static_cast<int>(nums.size());
//     if (n <= 1 || k < 0)
//     {
//         return 0;
//     }

//     int pairs = 0;
//     std::unordered_map<int, int> numsFreq;
//     numsFreq.reserve(n);

//     for (const int &val : nums)
//     {
//         numsFreq[val]++;
//     }

//     for (const int &val : nums)
//     {
//         int target = val + k;
//         auto iter = numsFreq.find(target);

//         if (iter != numsFreq.end())
//         {
//             pairs += numsFreq[target];
//         }
//     }

//     return pairs;
// }