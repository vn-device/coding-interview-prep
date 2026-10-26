#include <vector>
#include <unordered_map>
#include <unordered_set>

//==============================================================================
// LeetCode #217: Contains Duplicate
// Strategy: Hash Set with Single-Probe Insertion Boolean Checking
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) average time single linear scan across the vector.
      - Exactly one hash probe per element using insert().second.
    - Auxiliary Space: O(N) bounded memory for the node-based hash set.

    Algorithmic & Hardware Invariants:
    1. Single-Probe Lookup & Emplacement:
       - Eliminates redundant find() + operator[] double-hashing.
    2. Zero Value Payload:
       - Uses std::unordered_set instead of std::unordered_map to eliminate 
         redundant frequency counter storage.
*/
bool containsDuplicate(const std::vector<int>& nums)
{
    std::unordered_set<int> seen;
    seen.reserve(nums.size());

    for (const int val : nums)
    {
        // insert() returns std::pair<iterator, bool>
        // If bool is false, the element already exists in the set
        if (!seen.insert(val).second)
        {
            return true;
        }
    }

    return false;
}

// bool containsDuplicate(const std::vector<int> &nums)
// {
//     std::unordered_map<int, int> numsFreq;
//     numsFreq.reserve(nums.size());

//     for (int val : nums)
//     {
//         auto iter = numsFreq.find(val);
//         if (iter == numsFreq.end())
//         {
//             ++numsFreq[val];
//         }
//         else
//         {
//             return true;
//         }
//     }

//     return false;
// }