#include <vector>
#include <numeric>
#include <algorithm>

//==============================================================================
// LeetCode #1005: Maximize Sum Of Array After K Negations
// Strategy: Greedy Sorting & Parity-Based Penalty Minimization
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log N) where N is the number of elements in nums.
      - std::sort dominates at O(N log N).
      - Linear greedy negative scan runs in O(N).
      - std::accumulate and std::min_element execute in O(N).
    - Auxiliary Space: O(1) auxiliary memory.
      - Operates entirely in-place on the input vector.
      - 0 dynamic heap allocations.

    Greedy Invariants & Mathematical Proof:
    1. Maximum Delta Gain on Negatives:
       - Negating x < 0 increases the overall sum by 2 * |x|. 
       - Sorting in ascending order ensures we invert the most negative numbers first, 
         maximizing the immediate positive delta for each consumed negation operation.
    2. Zero Penalty on Even Residual Operations:
       - If k operations remain after all negative numbers are flipped, any even remainder 
         (k % 2 == 0) can be absorbed by flipping the same element back and forth:
         -(-x) = x, yielding zero net change to the total sum.
    3. Minimum Penalty on Odd Residual Operations:
       - If k % 2 == 1 remains, exactly one positive number must be negated.
       - To minimize the total deduction (2 * x), we subtract twice the global minimum 
         element found via std::min_element.
    4. Boundary Protection:
       - Guards array indexing with `index < n` to prevent buffer overflows when k exceeds 
         the total count of negative elements.
*/
int largestSumAfterKNegations(std::vector<int>& nums, int k)
{
    std::sort(nums.begin(), nums.end());
    int index = 0;

    while (k > 0 && index < nums.size() && nums[index] < 0)
    {
        nums[index] = -nums[index];
        index++;
        k--;
    }

    int currentSum = std::accumulate(nums.begin(), nums.end(), 0);
    if (k % 2 == 1)
    {
        auto minIter = std::min_element(nums.begin(), nums.end());
        int minVal = *minIter;
        currentSum -= (2 * minVal);
    }

    return currentSum;
}

//==============================================================================
// LeetCode #1005: Maximize Sum Of Array After K Negations
// Implementation: Initial Greedy Sort with Unbounded Indexing (Partial Pass: 80/84)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log N) where N is the length of nums[cite: 8].
      - std::sort requires O(N log N) time[cite: 8].
      - While loop scans up to N negative elements in O(N)[cite: 8].
      - std::accumulate runs in O(N)[cite: 8].
      - std::min_element runs in O(N) when k % 2 == 1[cite: 8].
    - Auxiliary Space: O(1) auxiliary memory (modifies nums in-place)[cite: 8].

    Failure Mode & Boundary Defect:
    1. Buffer Over-read / Unbounded Indexing:
       - Loop condition `while (k > 0 && nums[index] < 0)` lacks a boundary check 
         `index < nums.size()`[cite: 8].
       - When all elements in the array are negative and k exceeds nums.size() 
         (e.g., nums = {-100, -100, -100} with k >= 4), index increments past 
         the end of the buffer[cite: 8], evaluating `nums[nums.size()] < 0` and triggering 
         undefined behavior / segmentation faults[cite: 8].
    2. Redundant Iteration / Branching:
       - Instantiates `minIter` and reads `*minIter` separately rather than combining 
         directly or tracking running minimums during the scan[cite: 8].
*/
// int largestSumAfterKNegations(std::vector<int> &nums, int k)
// {
//     std::sort(nums.begin(), nums.end());
//     int finalSum = 0;
//     int index = 0;

//     while (k > 0 && nums[index] < 0)
//     {
//         nums[index] = -nums[index];
//         index++;
//         k--;
//     }

//     int currentSum = std::accumulate(nums.begin(), nums.end(), 0);
//     if (k % 2 == 0)
//     {
//         finalSum = currentSum;
//     }
//     else // if (k % 2 == 1)
//     {
//         auto minIter = std::min_element(nums.begin(), nums.end());
//         int minVal = *minIter;
//         finalSum = currentSum - 2 * minVal;
//     }

//     return finalSum;
// }