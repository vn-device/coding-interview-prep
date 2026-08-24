#include <string>
#include <unordered_map>
#include <algorithm>

//==============================================================================
// HackerRank: Sherlock and Anagrams
// Implementation: Substring Canonical Sorting & Combinatorial Map Reduction
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N^3 log N) where N = s.length().
      - Outer two loops generate O(N^2) contiguous substrings.
      - Sorting each substring of length L takes O(L log L) time, bounded by O(N log N).
      - Map lookup and string key hashing take O(L) = O(N).
      - Final reduction loop scans up to O(U) unique signatures, where U <= N^2.
      - Given N <= 100, the maximum operation count is ~5,000 * 100 log(100) ≈ 3.3e6 ops,
        comfortably passing well within the standard 2.0-second time limit.
    - Auxiliary Space: O(N^2) auxiliary heap memory.
      - Stores up to N(N + 1) / 2 dynamically allocated string keys in std::unordered_map.
      - Temporary string allocations via s.substr() within the inner loop.

    Key Invariants & Mechanism:
    1. Anagram Invariant:
       - Two substrings are anagrams iff their character frequency distributions match.
       - Sorting the characters alphabetically produces identical canonical keys (e.g., "cba" -> "abc").
    2. Frequency Aggregation:
       - std::unordered_map tracks the total occurrences (C) of each unique canonical key.
    3. Combinatorial Reduction:
       - For any signature appearing C times, the number of distinct unordered pairs is C * (C - 1) / 2.
       - Summing these combinations across all hash table entries yields the total valid anagrammatic pairs.
*/
int sherlockAndAnagrams(const std::string &s)
{
    const size_t len = s.length();
    if (len <= 1)
    {
        return 0;
    }

    std::unordered_map<std::string, int> anagramDB;
    for (size_t subLen = 1; subLen <= len; subLen++)
    {
        for (size_t i = 0; i + subLen <= len; i++)
        {
            std::string key = s.substr(i, subLen);
            std::sort(key.begin(), key.end());
            anagramDB[key]++;
        }
    }

    int anagramPairs = 0;
    for (const auto &pair : anagramDB)
    {
        if (pair.second > 1)
        {
            anagramPairs += (pair.second * (pair.second - 1)) / 2;
        }
    }

    return anagramPairs;
}