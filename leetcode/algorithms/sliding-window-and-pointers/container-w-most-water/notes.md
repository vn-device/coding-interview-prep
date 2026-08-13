# 11. Container With Most Water

## Core Concept
* Finding two lines that together with the x-axis form a container containing the most water.
* **Two-Pointer Greedy Shrinking Window:** Start pointers at opposite ends (`left = 0`, `right = N - 1`) to maximize initial width $(right - left)$.

## Algorithmic Strategy
1. Area is bottlenecked by the shorter line:
   $$\text{Area} = \min(\text{height}[left], \text{height}[right]) \times (right - left)$$
2. At each step in `while (left < right)`:
   * Record $\text{largestArea} = \max(\text{largestArea}, \text{currentArea})$.
   * **Greedy Decision:** Shift whichever pointer references the shorter line. Because width strictly decreases by $1$ at each step, discarding the taller line can never yield a larger area. Only discarding the shorter line allows the possibility of encountering a taller boundary.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ single pass through the array as pointers converge.
* **Space Complexity:** $\mathcal{O}(1)$ auxiliary space for pointer indices.