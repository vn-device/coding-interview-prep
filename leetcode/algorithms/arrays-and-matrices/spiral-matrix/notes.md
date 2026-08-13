# 54. Spiral Matrix

## Core Concept
* Return all elements of an $M \times N$ matrix in spiral order.
* **4-Boundary Invariant:** Shrink `topBound`, `botBound`, `leftBound`, and `rightBound` inward sequentially after each perimeter edge traversal until boundaries overlap.

## Algorithmic Strategy
1. Initialize `topBound = 0`, `botBound = M - 1`, `leftBound = 0`, `rightBound = N - 1`.
2. Pre-allocate buffer `sequence.reserve(M * N)`.
3. Execute `while (topBound <= botBound && leftBound <= rightBound)`:
   * **Left $\rightarrow$ Right:** Traverse along `topBound`, then `topBound++`.
   * **Top $\rightarrow$ Bottom:** Traverse down `rightBound`, then `rightBound--`.
   * **Right $\rightarrow$ Left:** If `topBound <= botBound`, traverse along `botBound`, then `botBound--`.
   * **Bottom $\rightarrow$ Top:** If `leftBound <= rightBound`, traverse up `leftBound`, then `leftBound++`.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(M \times N)$ — Visits every matrix cell exactly once.
* **Space Complexity:** $\mathcal{O}(1)$ — Auxiliary memory overhead (excluding output storage).