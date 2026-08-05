# Largest Rectangle

## Core Concept
* Finding the largest rectangular area in a histogram using a **Monotonic Increasing Stack**.
* Each building's maximum rectangular expansion is bounded by the first shorter building to its left and the first shorter building to its right.

## Algorithmic Strategy
1. **Index-Based Monotonic Stack:** Store indices on `std::stack<int>` rather than raw heights to preserve positional boundary information.
2. **Right-Boundary Invariant:** When iterating through index $i$, if $h[i] < h[\text{top}]$, $i$ serves as the **strict right boundary** for the bar at `stack.top()`.
3. **Left-Boundary Invariant:** After popping the target height, the new element at `stack.top()` represents the **strict left boundary** (first shorter element to the left).
4. **Width Formula:** $\text{Width} = \text{rightBound} - \text{leftBound} - 1$.
5. **Two-Pass Invariant Execution:**
   * **Pass 1 (Main Loop):** Resolves bars whose rightward expansion is interrupted by shorter bars.
   * **Pass 2 (Cleanup Sweep):** Resolves remaining stack elements whose rightward expansion extended uninhibited to the far right end of the histogram ($N$).

## Memory & Hardware Mechanics
* **Amortized $\mathcal{O}(N)$ Work:** Every element index is pushed onto `std::stack` exactly once and popped at most once.
* **Pass-by-Reference Optimization:** Taking `const vector<int>&` prevents buffer copy overhead on the execution stack frame.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ linear time.
* **Space Complexity:** $\mathcal{O}(N)$ auxiliary space for the stack container.