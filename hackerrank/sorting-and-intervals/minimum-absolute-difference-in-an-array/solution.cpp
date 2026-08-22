#include <vector>
#include <algorithm>
#include <limits>

//==============================================================================
// HackerRank: Minimum Absolute Difference in an Array
// Strategy: Optimal Monotonic Sort & Adjacent Delta Scan with Early Exit
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log N)
      - std::sort dominates at O(N log N).
      - Single-pass adjacent difference scan takes O(N), with O(1) best-case exit on zero delta.
    - Auxiliary Space: O(1) auxiliary memory.
      - In-place mutation of input vector; 0 dynamic heap allocations.

    Mathematical Invariant:
    1. Adjacent Pair Minimization:
       - For any three sorted elements a <= b <= c, (b - a) <= (c - a) and (c - b) <= (c - a).
       - Therefore, the global minimum absolute difference across all N*(N-1)/2 pairs 
         is guaranteed to occur between at least one adjacent pair in the sorted sequence.
    2. Non-Negative Subtraction:
       - By sorted monotonicity, (arr[i + 1] - arr[i]) >= 0, eliminating sign-checking instructions.
    3. Early Exit Optimization:
       - If minDiff reaches 0, no smaller non-negative difference can exist; terminates immediately.
*/
int minimumAbsoluteDifference(std::vector<int>& arr)
{
    std::sort(arr.begin(), arr.end());
    int minDiff = std::numeric_limits<int>::max();
    const size_t n = arr.size();

    // Bound loop to n - 1 to prevent out-of-bounds access on arr[i + 1]
    for (size_t i = 0; i < n - 1; ++i)
    {
        // arr is sorted ascending; (arr[i + 1] - arr[i]) is guaranteed >= 0
        int delta = arr[i + 1] - arr[i];
        if (delta < minDiff)
        {
            minDiff = delta;
            if (minDiff == 0)
            {
                break;
            }
        }
    }

    return minDiff;
}

//==============================================================================
// HackerRank: Minimum Absolute Difference in an Array
// Implementation: Initial Monotonic Scan with Buffer Overrun Defect
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log N) where N is the length of arr[cite: 11].
      - std::sort requires O(N log N) time[cite: 11].
      - Linear comparison scan executes in O(N)[cite: 11].
    - Auxiliary Space: O(1) auxiliary memory (modifies vector in-place)[cite: 11].

    Defects & Inefficiencies:
    1. Out-of-Bounds Buffer Read:
       - Loop condition `i < arr.size()` accesses `arr[i + 1]` on the last step[cite: 11],
         reading memory past the buffer allocation boundary (Undefined Behavior)[cite: 11].
       - Must iterate up to `i < arr.size() - 1`[cite: 11].
    2. Redundant Absolute Value Arithmetic:
       - Calling std::abs() is unnecessary because sorting enforces non-decreasing 
         monotonicity (arr[i + 1] >= arr[i])[cite: 11].
    3. Missing Header Dependency:
       - Uses INT_MAX without including <climits>[cite: 11].
*/
// int minimumAbsoluteDifference(std::vector<int> &arr)
// {
//     std::sort(arr.begin(), arr.end());
//     int diff = INT_MAX;

//     for (size_t i = 0; i < arr.size(); i++)
//     {
//         diff = std::min(diff, std::abs(arr[i] - arr[i + 1]));
//     }

//     return diff;
// }