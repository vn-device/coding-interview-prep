#include <vector>

//==============================================================================
// LeetCode #268: Missing Number
// Strategy: Dual-Range Bitwise XOR Reduction Fold
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - Traverses the index range and input vector in O(N) single-cycle bitwise operations.
    - Auxiliary Space: O(1) auxiliary memory.
      - Maintains state strictly inside scalar CPU register space (missing).

    Algebraic & Hardware Invariants:
    1. Nilpotence / Self-Inverse (x ^ x = 0):
       - Any number present in the array appears twice across the union of 
         the expected sequence [0, N] and nums, cancelling to zero.
    2. Identity Element (x ^ 0 = x):
       - The missing value appears exactly once across the union (in [0, N] only), 
         surviving the complete reduction fold intact.
    3. Overflow Immunity vs. Arithmetic Series:
       - Unlike Gauss's summation formula (N * (N + 1) / 2), bitwise XOR operates 
         bit-by-bit and cannot trigger signed integer overflow on large N.
*/
int missingNumber(const std::vector<int> &nums)
{
    int missing = static_cast<int>(nums.size());;

    for (size_t i = 0; i < nums.size(); ++i)
    {
        missing ^= static_cast<int>(i) ^ nums[i];
    }

    return missing;
}

//==============================================================================
// LeetCode #268: Missing Number
// Implementation: Two-Pass Dual-Range Bitwise XOR Accumulation
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - First pass iterates (N + 1) times across the complete expected index sequence [0, N].
      - Second pass traverses all N elements of the input vector.
      - Total operations equal 2N + 1 iterations, remaining strictly linear O(N).
    - Auxiliary Space: O(1) auxiliary memory.
      - State is isolated to a single scalar variable (missing) without heap or stack allocations.

    Algebraic Invariants:
    1. Nilpotence / Self-Inverse Invariant (x ^ x = 0):
       - Values existing in both the index range [0, N] and the nums vector cancel out to zero.
    2. Identity Element Invariant (x ^ 0 = x):
       - The single missing value appears only once across the two sequences and survives intact.

    Design Considerations & Optimizations:
    - Independent Two-Pass Traversal:
      - Accumulates the expected index range [0, N] and actual array values in two distinct loops.
      - Can be fused into a single forward pass by initializing 'missing = nums.size()' and 
        folding 'i ^ nums[i]' concurrently to reduce branch instructions and maximize pipeline throughput.
*/
int missingNumber(const std::vector<int> &nums)
{
    int missing = 0;

    for (size_t i = 0; i <= nums.size(); i++)
    {
        missing ^= static_cast<int>(i);
    }

    for (int val : nums)
    {
        missing ^= val;
    }

    return missing;
}