#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>

//==============================================================================
// LeetCode #128 / NeetCode: Longest Consecutive Sequence
// Strategy: Global Hash Set with Strict Sequence-Head Verification
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) average linear time.
      - Inserting into numsSet takes O(N) amortized time.
      - Each number is visited at most twice across the entire execution:
        once when testing (num - 1), and once during consecutive chain expansion.
    - Auxiliary Space: O(N) bounded auxiliary memory.
      - Pre-allocating numsSet prevents dynamic rehashing mid-execution.

    Algorithmic & Hardware Invariants:
    1. Complete Universe Initialization:
       - The set must be fully populated before evaluating sequence roots
         to prevent false starters caused by arrival-order dependence.
    2. Sequence Root Invariant:
       - An element 'num' starts a streak IF AND ONLY IF (num - 1) is absent.
         This guarantees that every streak is scanned exactly once from its true head.
    3. Zero Mid-Traversal Rehashing:
       - numsSet.reserve(nums.size()) pre-allocates bucket capacity up front.
*/
int longestConsecutive(const std::vector<int>& nums)
{
    if (nums.empty())
    {
        return 0;
    }

    std::unordered_set<int> numsSet;
    numsSet.reserve(nums.size());

    for (const int num : nums)
    {
        numsSet.insert(num);
    }

    int longestStreak = 0;

    for (const int num : numsSet)
    {
        // Only initiate sequence traversal if 'num' is the absolute beginning of a chain
        if (numsSet.find(num - 1) == numsSet.end())
        {
            int currentNum = num;
            int currentStreak = 1;

            // Expand forward along the consecutive sequence
            while (numsSet.find(currentNum + 1) != numsSet.end())
            {
                ++currentNum;
                ++currentStreak;
            }

            longestStreak = std::max(longestStreak, currentStreak);
        }
    }

    return longestStreak;
}

// int longestConsecutive(const std::vector<int>& nums)
// {
//     if (nums.empty())
//     {
//         return 0;
//     }

//     const size_t len = nums.size();
//     std::set<int> numsSeen;
//     std::vector<int> starters;
//     starters.reserve(len);

//     for (size_t i = 0; i < len; ++i)
//     {
//         numsSeen.insert(nums[i]);
//         auto iter = numsSeen.find(nums[i] - 1);

//         if (iter == numsSeen.end())
//         {
//             starters.push_back(nums[i]);
//         }
//     }

//     int longest = 1;

//     for (int start : starters)
//     {
//         int count = 1;
//         int target = start + 1;
//         auto iter = numsSeen.find(target);

//         while (iter != numsSeen.end())
//         {
//             iter = numsSeen.find(++target);
//             ++count;
//         }

//         longest = std::max(longest, count);
//     }

//     return longest;
// }