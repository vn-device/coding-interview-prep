# 53. Maximum Subarray

## Core Concept
* Finding the maximum sum of a contiguous subarray using **Kadane's Algorithm**.
* Dynamic decision invariant: At any index $i$, decide whether to extend the previous contiguous sum or reset the window and start fresh at $\text{nums}[i]$.

## Algorithmic Strategy
1. **Reset Condition:** A negative prefix sum decreases the sum of any subsequent contiguous subarray.
2. **Local Optimal Transition:**
   $$\text{currentSum} = \max(\text{nums}[i], \text{currentSum} + \text{nums}[i])$$
3. **Global Tracking:** Update $\text{maxSum} = \max(\text{maxSum}, \text{currentSum})$ at each step.
4. **Single-Pass Execution:** Loop runs from index $1$ to $N-1$ with base initialization at index $0$.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ single pass through array `nums`.
* **Space Complexity:** $\mathcal{O}(1)$ scalar space (`currentSum` and `maxSum`).