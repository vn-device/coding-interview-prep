#include <vector>
#include <unordered_map>

//==============================================================================
// LeetCode #1: Two Sum
// Strategy: Single-Pass Online Hash Map Complement Lookup
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - Single linear scan across input buffer; terminates early upon first pair match.
      - Average O(1) hash table lookup and insertion per element.
    - Auxiliary Space: O(N) auxiliary heap memory.
      - std::unordered_map stores at most N - 1 entries prior to finding the complement.

    Mathematical Invariants:
    1. Complement Relation:
       - For every element x = nums[i], the unique matching value is y = target - x.
    2. Single-Pass Directed Invariant:
       - Querying the map before inserting nums[i] guarantees that any found match y 
         resides at index j < i, naturally eliminating duplicate/self-index collisions.
*/
std::vector<int> twoSum(std::vector<int>& nums, int target)
{
    std::unordered_map<int, int> numToIndex;
    numToIndex.reserve(nums.size());

    const int n = static_cast<int>(nums.size());
    for (int i = 0; i < n; ++i)
    {
        const int complement = target - nums[i];
        const auto it = numToIndex.find(complement);

        if (it != numToIndex.end())
        {
            return {it->second, i};
        }

        numToIndex[nums[i]] = i;
    }

    return {};
}

//==============================================================================
// LeetCode #1: Two Sum
// Implementation: Two-Pass Hash Map Complement Lookup (2 ms / Beats 72.46%)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size()[cite: 6].
      - Pass 1: O(N) to insert all elements and indices into elementDB[cite: 6].
      - Pass 2: O(N) average time performing find() operations[cite: 6].
    - Auxiliary Space: O(N) heap memory[cite: 6].
      - std::unordered_map stores up to N key-value pairs[cite: 6].
      - Stack allocation for 2-element indices buffer[cite: 6].

    Defects & Bottlenecks:
    1. Redundant Second Pass:
       - Traverses nums twice instead of querying prior seen elements online[cite: 6].
    2. Self-Collision Guard:
       - Requires explicit condition (pairIter->second != j) to prevent an element 
         from pairing with its own index[cite: 6].
*/
// std::vector<int> twoSum(std::vector<int> &nums, int target)
// {
//     std::unordered_map<int, int> elementDB;
//     std::vector<int> indices;
//     indices.reserve(2);

//     for (size_t i = 0; i < nums.size(); i++)
//     {
//         elementDB[nums[i]] = i;
//     }

//     for (size_t j = 0; j < nums.size(); j++)
//     {
//         int diff = target - nums[j];
//         auto pairIter = elementDB.find(diff);

//         if (pairIter != elementDB.end() && pairIter->second != j)
//         {
//             indices.push_back(j);
//             indices.push_back(pairIter->second);
//             break;
//         }
//     }

//     return indices;
// }