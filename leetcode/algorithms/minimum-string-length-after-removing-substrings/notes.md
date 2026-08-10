# 2696. Minimum String Length After Removing Substrings

## Core Concept
* Given a string `s`, repeatedly remove any occurrences of `"AB"` or `"CD"` until no more removals are possible.
* Return the minimum length of the remaining string.
* **Reduction Invariant:** When a target pair is removed, previously non-adjacent characters become adjacent. A **Stack** naturally maintains the context of un-eliminated characters to process reductions in a single pass.

## Algorithmic Strategy
1. Initialize an auxiliary `string` to act as a stack. Reserve capacity equal to `s.length()`.
2. Iterate through each character `c` in string `s`:
   * If the stack is not empty and the top of the stack forms a valid pair with `c` (`"AB"` or `"CD"`), pop the top element via `stack.pop_back()`.
   * Otherwise, push `c` onto the stack via `stack.push_back(c)`.
3. Return the final length of the stack string.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ — Each character is pushed onto and popped from the stack at most once in a single linear pass.
* **Space Complexity:** $\mathcal{O}(N)$ — Auxiliary space required for the stack accumulator in the worst-case scenario where no character eliminations occur.