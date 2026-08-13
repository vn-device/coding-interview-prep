# 811. Subdomain Visit Count

## Core Concept
* Aggregate visit counts across parent and child subdomains provided in formatted string pairs (e.g., `"9001 discuss.leetcode.com"`).
* **Hash Table Aggregation:** Use `std::unordered_map<std::string, int>` to maintain cumulative counts per unique domain string.
* **String Index Invariants:** Parse visit count and base domain via `std::string::find(' ')` to avoid standard I/O stream (`std::stringstream`) overhead.

## Algorithmic Strategy
1. Initialize an `std::unordered_map<std::string, int>` for accumulation.
2. For each string in `cpdomains`:
   * Locate the space delimiter `spacePos` using `find(' ')`.
   * Extract count via `std::stoi(entry.substr(0, spacePos))`.
   * Extract domain via `entry.substr(spacePos + 1)`.
   * Increment `domainCounts[domain] += count`.
   * Iteratively search for period delimiters `find('.', dotPos + 1)` and increment counts for extracted subdomains `domain.substr(dotPos + 1)`.
3. Construct the output vector by iterating over the map and formatting entries as `count + " " + domain`.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ — Single pass over input strings where $N$ represents total character length across all domain representations.
* **Space Complexity:** $\mathcal{O}(N)$ — Auxiliary storage required for unique domain entries in the hash table and output result vector.