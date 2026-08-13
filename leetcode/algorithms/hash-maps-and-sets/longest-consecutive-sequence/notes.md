# 128. Longest Consecutive Sequence

## Core Concept
* Find the length of the longest consecutive elements sequence in an unsorted array in **$\mathcal{O}(N)$ time**.
* **Sequence-Starter Invariant:** An element $x$ is the beginning of a consecutive sequence if and only if $x - 1$ is **not** present in the input collection.

## Algorithmic Strategy
1. Populate a `std::unordered_set<int>` with all values from `nums` to enable $\mathcal{O}(1)$ average lookups and automatic deduplication.
2. Iterate through each unique number `num` in the set:
   * Check if `numsTracker.find(num - 1) == numsTracker.end()`.
   * If `num - 1` exists, skip `num` (it belongs to a sequence initiated earlier).
   * If `num - 1` does not exist, initialize `currentStreak = 1` and increment `currentNum` in a `while` loop as long as `numsTracker.find(++currentNum)` succeeds.
3. Track and return `highestStreak`.

## Complexity Breakdown
* **Time Complexity:** Amortized $\mathcal{O}(N)$ — Inserting $N$ elements into `std::unordered_set` takes $\mathcal{O}(N)$ time. Although nested `while` loops exist, each sequence element is touched at most twice across all iterations.
* **Space Complexity:** $\mathcal{O}(N)$ — Auxiliary hash set storage allocated for $N$ elements.