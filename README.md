# coding-interview-prep

> **Vision:** General technical interview preparation with a focus on systems programming, algorithmic efficiency, and memory optimization — targeting FAANG, HFT, and systems-level engineering roles.

---

## Master Scorecard

| Platform | Domain | Problem | Time Complexity | Space Complexity | Core Concept |
| :--- | :--- | :--- | :--- | :--- | :--- |
| HackerRank | Bit Manipulation & Hardware | [Sum vs XOR](hackerrank/bit-manipulation-hardware/sum-vs-xor/) | $O(\log_2 n)$ | $O(1)$ | Bitwise carry identity ($n \text{ AND } x = 0$) and `2^unset_bits` shift optimization |
| HackerRank | C++ Systems Architecture | [Attribute Parser](hackerrank/cpp-systems-architecture/attribute-parser/) | $O(N \cdot L + Q)$ | $O(N \cdot A)$ | Stack-based path scope serialization and $O(1)$ map lookup |
| HackerRank | Data Structures & Buffers | [Jesse and Cookies](hackerrank/data-structures-and-buffers/jesse-and-cookies/) | $O(N \log N)$ | $O(N)$ | Min-heap (`std::priority_queue`) dynamic order tracking via Floyd's construction |
| HackerRank | Data Structures & Buffers | [Largest Rectangle](hackerrank/data-structures-and-buffers/largest-rectangle/) | $O(N)$ | $O(N)$ | Amortized $O(N)$ monotonic stack boundary traversal |
| HackerRank | Data Structures & Buffers | [Making Anagrams](hackerrank/data-structures-and-buffers/making-anagrams/) | $O(N + M)$ | $O(1)$ | Dual-string frequency delta accumulation via symmetric absolute difference |
| LeetCode | Arrays & Matrices | [Maximum Subarray](leetcode/algorithms/arrays-and-matrices/maximum-subarray/) | $O(N)$ | $O(1)$ | Kadane's Algorithm local reset state invariant |
| LeetCode | Arrays & Matrices | [Product of Array Except Self](leetcode/algorithms/arrays-and-matrices/product-of-array-except-self/) | $O(N)$ | $O(1)$ | Two-pass prefix/suffix accumulation using output space and a running right product scalar |
| LeetCode | Arrays & Matrices | [Richest Customer Wealth](leetcode/algorithms/arrays-and-matrices/1672-richest-customer-wealth/) | $O(M \times N)$ | $O(1)$ | Single-pass row aggregation & maximum value tracking |
| LeetCode | Arrays & Matrices | [Rotate Image](leetcode/algorithms/arrays-and-matrices/rotate-image/) | $O(N^2)$ | $O(1)$ | In-place matrix transformation via main diagonal transpose and row reversal |
| LeetCode | Arrays & Matrices | [Spiral Matrix](leetcode/algorithms/arrays-and-matrices/spiral-matrix/) | $O(M \times N)$ | $O(1)$ | 4-boundary inward shrinking grid traversal |
| LeetCode | Arrays & Matrices | [Subarray Sum Equals K](leetcode/algorithms/arrays-and-matrices/subarray-sum-equals-k/) | $O(N)$ | $O(N)$ | Cumulative prefix sum identity and `std::unordered_map` frequency tracking |
| LeetCode | Hash Maps & Sets | [Group Anagrams](leetcode/algorithms/hash-maps-and-sets/group-anagrams/) | $O(N \cdot K \log K)$ | $O(N \cdot K)$ | Hash map bucket aggregation using sorted string canonical keys |
| LeetCode | Hash Maps & Sets | [Insert Delete GetRandom O(1)](leetcode/algorithms/hash-maps-and-sets/0380-insert-delete-getrandom-o1/) | $O(1)$ | $O(N)$ | Dual-structure synchronization (`unordered_map` index lookup + vector back-swap deletion) |
| LeetCode | Hash Maps & Sets | [Longest Consecutive Sequence](leetcode/algorithms/hash-maps-and-sets/longest-consecutive-sequence/) | $O(N)$ | $O(N)$ | Amortized linear set traversal via sequence-starter identification |
| LeetCode | Hash Maps & Sets | [Ransom Note](leetcode/algorithms/hash-maps-and-sets/0383-ransom-note/) | $O(M + N)$ | $O(1)$ | Direct-address frequency inventory decrement with early deficit pruning |
| LeetCode | Hash Maps & Sets | [Subdomain Visit Count](leetcode/algorithms/hash-maps-and-sets/subdomain-visit-count/) | $O(N)$ | $O(N)$ | Hash table aggregation with string index domain slicing |
| LeetCode | Hash Maps & Sets | [Valid Anagram](leetcode/algorithms/hash-maps-and-sets/valid-anagram/) | $O(N)$ | $O(1)$ | Direct-mapped 26-element stack frequency delta balancing |
| LeetCode | Sliding Window & Pointers | [Container With Most Water](leetcode/algorithms/sliding-window-and-pointers/container-w-most-water/) | $O(N)$ | $O(1)$ | Two-pointer greedy shrinking window bottlenecked by shorter height |
| LeetCode | Sliding Window & Pointers | [Find All Anagrams in a String](leetcode/algorithms/sliding-window-and-pointers/find-all-anagrams-in-a-string/) | $O(\|S\|)$ | $O(1)$ | Fixed-size sliding window with incremental direct-mapped frequency delta tracking |
| LeetCode | Sliding Window & Pointers | [Longest Substring Without Repeating Characters](leetcode/algorithms/sliding-window-and-pointers/longest-substring-without-repeating-characters/) | $O(N)$ | $O(1)$ | Dynamic sliding window & character last-seen direct-address index jumping |
| LeetCode | Sliding Window & Pointers | [Minimum Size Subarray Sum](leetcode/algorithms/sliding-window-and-pointers/minimum-size-subarray-sum/) | $O(N)$ | $O(1)$ | Variable sliding window monotonicity & prefix sum binary search follow-up |
| LeetCode | Sorting & Intervals | [Best Time to Buy and Sell Stock](leetcode/algorithms/sorting-and-intervals/0121-best-time-to-buy-and-sell-stock/) | $O(N)$ | $O(1)$ | Single-pass linear scan with running minimum tracking |
| LeetCode | Sorting & Intervals | [Maximize Sum Of Array After K Negations](leetcode/algorithms/sorting-and-intervals/1005-maximize-sum-of-array-after-k-negations/) | $O(N \log N)$ | $O(1)$ | Greedy sorting with sign-inversion saturation and parity reduction |
| LeetCode | Sorting & Intervals | [Merge Intervals](leetcode/algorithms/sorting-and-intervals/merge-intervals/) | $O(N \log N)$ | $O(N)$ | Monotonic start boundary sorting & linear sweep interval consolidation |
| LeetCode | Sorting & Intervals | [Simple Bank System](leetcode/algorithms/sorting-and-intervals/2043-simple-bank-system/) | $O(1)$ per op | $O(N)$ | State simulation & transaction boundary validation |
| LeetCode | Sorting & Intervals | [Assign Cookies](leetcode/algorithms/sorting-and-intervals/0455-assign-cookies/) | $O(M \log M + N \log N)$ | $O(1)$ | Dual-array greedy sorting with two-pointer greed-cookie matching |
| LeetCode | Stack & Strings | [Asteroid Collision](leetcode/algorithms/stack-and-strings/asteroid-collision/) | $O(N)$ | $O(N)$ | Stack accumulator pattern with directional magnitude collision simulation |
| LeetCode | Stack & Strings | [Final Value of Variable After Performing Operations](leetcode/algorithms/stack-and-strings/final-value-of-variable-after-performing-operations/) | $O(N)$ | $O(1)$ | Single-pass string parsing using middle-character invariant (`op[1]`) |
| LeetCode | Stack & Strings | [Make The String Great](leetcode/algorithms/stack-and-strings/make-the-str-great/) | $O(N)$ | $O(N)$ | String stack accumulator with ASCII distance check (`abs(diff) == 32`) for case-mismatched pair elimination |
| LeetCode | Stack & Strings | [Minimum String Length After Removing Substrings](leetcode/algorithms/stack-and-strings/minimum-string-length-after-removing-substrings/) | $O(N)$ | $O(N)$ | Stack accumulator pattern for linear adjacent character pair reduction |
| LeetCode | Stack & Strings | [Number of Different Integers in a String](leetcode/algorithms/stack-and-strings/number-of-different-ints-in-a-string/) | $O(N)$ | $O(N)$ | String parsing with inline leading-zero normalization and hash set deduplication |
| LeetCode | Stack & Strings | [Remove All Adjacent Duplicates In String](leetcode/algorithms/stack-and-strings/remove-all-adjacent-dupes-in-str/) | $O(N)$ | $O(N)$ | Single-pass string stack accumulator for adjacent duplicate elimination |

