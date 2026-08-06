# 560. Subarray Sum Equals K

## Core Concept
* Finding the number of contiguous subarrays that sum to $k$ using **Cumulative Prefix Sums** and a **Hash Map Frequency Tracker**.
* Contiguous subarray sum identity: $\text{Sum}(i, j) = \text{PrefixSum}[j] - \text{PrefixSum}[i-1]$.

## Algorithmic Strategy
1. **Mathematical Invariant:** To find a contiguous subarray ending at index $j$ that sums to $k$:
   $$\text{PrefixSum}[j] - \text{PrefixSum}[i-1] = k \implies \text{PrefixSum}[i-1] = \text{PrefixSum}[j] - k$$
2. **Frequency Map Tracking:** Maintain `unordered_map<int, int>` mapping `<prefixSum, frequency>`.
3. **Base Case:** Initialize `sumTracker[0] = 1` to account for valid subarrays starting at index $0$ where $\text{runningSum} == k$.
4. **Single-Pass Evaluation:**
   * Compute `runningSum += nums[j]`.
   * Look up `target = runningSum - k` in the map.
   * Add `sumTracker[target]` to total count.
   * Increment `sumTracker[runningSum]`.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ amortized single-pass array iteration with $\mathcal{O}(1)$ average hash map lookups.
* **Space Complexity:** $\mathcal{O}(N)$ auxiliary memory for up to $N + 1$ unique prefix sums in `std::unordered_map`.