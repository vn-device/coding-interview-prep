# 49. Group Anagrams

## Core Concept
* Group array of strings `strs` into anagram subsets.
* **Canonical Key Invariant:** All anagrams share the exact same character sequence when sorted lexicographically (e.g., `"eat"`, `"tea"`, `"ate"` $\rightarrow$ `"aet"`).

## Algorithmic Strategy
1. Initialize `std::unordered_map<std::string, std::vector<std::string>> anagramGroups`.
2. Reserve bucket capacity with `anagramGroups.reserve(strs.size())`.
3. For each string `word` in `strs`:
   * Copy `word` into key variable `key`.
   * Sort `key` using `std::sort(key.begin(), key.end())`.
   * Push `word` into `anagramGroups[key]`.
4. Extract vectors from map into final output vector using move semantics `std::move(pair.second)`.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N \cdot K \log K)$ — Where $N$ is the number of strings and $K$ is the maximum length of a string. Sorting each string takes $\mathcal{O}(K \log K)$, executed $N$ times.
* **Space Complexity:** $\mathcal{O}(N \cdot K)$ — Storage required for $N$ strings of length $K$ stored inside the hash map buckets.