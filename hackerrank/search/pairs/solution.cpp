#include <vector>
#include <algorithm>

//==============================================================================
// HackerRank: Pairs
// Strategy: In-Place Sort with Monotonic Two-Pointer Difference Traversal
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log N)
      - Dominated entirely by std::sort at O(N log N).
      - Two-pointer traversal advances left and right at most N steps each -> O(N) scan.
    - Auxiliary Space: O(1) auxiliary stack space.
      - Modifies vector in-place with zero heap allocations.

    Mathematical Invariants:
    1. Monotonic Step Invariant:
       - For sorted distinct array A, the difference D(left, right) = A[right] - A[left] 
         is strictly increasing with respect to right and strictly decreasing with respect to left.
    2. Two-Pointer Windowing:
       - If D < k, increasing right increases D toward k.
       - If D > k, increasing left decreases D toward k.
       - If D == k, both pointers must advance because all elements are unique.
*/
int pairs(int k, std::vector<int>& arr)
{
    std::sort(arr.begin(), arr.end());

    int possiblePairs = 0;
    size_t left = 0;
    size_t right = 1;
    const size_t n = arr.size();

    while (right < n)
    {
        const int diff = arr[right] - arr[left];

        if (diff == k)
        {
            possiblePairs++;
            left++;
            right++;
        }
        else if (diff < k)
        {
            right++;
        }
        else // diff > k
        {
            left++;
            if (left == right)
            {
                right++;
            }
        }
    }

    return possiblePairs;
}

//==============================================================================
// HackerRank: Pairs
// Implementation: In-Place Sort with Linear std::find Search (O(N^2) Worst-Case)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N^2) worst-case, O(N log N) best-case.
      - std::sort requires O(N log N) preprocessing.
      - std::find performs an unguided O(N) sequential scan on each iteration.
      - Overall time is bounded by O(N * N) = O(N^2), triggering timeouts on large inputs.
    - Auxiliary Space: O(1) auxiliary memory.
      - Operates in-place on the input vector with 0 dynamic heap allocations.

    Defects & Bottlenecks:
    1. Redundant Sequential Traversal:
       - std::find fails to exploit the sorted order established by std::sort.
    2. Missing Exploitation of Monotonicity:
       - Every target lookup starts scanning from arr.begin() + i without carrying forward 
         the search boundary from prior iterations.
*/
// int pairs(int k, std::vector<int> &arr)
// {
//     std::sort(arr.begin(), arr.end());

//     int possiblePairs = 0;
//     int max = arr.back();

//     for (size_t i = 0; i < arr.size(); i++)
//     {
//         int target = arr[i] + k;
//         if (target > max)
//         {
//             break;
//         }
//         else
//         {
//             if (std::find(arr.begin() + i, arr.end(), target) != arr.end())
//             {
//                 possiblePairs++;
//             }
//         }
//     }

//     return possiblePairs;
// }