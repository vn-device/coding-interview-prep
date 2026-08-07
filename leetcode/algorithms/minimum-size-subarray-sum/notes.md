# 209. Minimum Size Subarray Sum

## Core Concept
* Finding the minimal length contiguous subarray whose sum is $\ge \text{target}$.
* **Primary Approach:** Variable-size two-pointer sliding window leveraging array positivity (`nums[i]` $\ge 1$) for monotonicity.
* **Follow-up Approach:** Cumulative prefix sums combined with binary search (`std::lower_bound`).

## Algorithmic Strategies

### 1. Dynamic Sliding Window — $O(N)$ Time, $O(1)$ Space
1. **Expansion:** Iterate `rightBound` from $0$ to $N - 1$, accumulating `windowSum += nums[rightBound]`.
2. **Contraction:** While `windowSum >= target`:
   * Update minimum length: `minSubLen = min(minSubLen, rightBound - leftBound + 1)`.
   * Subtract `nums[leftBound++]` from `windowSum`.

### 2. Prefix Sums + Binary Search — $O(N \log N)$ Time, $O(N)$ Space
1. Construct 1-based prefix sum array `prefixSums` of size $N + 1$.
2. Because all numbers are positive, `prefixSums` is strictly increasing (sorted).
3. For each starting index $i$, binary search (`std::lower_bound`) for required prefix value:
   `requiredPrefix = target + prefixSums[i]`
4. If found at iterator `iter`, the subarray length is `(iter - prefixSums.begin()) - i`.

## Complexity Breakdown
| Approach | Time Complexity | Auxiliary Space |
| :--- | :--- | :--- |
| **Two-Pointer Window** | Amortized $O(N)$ | $O(1)$ |
| **Prefix + Binary Search** | $O(N \log N)$ | $O(N)$ |