---

## High-Yield C++ Systems & Performance Cheatsheet

### Erase-Remove Idiom

Remove elements matching a predicate from a `std::vector` without leaving gaps.

```cpp
#include <algorithm>
#include <vector>
#include <cstdint>

void remove_evens(std::vector<uint32_t>& v)
{
    v.erase(
        std::remove_if(v.begin(), v.end(),
            [](uint32_t x) { return x % 2 == 0; }),
        v.end()
    );
}
```

> **Why it matters:** A naïve loop with `erase()` inside is $O(n^2)$. The erase-remove idiom is $O(n)$ because `std::remove_if` compacts in one pass, and `erase` truncates in $O(1)$ amortised.

---

### Fast I/O

Eliminate synchronisation between C and C++ I/O streams to unlock near-`scanf` throughput.

```cpp
#include <iostream>

void setup_fast_io()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
}
```

> **Rule:** Call both lines once at the start of `main`. Never mix `printf`/`scanf` with `std::cin`/`std::cout` after doing this.

---

### Cache Locality Rules

Keep hot data contiguous in memory to minimise L1/L2 cache misses.

```cpp
#include <cstdint>
#include <vector>

// PREFER: Structure-of-Arrays (SoA) for SIMD-friendly iteration
struct Particles
{
    std::vector<float> x;
    std::vector<float> y;
    std::vector<float> vx;
    std::vector<float> vy;
};

// AVOID for bulk processing: Array-of-Structures (AoS) scatters fields
struct Particle
{
    float x, y, vx, vy;
};
// std::vector<Particle> particles; // Each field 4 bytes apart per object
```

