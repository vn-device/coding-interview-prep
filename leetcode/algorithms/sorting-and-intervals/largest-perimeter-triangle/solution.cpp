#include <vector>
#include <numeric>
#include <algorithm>

//==============================================================================
// LeetCode #976: Largest Perimeter Triangle
// Strategy: Reverse Monotonic Triplet Sweep & Triangle Inequality Invariant
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log N)
      - Dominated by std::sort at O(N log N).
      - Single-pass reverse scan takes O(N) worst-case, O(1) best-case.
    - Auxiliary Space: O(1) auxiliary memory.
      - Operates in-place on vector elements with 0 heap allocations.

    Mathematical Proof & Greedy Invariants:
    1. Triangle Inequality:
       - For sorted side lengths a <= b <= c, a non-degenerate triangle forms iff a + b > c.
    2. Maximal Predecessor Invariant:
       - For any fixed hypotenuse c = nums[i], the pair maximizing the sum (a + b) 
         is strictly the two largest preceding elements: nums[i-1] and nums[i-2].
       - If nums[i-2] + nums[i-1] <= nums[i], then for all j < i-1, k < j:
         nums[k] + nums[j] <= nums[i-2] + nums[i-1] <= nums[i].
       - Thus, if the immediate adjacent triplet fails, no triangle can be formed with nums[i].
    3. Global Optimality:
       - Scanning from the largest elements guarantees the first valid triplet encountered 
         has the strictly maximum possible sum (perimeter).
*/
int largestPerimeter(std::vector<int>& nums)
{
    std::sort(nums.begin(), nums.end());

    const int n = static_cast<int>(nums.size());

    // Traverse backwards from the largest potential hypotenuse
    for (int i = n - 1; i >= 2; --i)
    {
        // By monotonicity, nums[i-2] + nums[i-1] is the maximal sum available for nums[i]
        if (nums[i - 2] + nums[i - 1] > nums[i])
        {
            return nums[i - 2] + nums[i - 1] + nums[i];
        }
    }

    return 0;
}

//==============================================================================
// LeetCode #976: Largest Perimeter Triangle
// Implementation: Initial Sort with Nested Linear Sweep & Dynamic Buffer (4 ms)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N^2) worst-case, O(N log N) best/average[cite: 6].
      - std::sort requires O(N log N) time[cite: 6].
      - Nested for-loop structure evaluates up to O(N^2) triplet combinations[cite: 6].
    - Auxiliary Space: O(1) stack / O(1) dynamic heap space[cite: 6].
      - Allocates heap storage via std::vector<int> sideLens (reserved 3 ints)[cite: 6].

    Defects & Bottlenecks:
    1. Redundant Inner Loop:
       - If nums[i-1] + nums[i-2] <= nums[i], no pair further left can exceed nums[i][cite: 6]. 
         Scanning j down to 0 performs unneeded branch evaluations[cite: 6].
    2. Dynamic Buffer Allocation:
       - Instantiating sideLens pushes small integer buffers through allocator/deallocator 
         paths instead of computing scalar arithmetic directly in registers[cite: 6].
*/
// int largestPerimeter(std::vector<int> &nums)
// {
//     std::sort(nums.begin(), nums.end());

//     const int numsSize = static_cast<int>(nums.size());
//     bool tripletFound = false;
//     std::vector<int> sideLens;
//     sideLens.reserve(3);

//     for (int i = numsSize - 1; i >= 0; i--)
//     {
//         int longestLen = nums[i];

//         for (int j = i - 1; j - 1 >= 0; j--)
//         {
//             if (nums[j - 1] + nums[j] > longestLen)
//             {
//                 sideLens.push_back(longestLen);
//                 sideLens.push_back(nums[j]);
//                 sideLens.push_back(nums[j - 1]);
//                 tripletFound = true;
//                 break;
//             }
//         }

//         if (tripletFound)
//         {
//             break;
//         }
//     }

//     return (tripletFound) ? std::accumulate(sideLens.begin(), sideLens.end(), 0) : 0;
// }