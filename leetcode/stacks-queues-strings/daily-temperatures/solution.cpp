#include <vector>

//==============================================================================
// LeetCode #739: Daily Temperatures
// Strategy: Monotonic Decreasing Index Stack (Next Greater Element)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) amortized where N = temperatures.size().
      - Each index is pushed onto the stack exactly once.
      - Each index is popped from the stack at most once across the entire traversal.
      - Total amortized loop evaluations are bounded by 2N operations.
    - Auxiliary Space: O(N) auxiliary memory.
      - 'answer' vector occupies O(N) space to store resulting day offsets.
      - 'stack' stores up to N unresolved indices in the worst-case (strictly non-increasing stream).
      - Uses a contiguous std::vector<int> buffer with reserve() to avoid segmented deque allocations.

    Algorithmic & Structural Invariants:
    1. Monotonic Decreasing Invariant:
       - The stack stores indices whose corresponding values in 'temperatures' are 
         strictly non-increasing from bottom to top:
         temperatures[stack[k]] >= temperatures[stack[k + 1]].
    2. Event-Driven Resolution:
       - Encountering any temperature greater than the top of the stack triggers resolution 
         for all cooler preceding days, recording the index delta (current - previous) directly.
    3. Default Sentinel Initialization:
       - Sizing the result vector with default zero values ('answer(n, 0)') automatically 
         satisfies the requirement for days that never encounter a subsequent warmer temperature, 
         eliminating a terminal cleanup pass over remaining stack elements.
*/
std::vector<int> dailyTemperatures(const std::vector<int> &temperatures)
{
    const int n = static_cast<int>(temperatures.size());
    std::vector<int> answer(n, 0);

    // Monotonic stack storing indices of unresolved temperatures
    std::vector<int> stack;
    stack.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        // Resolve past cooler days using the incoming warmer temperature
        while (!stack.empty() && temperatures[i] > temperatures[stack.back()])
        {
            const int prevIndex = stack.back();
            stack.pop_back();
            answer[prevIndex] = i - prevIndex;
        }

        stack.push_back(i);
    }

    return answer;
}