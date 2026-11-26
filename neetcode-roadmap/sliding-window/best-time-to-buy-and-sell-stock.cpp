#include <vector>
#include <algorithm>

//==============================================================================
// LeetCode #121 / NeetCode: Best Time to Buy and Sell Stock
// Strategy: Dynamic Two-Pointer Sliding Window (Left-Snap on New Minimum)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = prices.size().
      - Single linear pass where 'right' advances 1 step per iteration.
    - Auxiliary Space: O(1) strictly stack/register-resident scalar indices.
      - Zero dynamic allocations.

    Algorithmic & Hardware Invariants:
    1. Left-Boundary Snap Invariant:
       - 'left' anchors the lowest purchase price seen so far.
       - If prices[right] < prices[left], no future sell day can achieve a higher
         profit using the old 'left' than using 'right'; snap left = right.
    2. Hardware Branching vs. CMOV:
       - Compiles cleanly to register comparisons with sequential L1 cache reads.
*/

int maxProfit(const std::vector<int>& prices)
{
    const int len = static_cast<int>(prices.size());
    int left = 0;
    int maxProfit = 0;

    for (int right = 1; right < len; ++right)
    {
        if (prices[right] > prices[left])
        {
            maxProfit = std::max(maxProfit, prices[right] - prices[left]);
        }
        else
        {
            // Found a strictly lower buy price; collapse window left bound to right
            left = right;
        }
    }

    return maxProfit;
}