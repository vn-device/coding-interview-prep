#include <vector>

//==============================================================================
// HackerRank: Lonely Integer
// Strategy: Bitwise XOR Accumulation Fold
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = a.size().
      - Traverses the input vector exactly once in a single sequential pass.
      - Each bitwise XOR step translates directly to a single-cycle CPU instruction.
    - Auxiliary Space: O(1) auxiliary memory.
      - Operates entirely within scalar register space (result) with zero heap 
        or stack buffer allocations.

    Algebraic & Hardware Invariants:
    1. Nilpotence & Self-Inverse (x ^ x = 0):
       - Paired duplicate elements neutralize bit-for-bit to zero, regardless of 
         their relative index positioning in memory.
    2. Identity Element (x ^ 0 = x):
       - The initial accumulator state (0) preserves the first encountered value, 
         ensuring the single unpaired integer survives the reduction fold.
    3. Commutativity & Associativity:
       - Eliminates the need to presort or bucket elements into a hash table, 
         maximizing linear streaming performance and hardware prefetcher efficiency.
*/
int lonelyinteger(const std::vector<int>& a)
{
    int result = 0;
    
    for (int num : a)
    {
        result ^= num;
    }
    
    return result;
}