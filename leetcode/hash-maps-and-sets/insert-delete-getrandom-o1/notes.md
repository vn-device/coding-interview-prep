# 380. Insert Delete GetRandom O(1)

## Core Concept
* Design a data structure supporting `insert`, `remove`, and `getRandom` in average $\mathcal{O}(1)$ time.
* **Dual-Structure Invariant:** `std::vector<int>` handles element storage and $\mathcal{O}(1)$ uniform indexing, while `std::unordered_map<int, int>` stores key-to-index mappings (`value -> vector_index`).

## Algorithmic Strategy
1. **`insert(val)`:**
   * If `setDB.find(val) != setDB.end()`, return `false`.
   * Push `val` to `values`.
   * Record `setDB[val] = values.size() - 1` and return `true`.
2. **`remove(val)`:**
   * If `val` is not in `setDB`, return `false`.
   * Retrieve `valIndex = setDB[val]` and `lastVal = values.back()`.
   * Overwrite `values[valIndex] = lastVal` and update `setDB[lastVal] = valIndex`.
   * Execute `values.pop_back()` and `setDB.erase(val)`, then return `true`.
3. **`getRandom()`:**
   * Return `values[rand() % values.size()]`.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(1)$ average per operation.
* **Space Complexity:** $\mathcal{O}(N)$ auxiliary space for $N$ elements across the map and vector.