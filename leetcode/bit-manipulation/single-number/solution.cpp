#include <vector>

//==============================================================================
// LeetCode #136: Single Number
// Strategy: Bitwise XOR Accumulation Fold
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - Executes a single forward pass over the contiguous buffer.
      - Each step translates directly to a single-cycle bitwise XOR instruction.
    - Auxiliary Space: O(1) auxiliary memory.
      - Operates strictly within CPU scalar register space without heap or stack allocations.

    Algebraic & Hardware Invariants:
    1. Nilpotence / Self-Inverse Invariant (x ^ x = 0):
       - Paired identical values negate to zero irrespective of memory order.
    2. Identity Element Invariant (x ^ 0 = x):
       - Initializing the register accumulator to zero guarantees that XORing the 
         unpaired value preserves its exact bit pattern intact.
    3. Contiguous Streaming & Prefetching:
       - Sequentially accessing std::vector maximizes L1 data cache line utilization 
         and eliminates CPU branch mispredictions.
*/
int singleNumber(const std::vector<int> &nums)
{
    int result = 0;

    for (int val : nums)
    {
        result ^= val;
    }

    return result;
}