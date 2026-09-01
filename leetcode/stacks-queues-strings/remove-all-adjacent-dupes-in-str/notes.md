# 1047. Remove All Adjacent Duplicates In String

## Core Concept
* Continuously remove adjacent, identical character pairs until no duplicates remain.
* **Reduction Invariant:** Removing a duplicate pair causes previously non-adjacent characters to become adjacent. A **Stack** naturally preserves un-eliminated left neighbors to evaluate newly formed duplicates in $\mathcal{O}(1)$ time per character.

## Algorithmic Strategy
1. Initialize a `std::string` as a stack accumulator and reserve `s.length()` capacity up front to avoid heap reallocations.
2. Sweep left-to-right over `s`:
   * If the stack is not empty and `stack.back() == c`, pop the matching character via `stack.pop_back()`.
   * Otherwise, append `c` via `stack.push_back(c)`.
3. Return the populated stack string.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ — Each character is pushed and popped at most once in a single linear pass.
* **Space Complexity:** $\mathcal{O}(N)$ — Auxiliary space required for the output stack in worst-case scenarios with no duplicate pairs (e.g., `"abcdef"`).