//==============================================================================
// LeetCode #191: Number of 1 Bits
// Strategy: Brian Kernighan's Lowest-Set-Bit Reset Invariant
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(k) where k is the population count (number of set bits).
      - Worst case: O(32) = O(1) when all bits are set.
      - Best case: O(1) when n = 0 (loop terminates immediately).
    - Auxiliary Space: O(1) auxiliary memory.
      - Operates strictly within scalar registers without heap or stack allocations.

    Bitwise & Hardware Invariants:
    1. Lowest Set Bit Clearing:
       - Subtracting 1 inverts the lowest set bit and all trailing zeros to ones.
       - Bitwise ANDing 'n & (n - 1)' cancels out precisely that lowest set bit, 
         reducing loop cycles strictly to the count of 1s rather than total word length.
    2. Register-Level Execution:
       - Avoids multi-step conditional bit shifts and branch-heavy masking loops.
       - Modern architectures with SSE4.2/POPCNT can execute this natively via 
         '__builtin_popcount' or C++20 'std::popcount' in a single cycle.
*/
int hammingWeight(int n)
{
    int setBits = 0;

    while (n)
    {
        n &= (n - 1);
        setBits++;
    }

    return setBits;
}