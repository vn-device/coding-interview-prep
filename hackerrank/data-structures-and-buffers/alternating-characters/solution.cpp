#include <string>

//==============================================================================
// HackerRank: Alternating Characters
// Strategy: Linear Single-Pass Adjacent Collision Counting
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N is the length of string s.
      - Exactly N - 1 character comparisons in a single contiguous memory pass.
    - Auxiliary Space: O(1) auxiliary stack space.
      - Operates strictly with scalar variables (0 heap allocations).

    Architectural & Algorithmic Notes:
    1. Greedy Adjacent Collision Invariant:
       - In any sequence of identical consecutive characters (e.g., 'AAAA'), 
         preserving exactly one instance requires deleting the other k - 1 characters.
       - Each occurrence where s[i] == s[i - 1] represents a mandatory deletion.
    2. Cache-Friendly Linear Traversal:
       - Traverses contiguous memory sequentially from left to right, triggering 
         hardware prefetching and maximizing L1 data cache throughput.
*/
int alternatingCharacters(const std::string& s)
{
    const size_t n = s.length();
    int deletions = 0;

    // Single-pass adjacent equality sweep
    for (size_t i = 1; i < n; ++i)
    {
        if (s[i] == s[i - 1])
        {
            deletions++;
        }
    }

    return deletions;
}

//==============================================================================
// HackerRank: Alternating Characters
// Implementation: Linear Scan with Explicit State Tracking Register
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N is the length of string s.
      - Single linear pass evaluating N - 1 character transitions.
    - Auxiliary Space: O(1) auxiliary stack space.
      - Zero heap allocations; state maintained via scalar stack variables.

    Implementation Notes & Evaluation:
    1. Explicit State Tracking:
       - Uses `prev` scalar to cache the active anchor character, updating it only 
         when a character transition occurs (`prev != current`).
    2. Redundant Assignment Branch:
       - The `else { prev = current; }` branch introduces unnecessary state copying. 
         Direct index access `s[i] == s[i - 1]` eliminates the `prev` register entirely 
         and streamlines compiler loop unrolling.
    3. Defensive Empty Guard:
       - Includes `if (s.empty())` check, safely guarding against out-of-bounds indexing 
         on `s[0]` when handling empty string edge cases.
*/
// int alternatingCharacters(const std::string &s)
// {
//     if (s.empty())
//     {
//         return 0;
//     }

//     int deletions = 0;
//     char prev = s[0];

//     for (size_t i = 1; i < s.length(); i++)
//     {
//         char current = s[i];
//         if (prev == current)
//         {
//             deletions++;
//         }
//         else
//         {
//             prev = current;
//         }
//     }

//     return deletions;
// }