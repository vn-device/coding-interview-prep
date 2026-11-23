#include <vector>
#include <algorithm>

//==============================================================================
// LeetCode #42 / NeetCode: Trapping Rain Water
// Strategy: Converging Two-Pointer Running Boundary Maximums (O(1) Space)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = height.size().
      - Single converging linear pass; 'left' and 'right' meet after N - 1 steps.
    - Auxiliary Space: O(1) strictly register-resident scalar variables.
      - Zero dynamic memory allocations.

    Algorithmic & Hardware Invariants:
    1. Early Geometric Pruning:
       - Arrays with fewer than 3 bars cannot form a basin; returning 0 upfront
         also prevents out-of-bounds reads on empty inputs.
    2. Bottleneck Boundary Guarantee:
       - Advancing the side with the smaller running maximum locks in that maximum
         as the exact water ceiling for the newly visited bar.
*/
int trap(const std::vector<int>& height)
{
    const int len = static_cast<int>(height.size());
    if (len < 3)
    {
        return 0;
    }

    int left = 0;
    int right = len - 1;

    int water = 0;
    int leftMax = height[left];
    int rightMax = height[right];

    while (left < right)
    {
        if (leftMax < rightMax)
        {
            ++left;
            leftMax = std::max(leftMax, height[left]);
            water += leftMax - height[left];
        }
        else
        {
            --right;
            rightMax = std::max(rightMax, height[right]);
            water += rightMax - height[right];
        }
    }

    return water;
}

// int trap(const std::vector<int>& height)
// {
//     const int len = static_cast<int>(height.size());
//     int left = 0;
//     int right = len - 1;

//     int water = 0;
//     int leftMax = height[left];
//     int rightMax = height[right];

//     while (left < right)
//     {
//         if (leftMax < rightMax)
//         {
//             ++left;
//             leftMax = std::max(leftMax, height[left]);
//             water += leftMax - height[left];
//         }
//         else // if (leftMax >= rightMax)
//         {
//             --right;
//             rightMax = std::max(rightMax, height[right]);
//             water += rightMax - height[right];
//         }
//     }

//     return water;
// }