#include <string>
#include <array>
#include <cmath>

//==============================================================================
// LeetCode #409: Longest Palindrome
// Strategy: Branchless ASCII Frequency Histogram & Bitwise Parity Accumulation
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N)
      - O(N) linear scan across contiguous string buffer.
      - O(1) sweep across 128-byte ASCII array.
    - Auxiliary Space: O(1) (128 integers on the call stack).
      - Zero heap allocations; maximum L1 data cache throughput.

    Mathematical Invariants:
    1. Palindromic Symmetry Invariant:
       - Every even count of identical characters can be split evenly across outer wings.
       - Any odd count `c` provides `c - 1` characters for the outer wings.
    2. Branchless Even Component Extraction:
       - Clearing the least significant bit (`count & ~1`) instantly isolates the 
         maximum even portion of any integer without conditional branching.
    3. Center Singleton Invariant:
       - A palindrome can hold at most one unmatched singleton in its exact center.
       - If `maxLen < s.length()`, at least one odd character was discarded, 
         allowing `maxLen + 1`.
*/
int longestPalindrome(const std::string& s)
{
    const size_t n = s.length();
    if (n <= 1)
    {
        return static_cast<int>(n);
    }

    // Direct ASCII table to avoid character range branching
    std::array<int, 128> freq{};
    for (unsigned char c : s)
    {
        freq[c]++;
    }

    int maxLen = 0;
    for (int count : freq)
    {
        // Extract largest even component branchlessly: count & ~1
        maxLen += (count & ~1);
    }

    // If maxLen < n, at least one odd character existed to serve as the center
    return (maxLen < static_cast<int>(n)) ? maxLen + 1 : maxLen;
}

//==============================================================================
// LeetCode #409: Longest Palindrome
// Implementation: Dual Direct-Mapped Stack Arrays (0 ms, Beats 100.00%)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = s.length().
      - Single-pass frequency population in O(N).
      - Fixed O(Σ) = O(52) = O(1) sweep across lower and upper arrays.
    - Auxiliary Space: O(1) auxiliary stack space.
      - Allocates two 26-element stack buffers (208 bytes total).
      - 0 dynamic heap memory allocations.

    Implementation Notes & Evaluation:
    1. Direct-Offset Mapping:
       - Uses (c - 'a') and (c - 'A') scalar indexing to maintain O(1) frequency 
         tracking without hashing overhead.
    2. Parity Aggregation:
       - Adds full count if even; adds (count - 1) if odd and sets oddCountExists flag.
    3. Micro-Optimization Opportunities:
       - Direct ASCII Indexing: A single 128-element buffer avoids per-character conditional branches.
       - Bitwise Truncation: `count & ~1` replaces if/else branching during accumulation.
*/
// int longestPalindrome(const std::string &s)
// {
//     const size_t sSize = s.length();
//     if (sSize <= 1)
//     {
//         return static_cast<int>(sSize);
//     }

//     std::array<int, 26> lowercase{};
//     std::array<int, 26> uppercase{};

//     for (char c : s)
//     {
//         if (c >= 'a' && c <= 'z')
//         {
//             lowercase[c - 'a']++;
//         }
//         else
//         {
//             uppercase[c - 'A']++;
//         }
//     }

//     int maxLen = 0;
//     bool oddCountExists = false;

//     for (int i = 0; i < 26; i++)
//     {
//         int lowerCount = lowercase[i];
//         int upperCount = uppercase[i];

//         if (lowerCount % 2 == 0)
//         {
//             maxLen += lowerCount;
//         }
//         else
//         {
//             oddCountExists = true;
//             maxLen += (lowerCount - 1);
//         }

//         if (upperCount % 2 == 0)
//         {
//             maxLen += upperCount;
//         }
//         else
//         {
//             oddCountExists = true;
//             maxLen += (upperCount - 1);
//         }
//     }

//     if (oddCountExists)
//     {
//         maxLen++;
//     }

//     return maxLen;
// }