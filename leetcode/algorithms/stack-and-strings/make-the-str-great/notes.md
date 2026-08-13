# 1544. Make The String Great

## Core Concept
* Given a string `s`, continuously remove adjacent pairs where the same letter exists in both lower and upper case (e.g., `'a'` and `'A'`).
* **ASCII Invariant:** The distance between any uppercase ASCII character and its corresponding lowercase equivalent is exactly `32` (`'a' - 'A' = 97 - 65 = 32`).
* A **Stack** naturally preserves un-eliminated left neighbors to detect newly adjacent valid pairs in $\mathcal{O}(1)$ time.

## Algorithmic Strategy
1. Initialize a `std::string` as a stack accumulator and reserve `s.length()` capacity up front to prevent heap reallocations.
2. Sweep left-to-right over `s`:
   * If the stack is not empty and `std::abs(stack.back() - c) == 32`, pop the top element via `stack.pop_back()`.
   * Otherwise, push `c` onto the stack via `stack.push_back(c)`.
3. Return the processed stack string.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ — Single pass over `s`. Push and pop operations run in $\mathcal{O}(1)$ time.
* **Space Complexity:** $\mathcal{O}(N)$ — Auxiliary space used for the output stack in worst-case scenarios where no character pairs trigger elimination.