> **Rule:** Prefer SoA when iterating over a single field across many objects (e.g., integrating positions). Prefer AoS when all fields of one object are accessed together.

---

### Const-Correctness

Express immutability in function signatures to prevent accidental mutation and enable compiler optimisations.

```cpp
#include <cstdint>
#include <string>

// Pass large objects by const reference — zero copy, compiler-enforced read-only
uint64_t compute_hash(const std::string& key);

// Mark member functions that do not mutate state
class Cache
{
public:
    bool contains(const std::string& key) const;  // const member: cannot modify *this
    void insert(const std::string& key, uint64_t value);
};
```

> **Rule:** Default to `const`. Remove it only when mutation is explicitly required.

---

### Branchless Bit Logic

Replace branch-heavy conditional logic with bitwise operations to avoid CPU branch-misprediction penalties.

```cpp
#include <cstdint>

// Branchless absolute value for signed 32-bit integer
int32_t abs_branchless(int32_t x)
{
    int32_t mask = x >> 31;          // arithmetic right shift: all 0s or all 1s
    return (x ^ mask) - mask;
}

// Branchless min — avoids conditional branch entirely
int32_t min_branchless(int32_t a, int32_t b)
{
    return b + ((a - b) & ((a - b) >> 31));
}

// Check if integer is a power of two
bool is_power_of_two(uint32_t n)
{
    return n != 0 && (n & (n - 1)) == 0;
}
```

> **Why it matters:** Modern CPUs speculatively execute branches; a misprediction costs ~15–20 cycles. Branchless idioms guarantee a single execution path at the cost of slightly more arithmetic — net win for unpredictable data.

---

## Repository Layout

```
coding-interview-prep/
├── .github/
│   └── NOTE_TEMPLATE.md   # Standardised problem note template
├── README.md               # This file
├── extra-help.md           # Supplementary reference notes
├── hackerrank/             # HackerRank solutions by domain
└── leetcode/               # LeetCode solutions by domain
```