#include <vector>

//==============================================================================
// LeetCode #134: Gas Station
// Strategy: Single-Pass Greedy Scan with Global Deficit Verification
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) single-pass linear sweep across the buffer.
    - Auxiliary Space: O(1) scalar register storage with zero heap allocations.

    Algorithmic & Hardware Invariants:
    1. Global Solvability Invariant:
       - If totalGas >= totalCost (or totalTank >= 0), a valid circular traversal 
         is mathematically guaranteed to exist.
    2. Local Candidate Invalidation:
       - If traveling from 'start' causes 'currentGas' to dip below 0 at index 'i',
         no station in range [start, i] can be a valid starting station.
       - The candidate start index is safely fast-forwarded to 'i + 1', pruning 
         the quadratic search space down to O(N).
    3. Cache-Line Stream Contiguity:
       - Traverses gas and cost vectors linearly in lockstep, leveraging CPU 
         hardware prefetchers.
*/

int canCompleteCircuit(const std::vector<int> &gas, const std::vector<int> &cost)
{
    const size_t len = gas.size();
    int totalGas = 0;
    int currentGas = 0;
    int station = 0;

    for (size_t i = 0; i < len; ++i)
    {
        int netGas = gas[i] - cost[i];
        totalGas += netGas;
        currentGas += netGas;

        if (currentGas < 0)
        {
            station = i + 1;
            currentGas = 0;
        }
    }

    return (totalGas >= 0) ? station : -1;
}