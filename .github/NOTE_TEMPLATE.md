# Problem Note Template

**Platform:** <!-- LeetCode | HackerRank | Other -->  
**Problem:** <!-- Problem name and link -->  
**Difficulty:** <!-- Easy | Medium | Hard -->  
**Date:** <!-- YYYY-MM-DD -->  

---

## Core Concept

<!-- What is the fundamental data structure or algorithm technique at play?
     Examples: monotonic stack, sliding window, union-find, segment tree, two-pointer. -->

---

## Algorithmic Strategy & Trade-offs

<!-- Describe the chosen approach and why it was selected over alternatives.
     Address relevant systems-level considerations where applicable: -->

- **Approach chosen:**  
  <!-- e.g., Bottom-up DP with rolling array vs. top-down memoisation -->

- **L1 cache locality:**  
  <!-- Does the access pattern iterate contiguously through memory?
       Row-major vs. column-major traversal, SoA vs. AoS layout implications. -->

- **Stack vs. heap allocations:**  
  <!-- Are temporary buffers stack-allocated (fixed size, zero-cost teardown) or
       heap-allocated (flexible, but malloc/free overhead + potential fragmentation)? -->

- **Time-space trade-off:**  
  <!-- e.g., precomputing a prefix-sum array trades O(n) space for O(1) range queries. -->

- **Alternative approaches considered:**  
  <!-- List alternatives and why they were rejected. -->

---

## Pitfalls & Edge Cases

<!-- Document non-obvious failure modes. Common categories: -->

- **Integer overflow:**  
  <!-- e.g., multiplying two int32_t values that individually fit but whose product
       exceeds 2^31 - 1. Mitigation: cast to int64_t / use uint64_t. -->

- **Dangling pointers / iterator invalidation:**  
  <!-- e.g., storing a pointer into a std::vector and then calling push_back,
       which may reallocate and invalidate the pointer. -->

- **Off-by-one errors:**  
  <!-- e.g., loop bound should be < n vs. <= n; half-open interval conventions. -->

- **Empty input / single element:**  
  <!-- Does the algorithm degenerate or invoke undefined behaviour on size-0 or size-1 input? -->

- **Signed vs. unsigned comparison:**  
  <!-- Comparing int and size_t (unsigned) silently promotes int to unsigned,
       causing wrap-around bugs when int is negative. -->

---

## Complexity Breakdown

| Dimension | Complexity | Notes |
|---|---|---|
| Time | $O(?)$ | <!-- Dominant term and reasoning --> |
| Space | $O(?)$ | <!-- Auxiliary space excluding input --> |

<!-- Example derivation:
     Outer loop: O(n). Inner loop: amortised O(1) due to each element pushed/popped at most once.
     Total: O(n) time, O(n) auxiliary space for the stack. -->

---

## Solution Sketch

```cpp
#include <cstdint>
// Add further includes as needed.

// Solution using Allman (BSD) bracing style with explicit standard types.
class Solution
{
public:
    // TODO: replace with actual return type and parameters
    void solve()
    {

    }
};
```
