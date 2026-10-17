#include <vector>
#include <algorithm>

//==============================================================================
// LeetCode #435: Non-overlapping Intervals
// Strategy: Greedy Finish-Time Sorting with O(1) Scalar Horizon Tracking
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log N) dominated by std::sort, followed by an O(N) sweep.
    - Auxiliary Space: O(1) auxiliary register space with zero heap allocations.

    Algorithmic & Hardware Invariants:
    1. Early Return Guard:
       - Guards against intervals.empty() to prevent out-of-bounds indexing.
    2. Strict Weak Ordering:
       - Comparator (a[1] < b[1]) preserves irreflexivity and asymmetry.
    3. Scalar Horizon Invariant:
       - Tracking 'backend' in a single primitive integer eliminates stack buffers
         and maximizes L1 data cache throughput.
*/

int eraseOverlapIntervals(std::vector<std::vector<int>> &intervals)
{
    std::sort(intervals.begin(), intervals.end(),
        [](const std::vector<int> &a, const std::vector<int> &b)
        {
            return a[1] < b[1];
        }
    );

    int backend = intervals[0][1];
    int removals = 0;
    const size_t len = intervals.size();

    for (size_t i = 1; i < len; ++i)
    {
        if (backend > intervals[i][0])
        {
            ++removals;
        }
        else
        {
            backend = intervals[i][1];
        }
    }

    return removals;
}