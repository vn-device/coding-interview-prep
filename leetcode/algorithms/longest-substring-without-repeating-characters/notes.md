# 3. Longest Substring Without Repeating Characters

## Core Concept
* Finding the length of the longest contiguous substring containing only unique characters.
* **Sliding Window + Index Mapping:** Track the dynamic character window using two pointers (`leftBound` and `rightBound`) and use a hash table / direct-address lookup to jump `leftBound` instantly when duplicates enter the window.

## Algorithmic Strategy
1. Maintain an array `lastSeen` of size $256$ initialized to $-1$ (mapping ASCII character to its last seen 0-based index).
2. Iterate `rightBound` across the string $0 \dots N - 1$:
   * **Jump Condition:** If `lastSeen[currentChar] >= leftBound`, a duplicate exists within the active window. Move `leftBound = lastSeen[currentChar] + 1`.
   * **Update State:** Record `lastSeen[currentChar] = rightBound`.
   * **Global Record:** Compute $\text{maxLen} = \max(\text{maxLen}, \text{rightBound} - \text{leftBound} + 1)$.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ single pass through string $s$.
* **Space Complexity:** $\mathcal{O}(1)$ auxiliary space ($256$ element direct-address lookup array).