#include <iostream>
#include <vector>
#include <algorithm>

//---------- Implementation #2 (Monotonic Start Boundary Sorting & Linear Sweep) ----------
/*
    Optimal Strategy: O(N log N) Time | O(N) Auxiliary Space

    Improvements over Implementation #1:

    1. Monotonic Start Sorting Invariant:
       Sorting the input intervals by start boundary (a[0] < b[0]) in O(N log N) time 
       guarantees that for any incoming interval, its start boundary is always greater 
       than or equal to all previously processed intervals.

    2. Single-Pass Adjacent Evaluation:
       Because of the sorted start invariant, an incoming interval can only ever overlap 
       with the most recently merged interval (merged.back()). This reduces the inner 
       lookup loop from O(N) down to a strict O(1) comparison:
         if (merged.back()[1] >= current[0]) -> merged.back()[1] = max(merged.back()[1], current[1])
       This eliminates the chain-reaction failure modes and O(N^2) time complexity of 
       Implementation #1.

    3. Boundary Handling & Heap Pre-Allocation:
       Retains sequence.reserve(intervals.size()) to minimize dynamic array re-allocations, 
       while relying on merged.empty() checks to handle empty/single-element bounds naturally.
*/
std::vector<std::vector<int>> merge(const std::vector<std::vector<int>>& intervals)
{
    if (intervals.size() < 2)
    {
        return intervals;
    }

    std::vector<std::vector<int>> merged;
    merged.reserve(intervals.size());

    std::vector<std::vector<int>> sortedIntervals = intervals;
    std::sort(sortedIntervals.begin(), sortedIntervals.end(),
        [](const std::vector<int> &a, const std::vector<int> &b)
        {
            return a[0] < b[0];
        });

    for (const auto& interval : sortedIntervals)
    {
        if (merged.empty() || merged.back()[1] < interval[0])
        {
            merged.push_back(interval);
        }
        else
        {
            merged.back()[1] = std::max(merged.back()[1], interval[1]);
        }
    }

    return merged;
}

//---------- Implementation #1 (Unsorted Multi-Pass Overlap Scanning) ----------
/*
    Sub-Optimal Strategy: O(N^2) Time | O(N) Auxiliary Space
    Test Case Result: Passed 89 / 172 Cases (Fails on unsorted / wide-bridging intervals)

    1. Algorithmic Approach:
       Pushes intervals into a result vector (merged) sequentially and runs a nested 
       O(N) search over previously stored results to detect partial boundary overlaps.

    2. Failure Modes & Limitations:
       - Out-of-Order Input Failure: Unsorted inputs (e.g., [[2,3],[4,5],[1,10]]) cause 
         late-arriving wide intervals (like [1,10]) to merge with only the first 
         overlapping segment encountered, leaving remaining adjacent blocks fragmented.
       - Chain Reaction Merging: Merging two separate intervals into a single wide block 
         requires updating multiple existing entries in 'merged', which cannot be resolved 
         in a single linear pass without rescanning the entire array.

    3. Refactoring Target (Sorting Invariant):
       Pre-sorting input intervals by start boundary (intervals[i][0]) in O(N log N) time 
       establishes a monotonic start property. This guarantees that overlap checks only 
       ever need to evaluate the most recently added element (merged.back()) in O(N) time.
*/
// std::vector<std::vector<int>> merge(const std::vector<std::vector<int>>& intervals)
// {
//     std::vector<std::vector<int>> merged;
//     merged.reserve(intervals.size());
    
//     if (intervals.size() < 2)
//     {
//         return (intervals.size() == 0) ? merged : intervals;
//     }

//     merged.push_back(intervals[0]);

//     for (size_t i = 1; i < intervals.size(); i++)
//     {
//         int start1 = intervals[i][0];
//         int end1 = intervals[i][1];
//         bool isMerged = false;

//         for (size_t j = 0; j < merged.size(); j++)
//         {
//             int start2 = merged[j][0];
//             int end2 = merged[j][1];
//             int start = std::min(start1, start2);

//             if (end1 >= start2 && end1 <= end2)
//             {                   
//                 merged[j][0] = start;
//                 merged[j][1] = end2;
//                 isMerged = true;
//                 break;
//             }
//             else if (end2 >= start1 && end2 <= end1)
//             {                
//                 merged[j][0] = start;
//                 merged[j][1] = end1;
//                 isMerged = true;
//                 break;
//             }
//         }

//         if (!isMerged)
//         {
//             merged.push_back(intervals[i]);
//         }
//     }

//     return merged;
// }

int main()
{
    // Test Case #1
    std::vector<std::vector<int>> intervals1 = {{1,3},{2,6},{8,10},{15,18}};
    std::vector<std::vector<int>> result1 = merge(intervals1);
    std::cout << "Expected Test #1 Output = [ {1,6} {8,10} {15,18} ]" << std::endl;
    std::cout << "  Actual Test #1 Output = [ ";
    for (std::vector<int>& vals : result1)
    {
        std::cout << "{" << vals[0] << "," << vals[1] << "} ";
    }
    std::cout << "]" << std::endl << std::endl;

    // Test Case #2
    std::vector<std::vector<int>> intervals2 = {{1,4},{4,5}};
    std::vector<std::vector<int>> result2 = merge(intervals2);
    std::cout << "Expected Test #2 Output = [ {1,5} ]" << std::endl;
    std::cout << "  Actual Test #2 Output = [ ";
    for (std::vector<int>& vals : result2)
    {
        std::cout << "{" << vals[0] << "," << vals[1] << "} ";
    }
    std::cout << "]" << std::endl << std::endl;

    // Test Case #3
    std::vector<std::vector<int>> intervals3 = {{4,7},{1,4}};
    std::vector<std::vector<int>> result3 = merge(intervals3);
    std::cout << "Expected Test #3 Output = [ {1,7} ]" << std::endl;
    std::cout << "  Actual Test #3 Output = [ ";
    for (std::vector<int>& vals : result3)
    {
        std::cout << "{" << vals[0] << "," << vals[1] << "} ";
    }
    std::cout << "]" << std::endl << std::endl;

    // Test Case #4
    std::vector<std::vector<int>> intervals4 = {{2,3},{4,5},{6,7},{8,9},{1,10}};
    std::vector<std::vector<int>> result4 = merge(intervals4);
    std::cout << "Expected Test #4 Output = [ {1,10} ]" << std::endl;
    std::cout << "  Actual Test #4 Output = [ ";
    for (std::vector<int>& vals : result4)
    {
        std::cout << "{" << vals[0] << "," << vals[1] << "} ";
    }
    std::cout << "]" << std::endl << std::endl;

    return 0;
}