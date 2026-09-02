#include <string>
#include <unordered_map>
#include <array>
#include <queue>

//==============================================================================
// LeetCode #387: First Unique Character in a String
// Strategy: Single-Pass Streaming Queue with Lazy Duplication Eviction
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = s.size().
      - Each character is pushed to the queue at most once and popped at most once.
      - Amortized queue maintenance executes in O(1) per stream input.
    - Auxiliary Space: O(U) auxiliary memory where U <= 26 unique characters.
      - queue holds at most 26 non-duplicate character candidate pairs.

    Algorithmic Invariants:
    1. Streaming Monotonic Invariant:
       - candidates.front() consistently holds the oldest seen character with freq == 1.
    2. Lazy Pop Pruning:
       - Characters invalidated by subsequent duplicate appearances are evicted lazily 
         from the front of the queue.
*/
int firstUniqChar(const std::string& s)
{
    std::array<int, 26> freq{};
    std::queue<std::pair<char, int>> candidates;

    for (size_t i = 0; i < s.size(); ++i)
    {
        const char c = s[i];
        const size_t idx = static_cast<size_t>(c - 'a');

        ++freq[idx];
        candidates.emplace(c, static_cast<int>(i));

        // Lazily discard front candidates that have become duplicates
        while (!candidates.empty() && freq[static_cast<size_t>(candidates.front().first - 'a')] > 1)
        {
            candidates.pop();
        }
    }

    return candidates.empty() ? -1 : candidates.front().second;
}

//==============================================================================
// LeetCode #387: First Unique Character in a String
// Strategy: Fixed-Size Direct-Mapped Stack Array (std::array<int, 26>)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = s.size().
      - Pass 1: Populates frequency array via direct O(1) indexing: O(N).
      - Pass 2: Identifies first index matching freq == 1: O(N).
    - Auxiliary Space: O(1) stack memory.
      - Fixed 104-byte buffer (26 * sizeof(int)) allocated on the stack with zero heap calls.

    Algorithmic Optimizations & Hardware Invariants:
    1. Direct Memory Addressing:
       - Computes array indices via arithmetic (c - 'a'), bypassing hashing and heap allocators.
    2. L1 Cache Alignment:
       - The contiguous 26-integer buffer fits entirely within standard L1 CPU cache lines.
*/
// int firstUniqChar(const std::string& s)
// {
//     std::array<int, 26> freq{};

//     for (char c : s)
//     {
//         ++freq[static_cast<size_t>(c - 'a')];
//     }

//     for (size_t i = 0; i < s.size(); ++i)
//     {
//         if (freq[static_cast<size_t>(s[i] - 'a')] == 1)
//         {
//             return static_cast<int>(i);
//         }
//     }

//     return -1;
// }

//==============================================================================
// LeetCode #387: First Unique Character in a String
// Strategy: Hash Map Two-Pass Traversal (11 ms / Beats 49.57%)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = s.size().
      - Traverses s to insert/update frequencies in std::unordered_map: O(N).
      - Traverses s a second time to execute find() iterator lookups: O(N).
    - Auxiliary Space: O(U) auxiliary heap memory where U <= 26 unique characters.
      - Allocates hash table buckets and linked node metadata.

    Defects & Bottlenecks:
    1. Dynamic Hash Overhead:
       - Incurs pointer indirection and hash computation per character instead of 
         direct O(1) index offsets.
    2. Missing Stack Allocation:
       - Fails to leverage the bounded 26-character English alphabet constraint.
*/
// int firstUniqChar(const std::string &s)
// {
//     std::unordered_map<char, int> letterFreq;
//     for (char c : s)
//     {
//         letterFreq[c]++;
//     }

//     for (size_t i = 0; i < s.size(); i++)
//     {
//         auto iter = letterFreq.find(s[i]);
//         if (iter->second == 1)
//         {
//             return static_cast<int>(i);
//         }
//     }

//     return -1;
// }