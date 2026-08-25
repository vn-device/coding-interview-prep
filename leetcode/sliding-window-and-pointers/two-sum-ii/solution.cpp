#include <vector>

//==============================================================================
// LeetCode #167: Two Sum II - Input Array Is Sorted
// Strategy: Monotonic Converging Two-Pointer Traversal (0 ms / Beats 100.00%)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = numbers.size()[cite: 8].
      - Single-pass converging scan from array boundaries toward center[cite: 8].
      - Exactly one pointer (lBound or rBound) advances on each iteration, 
        guaranteeing at most N total pointer steps[cite: 8].
    - Auxiliary Space: O(1) auxiliary memory[cite: 8].
      - Executes strictly on the stack with zero dynamic heap allocations[cite: 8].

    Mathematical Invariants:
    1. Monotonic Search Space Reduction:
       - For sorted array A and bounds L < R, sum S = A[L] + A[R][cite: 8].
       - If S > target: A[R] cannot pair with any element at index >= L, 
         safely eliminating index R from the candidate space (R--)[cite: 8].
       - If S < target: A[L] cannot pair with any element at index <= R, 
         safely eliminating index L from the candidate space (L++)[cite: 8].
    2. 1-Based Index Mapping:
       - Returns {L + 1, R + 1} upon match satisfying 1-indexed specification[cite: 8].
*/
std::vector<int> twoSum(std::vector<int> &numbers, int target)
{
    const int n = static_cast<int>(numbers.size());
    int lBound = 0;
    int rBound = n - 1;

    while (lBound < rBound)
    {
        int sum = numbers[lBound] + numbers[rBound];
        if (sum == target)
        {
            return {lBound + 1, rBound + 1};
        }
        else if (sum > target)
        {
            rBound--;
        }
        else // if (sum < target)
        {
            lBound++;
        }
    }

    return {};
}