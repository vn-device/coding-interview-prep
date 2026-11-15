#include <vector>

//==============================================================================
// LeetCode #167 / NeetCode: Two Integer Sum II (Input Array Is Sorted)
// Strategy: Converging Two-Pointer Search Space Elimination (O(1) Space)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = numbers.size().
      - Each iteration advances 'left' or retreats 'right' by 1 step, bounding
        total iterations to at most N - 1.
    - Auxiliary Space: O(1) strictly stack-resident scalar indices.
      - Zero auxiliary heap structures (eliminates the O(N) hash map from Two Sum I).

    Algorithmic & Hardware Invariants:
    1. Sorted Monotonicity Pruning:
       - sum < target eliminates numbers[left] against all remaining indices <= right.
       - sum > target eliminates numbers[right] against all remaining indices >= left.
    2. Bidirectional Cache Prefetching:
       - Contiguous linear strides from both ends trigger sequential hardware cache prefetchers.
    3. 1-Based Index Contract:
       - Returns {left + 1, right + 1} via direct initializer-list construction.
*/
std::vector<int> twoSum(const std::vector<int>& numbers, int target)
{
    int left = 0;
    int right = static_cast<int>(numbers.size()) - 1;

    while (left < right)
    {
        int sum = numbers[left] + numbers[right];

        if (sum == target)
        {
            return {left + 1, right + 1};
        }
        else if (sum < target)
        {
            ++left;
        }
        else // if (sum > target)
        {
            --right;
        }
    }

    return {};
}