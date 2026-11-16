#include <vector>
#include <algorithm>

//==============================================================================
// LeetCode #11 / NeetCode: Container With Most Water
// Strategy: Converging Two-Pointer Greedy Contraction with Sub-Threshold Pruning
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = heights.size().
      - Single converging pass where 'left' and 'right' meet after N - 1 steps.
    - Auxiliary Space: O(1) strictly stack/register-resident scalar variables.
      - Zero heap allocations.

    Algorithmic & Hardware Invariants:
    1. Bottleneck Boundary Advancement:
       - Area is capped by min(heights[left], heights[right]). Moving the taller
         wall inward strictly reduces width without increasing the height cap.
    2. Sub-Threshold Fast-Forwarding:
       - After computing area for 'minHeight', any inward bar with height <= minHeight
         yields strictly smaller area (smaller width, non-increasing height) and
         can be skipped without computing multiplication.
*/
int maxArea(const std::vector<int>& heights)
{
    int result = 0;
    int left = 0;
    int right = static_cast<int>(heights.size()) - 1;

    while (left < right)
    {
        const int minHeight = std::min(heights[left], heights[right]);
        result = std::max(result, (right - left) * minHeight);

        // Skip inward bars that cannot exceed the current bounding height
        while (left < right && heights[left] <= minHeight)
        {
            ++left;
        }

        while (left < right && heights[right] <= minHeight)
        {
            --right;
        }
    }

    return result;
}

// int maxArea(const std::vector<int>& heights)
// {
//     int result = 0;
//     int left = 0;
//     int right = static_cast<int>(heights.size()) - 1;

//     while (left < right)
//     {
//         int height = std::min(heights[left], heights[right]);
//         int width = right - left;
//         result = std::max(result, height * width);

//         if (heights[left] < heights[right])
//         {
//             ++left;
//         }
//         else // if (heights[left] >= heights[right])
//         {
//             --right;
//         }
//     }

//     return result;
// }