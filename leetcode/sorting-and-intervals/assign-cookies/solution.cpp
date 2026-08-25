#include <vector>
#include <algorithm>

//==============================================================================
// LeetCode #455: Assign Cookies
// Strategy: Dual Greedy Sort with Early-Exit Two-Pointer Marching
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(M log M + N log N)
      - Sorting dominates the runtime: O(M log M + N log N).
      - Single-pass two-pointer traversal takes O(min(M, N)) due to early termination.
    - Auxiliary Space: O(1) auxiliary memory (in-place pointer advancement).

    Greedy Invariant & Systems Logic:
    1. Minimal Waste Invariant:
       - Sorting both arrays in non-decreasing order guarantees that the smallest 
         viable cookie satisfies the least greedy child without wasting large cookies.
    2. Early Termination:
       - Traversal exits as soon as either all children are satisfied (childPtr == gSize) 
         or available cookies are exhausted (cookiePtr == sSize).
    3. Direct State Invariant:
       - The child index `childPtr` directly represents the count of satisfied children, 
         eliminating secondary accumulation variables.
*/
int findContentChildren(std::vector<int> &g, std::vector<int> &s)
{
    std::sort(g.begin(), g.end());
    std::sort(s.begin(), s.end());

    const size_t gSize = g.size();
    const size_t sSize = s.size();

    size_t childPtr = 0;
    size_t cookiePtr = 0;

    // Greedily satisfy the least demanding children with the smallest eligible cookies
    while (childPtr < gSize && cookiePtr < sSize)
    {
        if (s[cookiePtr] >= g[childPtr])
        {
            childPtr++;
        }
        cookiePtr++;
    }

    return static_cast<int>(childPtr);
}

//==============================================================================
// LeetCode #455: Assign Cookies
// Implementation: Initial Greedy Sort with Full Scan (Beats 14.99%)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(M log M + N log N) where M = g.size() and N = s.size()[cite: 9].
      - std::sort on greed factor array g requires O(M log M)[cite: 9].
      - std::sort on cookie size array s requires O(N log N)[cite: 9].
      - Outer loop executes exactly N iterations regardless of early satisfaction[cite: 9].
    - Auxiliary Space: O(1) auxiliary memory (modifies input vectors in-place)[cite: 9].

    Bottlenecks & Redundancies:
    1. Unpruned Loop Cycles:
       - Continues iterating over remaining cookie elements even after all children 
         have been satisfied (gIndex reaches gSize)[cite: 9].
    2. Redundant State Tracking:
       - Tracks both `satisfied` and `gIndex` concurrently despite them sharing 
         identical scalar values throughout traversal[cite: 9].
*/
// int findContentChildren(std::vector<int> &g, std::vector<int> &s)
// {
//     const size_t gSize = g.size();
//     const size_t sSize = s.size();
//     if (sSize == 0)
//     {
//         return 0;
//     }

//     std::sort(g.begin(), g.end());
//     std::sort(s.begin(), s.end());

//     int satisfied = 0;
//     int gIndex = 0;

//     for (size_t j = 0; j < sSize; j++)
//     {
//         if (gIndex < gSize && s[j] >= g[gIndex])
//         {
//             satisfied++;
//             gIndex++;
//         }
//     }

//     return satisfied;
// }