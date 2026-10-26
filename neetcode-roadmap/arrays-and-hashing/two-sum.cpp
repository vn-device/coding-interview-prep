#include <vector>
#include <unordered_map>

//==============================================================================
// LeetCode #1: Two Sum
// Strategy: Online Target Complement Hashing with Pre-Reserved Flat Bucket Table
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) average time single linear sweep across the stream.
      - Exactly one hash lookup per element.
      - At most one hash insertion per non-matching element.
    - Auxiliary Space: O(N) bounded auxiliary memory.
      - numsTable pre-reserves capacity for N elements to prevent mid-traversal
        rehashing and pointer-chain reallocations.

    Algorithmic & Hardware Invariants:
    1. Single-Pass Forward Search:
       - Looking up 'target - nums[i]' prior to storing 'nums[i]' prevents an
         element from matching with itself when '2 * nums[i] == target'.
    2. Zero Rehash Reallocations:
       - 'numsTable.reserve(len)' pre-allocates bucket storage up front, ensuring
         O(1) average insertions without triggering container expansion on the heap.
    3. Return Vector Pre-Sizing:
       - Direct brace return {iter->second, i} avoids intermediate vector allocations.
*/
std::vector<int> twoSum(const std::vector<int> &nums, int target)
{
    const int len = static_cast<int>(nums.size());
    std::unordered_map<int, int> numsTable;
    numsTable.reserve(len);

    for (int i = 0; i < len; ++i)
    {
        int diff = target - nums[i];
        auto iter = numsTable.find(diff);

        if (iter != numsTable.end())
        {
            return {iter->second, i};
        }

        numsTable[nums[i]] = i;
    }

    return {};
}