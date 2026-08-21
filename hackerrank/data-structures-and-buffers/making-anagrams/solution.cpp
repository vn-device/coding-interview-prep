#include <string>
#include <array>

//==============================================================================
// HackerRank: Making Anagrams
// Strategy: Symmetric Frequency Delta Balancing
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(|S1| + |S2|)
      - O(|S1|) to populate character frequencies from s1.
      - O(|S2|) to decrement character frequencies from s2.
      - O(Σ) = O(26) = O(1) constant sweep to aggregate absolute differences.
    - Auxiliary Space: O(1) (104 bytes on the call stack).
      - Utilizes a single 26-element std::array<int, 26> direct-mapped buffer.
      - Zero dynamic heap memory allocations.

    Core Mechanism:
    - Unlike one-way substring substitution (where 1 change replaces 1 surplus 
      and fills 1 deficit simultaneously), making strings anagrams via deletion 
      requires removing every unmatched surplus character from BOTH strings.
    - Total deletions = sum(|freq1[c] - freq2[c]|) across 'a' through 'z'.
*/
int makingAnagrams(const std::string& s1, const std::string& s2)
{
    // Single 26-element stack buffer tracking signed frequency balance
    std::array<int, 26> freqDelta{};

    for (const char c : s1)
    {
        freqDelta[c - 'a']++;
    }

    for (const char c : s2)
    {
        freqDelta[c - 'a']--;
    }

    int deletions = 0;
    for (int delta : freqDelta)
    {
        deletions += std::abs(delta);
    }

    return deletions;
}

//==============================================================================
// HackerRank: Making Anagrams
// Implementation: Dual Direct-Mapped Frequency Tables with Absolute Difference
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(|S1| + |S2|)
      - O(|S1|) linear scan to count character frequencies for s1.
      - O(|S2|) linear scan to count character frequencies for s2.
      - O(Σ) = O(26) = O(1) constant-time sweep across the alphabet to accumulate deletions.
    - Auxiliary Space: O(1) auxiliary stack space.
      - Allocates two 26-integer stack arrays (208 bytes total).
      - 0 dynamic heap allocations (no std::unordered_map node overhead).

    Implementation Notes & Evaluation:
    1. Direct-Offset Mapping:
       - Uses (c - 'a') scalar indexing into std::array<int, 26> to achieve O(1) 
         frequency tracking without hashing overhead.
    2. Absolute Imbalance Accumulation:
       - Since characters can only be deleted (not substituted), each unmatched 
         occurrence in s1 or s2 represents an invalid character that must be removed.
       - Sums std::abs(s1Freq[i] - s2Freq[i]) across all 26 alphabet buckets.
    3. Structural Optimization Opportunities:
       - Redundant Condition: The check `if (s1Freq[i] != s2Freq[i])` introduces 
         unnecessary conditional branch instructions; std::abs(0) naturally evaluates to 0.
       - Buffer Consolidation: Both s1Freq and s2Freq arrays can be unified into a 
         single signed delta array (increment for s1, decrement for s2) to halve stack usage.
*/
// int makingAnagrams(const std::string& s1, const std::string& s2)
// {
//     const size_t s1Len = s1.length();
//     const size_t s2Len = s2.length();

//     if (s1Len == 0 || s2Len == 0)
//     {
//         return (s1Len == 0) ? static_cast<int>(s2Len) : static_cast<int>(s1Len);
//     }

//     std::array<int, 26> s1Freq{};
//     std::array<int, 26> s2Freq{};

//     for (char c : s1)
//     {
//         s1Freq[c - 'a']++;
//     }

//     for (char c : s2)
//     {
//         s2Freq[c - 'a']++;
//     }

//     int deletions = 0;

//     for (int i = 0; i < 26; i++)
//     {
//         if (s1Freq[i] != s2Freq[i])
//         {
//             deletions += (std::abs(s1Freq[i] - s2Freq[i]));
//         }
//     }

//     return deletions;
// }