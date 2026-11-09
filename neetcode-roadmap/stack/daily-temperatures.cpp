#include <vector>

//==============================================================================
// LeetCode #739 / NeetCode: Daily Temperatures
// Strategy: Monotonic Decreasing Index Stack (Amortized O(N) Next-Greater Element)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = temperatures.size().
      - Each index is pushed onto the stack exactly once and popped at most once.
      - Total while-loop iterations across the entire loop <= N.
    - Auxiliary Space: O(N) worst-case stack capacity (strictly decreasing input).
      - Buffer pre-allocation prevents mid-traversal vector reallocations.

    Algorithmic & Hardware Invariants:
    1. Monotonic Decreasing Order:
       - The stack stores indices corresponding to strictly non-increasing temperatures.
    2. Next Greater Resolution:
       - Arrival of temperatures[i] > temperatures[buffer.back()] immediately resolves
         the wait time for buffer.back() as (i - buffer.back()).
    3. Contiguous Buffer Residency:
       - std::vector<int> avoids std::deque chunk indirection, maximizing L1 cache hits.
*/
std::vector<int> dailyTemperatures(const std::vector<int>& temperatures)
{
    const size_t len = temperatures.size();
    std::vector<int> result(len, 0);
    std::vector<int> buffer;
    buffer.reserve(len);

    for (size_t i = 0; i < len; ++i)
    {
        while (!buffer.empty() && temperatures[i] > temperatures[buffer.back()])
        {
            int back = buffer.back();
            buffer.pop_back();

            result[back] = i - back;
        }

        buffer.push_back(i);
    }

    return result;
}