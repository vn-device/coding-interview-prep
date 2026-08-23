#include <vector>
#include <algorithm>
#include <array>

//==============================================================================
// LeetCode #621: Task Scheduler
// Strategy: Greedy Chunk Partitioning & Idle Slot Fill Invariant
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = tasks.size().
      - Single-pass frequency accumulation in O(N).
      - Single-pass O(Σ) = O(26) = O(1) mode reduction.
    - Auxiliary Space: O(1) auxiliary stack space (104 bytes).
      - Zero dynamic heap memory allocations.

    Mathematical Proof & Invariants:
    1. Frame Partitioning:
       - Let maxFreq be the maximum frequency of any task.
       - These tasks create (maxFreq - 1) full chunks/frames.
       - Each frame requires (n + 1) execution slots to maintain cooling distance n.
    2. Mode Multiplicity:
       - If multiple distinct tasks share the maximum frequency (maxFreqCount tasks), 
         each such task occupies one slot in the final trailing chunk.
       - Formula: frameSlots = (maxFreq - 1) * (n + 1) + maxFreqCount.
    3. Saturation Invariant:
       - If tasks.size() > frameSlots, there are enough distinct tasks to fill all 
         idle gaps without extending the schedule. The answer is simply tasks.size().
       - Final Result = max(tasks.size(), frameSlots).
*/
int leastInterval(std::vector<char>& tasks, int n)
{
    // Direct-mapped 26-bucket stack histogram
    std::array<int, 26> freq{};
    for (char c : tasks)
    {
        freq[c - 'A']++;
    }

    int maxFreq = 0;
    int maxFreqCount = 0;

    // Single-pass extraction of max frequency and mode multiplicity
    for (int count : freq)
    {
        if (count > maxFreq)
        {
            maxFreq = count;
            maxFreqCount = 1;
        }
        else if (count == maxFreq && count > 0)
        {
            maxFreqCount++;
        }
    }

    // Closed-form lower bound vs total task saturation
    const int frameSlots = (maxFreq - 1) * (n + 1) + maxFreqCount;
    return std::max(static_cast<int>(tasks.size()), frameSlots);
}

//==============================================================================
// LeetCode #621: Task Scheduler
// Implementation: Direct Histogram with STL Reductions (0 ms, Beats 100.00%)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = tasks.size().
      - Linear pass over input tasks vector to populate direct frequency table.
      - Two consecutive 26-element sweeps via std::max_element and std::count.
    - Auxiliary Space: O(1) auxiliary stack space.
      - Fixed-size 26-element std::array<int, 26> on the call stack (104 bytes).
      - 0 heap allocations.

    Implementation Notes:
    1. Direct-Offset Mapping:
       - Uses (c - 'A') offset mapping to track uppercase ASCII tasks in O(1) time.
    2. Closed-Form Frame Invariant:
       - Computes minimum execution units by projecting frames of size (n + 1) 
         anchored by the most frequent task.
    3. Multi-Pass Array Iteration:
       - Performs two sequential STL reductions across taskFreq; can be unified 
         into a single linear loop over the 26 buckets.
*/
// int leastInterval(std::vector<char> &tasks, int n)
// {
//     std::array<int, 26> taskFreq{};
//     for (char c : tasks)
//     {
//         taskFreq[c - 'A']++;
//     }

//     int maxFreq = *(std::max_element(taskFreq.begin(), taskFreq.end()));
//     int maxFreqCount = std::count(taskFreq.begin(), taskFreq.end(), maxFreq);
//     int minTime = std::max(static_cast<int>(tasks.size()), (maxFreq - 1) * (n + 1) + maxFreqCount);

//     return minTime;
// }