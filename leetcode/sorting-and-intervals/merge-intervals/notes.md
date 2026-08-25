# 56. Merge Intervals

## Core Concept
* Given an array of `intervals` where `intervals[i] = [start_i, end_i]`, merge all overlapping intervals and return an array of non-overlapping intervals covering all inputs.
* **Monotonic Start Invariant:** Sorting the intervals by their start boundary (`a[0] < b[0]`) guarantees that any incoming interval only needs to be checked against the **most recently merged interval** (`merged.back()`).

## Algorithmic Strategy
1. Handle base cases: If `intervals.size() < 2`, return `intervals` immediately.
2. Sort a copy of `intervals` in $\mathcal{O}(N \log N)$ time using a custom lambda comparator: `a[0] < b[0]`.
3. Pre-allocate dynamic output vector memory: `merged.reserve(intervals.size())`.
4. Iterate linearly through `sortedIntervals`:
   * If `merged` is empty OR `merged.back()[1] < interval[0]` (no overlap), push `interval` onto `merged`.
   * Otherwise (overlap detected), extend the upper bound: `merged.back()[1] = std::max(merged.back()[1], interval[1])`.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N \log N)$ — Dominated by `std::sort`. The subsequent sweep over the intervals takes $\mathcal{O}(N)$ linear time.
* **Space Complexity:** $\mathcal{O}(N)$ — Dynamic allocation for `sortedIntervals` and the `merged` output container.