#include <vector>
#include <algorithm>

//==============================================================================
// LeetCode #84 / NeetCode: Largest Rectangle in Histogram
// Strategy: Single-Pass Monotonic Increasing Index Stack with Virtual Sentinel
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = heights.size().
      - Every index i in [0, N - 1] is pushed onto the stack once and popped once.
      - Total inner while-loop iterations across the entire scan <= N.
    - Auxiliary Space: O(N) worst-case stack capacity (strictly increasing input).
      - Eliminates the two O(N) leftBoundary/rightBoundary heap arrays from the
        two-pass DP/stack approach.

    Algorithmic & Hardware Invariants:
    1. Dual-Boundary Resolution on Eviction:
       - Maintaining a monotonic increasing stack of indices ensures that when
         heights[i] < heights[stack.back()], index 'i' is the first smaller bar
         to the right, and the element directly beneath stack.back() is the first
         smaller bar to the left.
    2. Virtual Zero-Height Sentinel (i == len):
       - Evaluating currHeight = (i == len) ? 0 : heights[i] forces eviction of
         all surviving bars at the right boundary without mutating the const
         input vector or duplicating the pop loop.
    3. Contiguous Buffer Residency:
       - std::vector<int> with reserve(len) prevents dynamic reallocations and
         avoids std::deque chunk indirection.
*/
int largestRectangleArea(const std::vector<int>& heights)
{
    const int len = static_cast<int>(heights.size());
    std::vector<int> indexStack;
    indexStack.reserve(len);

    int maxArea = 0;

    for (int i = 0; i <= len; ++i)
    {
        // Virtual sentinel height 0 at i == len flushes remaining bars in stack
        const int currHeight = (i == len) ? 0 : heights[i];

        while (!indexStack.empty() && currHeight < heights[indexStack.back()])
        {
            const int height = heights[indexStack.back()];
            indexStack.pop_back();

            // Left boundary is the new stack top (or -1 if no smaller bar exists to the left)
            const int leftBoundary = indexStack.empty() ? -1 : indexStack.back();
            const int width = i - leftBoundary - 1;

            maxArea = std::max(maxArea, height * width);
        }

        indexStack.push_back(i);
    }

    return maxArea;
}