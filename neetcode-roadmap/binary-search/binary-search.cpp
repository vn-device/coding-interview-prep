#include <vector>

//==============================================================================
// LeetCode #704 / NeetCode: Binary Search
// Strategy: Iterative Closed-Interval [left, right] Search with Overflow-Safe Midpoint
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(log N) where N = nums.size().
      - Halves the active search interval [left, right] on each comparison.
    - Auxiliary Space: O(1) strictly three register-resident 32-bit integers.
      - Zero heap allocations and zero recursive call-stack frames.

    Algorithmic & Hardware Invariants:
    1. Overflow-Safe Midpoint Arithmetic:
       - Uses left + ((right - left) / 2) rather than (left + right) / 2 to
         prevent signed 32-bit integer overflow when left + right > INT_MAX.
    2. Closed-Interval Termination Guarantee:
       - Invariant [left, right] shrinks strictly on every non-matching branch
         (left = mid + 1 or right = mid - 1), guaranteeing termination in at most
         floor(log2(N)) + 1 iterations.
*/
int search(const std::vector<int>& nums, int target)
{
    int left = 0;
    int right = static_cast<int>(nums.size()) - 1;

    while (left <= right)
    {
        const int mid = left + ((right - left) / 2);
        const int val = nums[mid];

        if (val < target)
        {
            left = mid + 1;
        }
        else if (val > target)
        {
            right = mid - 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}

// int search(const std::vector<int>& nums, int target)
// {
//     int left = 0;
//     int right = static_cast<int>(nums.size()) - 1;
//     int mid = (left + right) / 2;
//     bool found = false;

//     while (left <= right)
//     {
//         int check = nums[mid];

//         if (check < target)
//         {
//             left = mid + 1;
//         }
//         else if (check > target)
//         {
//             right = mid - 1;
//         }
//         else
//         {
//             found = true;
//             break;
//         }

//         mid = (left + right) / 2;
//     }

//     return found ? mid : -1;
// }