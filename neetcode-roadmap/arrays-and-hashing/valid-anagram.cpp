#include <string>
#include <unordered_map>
#include <array>

//==============================================================================
// LeetCode #242: Valid Anagram
// Strategy: Fixed 26-Slot L1 Cache Stack Table with Net Frequency Tracking
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = s.length().
      - Single simultaneous traversal across s and t.
      - Final constant-time scan of 26 array elements.
    - Auxiliary Space: O(1) stack memory (104 bytes, zero heap allocations).

    Algorithmic & Hardware Invariants:
    1. Zero Dynamic Allocation:
       - std::array<int, 26> resides completely on the thread stack, eliminating
         all heap allocations and heap fragmentation.
    2. L1 Cache Contiguity:
       - 104 contiguous bytes guarantees all lookups and mutations hit L1 cache lines.
    3. Direct Offset Indexing:
       - Array lookup via (c - 'a') avoids hash function computation and bucket walking.
*/
bool isAnagram(const std::string& s, const std::string& t)
{
    if (s.length() != t.length())
    {
        return false;
    }

    std::array<int, 26> charFreq{};

    const size_t len = s.length();
    for (size_t i = 0; i < len; ++i)
    {
        ++charFreq[static_cast<unsigned char>(s[i]) - 'a'];
        --charFreq[static_cast<unsigned char>(t[i]) - 'a'];
    }

    for (int count : charFreq)
    {
        if (count != 0)
        {
            return false;
        }
    }

    return true;
}

// bool isAnagram(const std::string &s, const std::string &t)
// {
//     if (s.length() != t.length())
//     {
//         return false;
//     }

//     std::unordered_map<char, int> lettersFreq;
//     lettersFreq.reserve(s.length());

//     for (char c1 : s)
//     {
//         ++lettersFreq[c1];
//     }

//     for (char c2 : t)
//     {
//         auto iter = lettersFreq.find(c2);
//         if (iter == lettersFreq.end())
//         {
//             return false;
//         }
//         else
//         {
//             --iter->second;
//             if (iter->second == 0)
//             {
//                 lettersFreq.erase(c2);
//             }
//         }
//     }

//     return true;
// }