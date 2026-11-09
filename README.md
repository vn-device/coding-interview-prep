# coding-interview-prep

> **Vision:** General technical interview preparation with a focus on systems programming, algorithmic efficiency, and memory optimization — targeting FAANG, HFT, and systems-level engineering roles.

---

## Master Scorecard

| Platform | Domain | Problem | Time Complexity | Space Complexity | Core Concept |
| :--- | :--- | :--- | :--- | :--- | :--- |
| NeetCode | Arrays & Hashing | [Contains Duplicate]() | $O(N)$ | $O(N)$ | Single-pass insertion status verification using reserved std::unordered_set |
| NeetCode | Arrays & Hashing | [Valid Anagram]() | $O(N)$ | $O(1)$ | Stack-allocated 26-element array with net delta frequency tracking |
| NeetCode | Arrays & Hashing | [Two Sum]() | $O(N)$ | $O(N)$ | Single-pass complement lookup with pre-reserved std::unordered_map |
| NeetCode | Arrays & Hashing | [Group Anagrams]() | $O(N \cdot K)$ | $O(N \cdot K)$ | 26-element frequency serialization with zero-copy move transfer |
| NeetCode | Arrays & Hashing | [Top K Frequent Elements]() | $O(N)$ | $O(N)$ | Bucket distribution indexed by frequency with dynamic early termination |
| NeetCode | Arrays & Hashing | [Encode and Decode Strings]() | $O(N)$ | $O(1)$ | Length-prefixed framing with std::from_chars zero-copy deserialization |
| NeetCode | Arrays & Hashing | [Product of Array Except Self]() | $O(N)$ | $O(1)$ | Two-pass in-place prefix/suffix scalar accumulation |
| NeetCode | Arrays & Hashing | [Valid Sudoku]() | $O(1)$ | $O(1)$ | Direct-address table using fixed 2D boolean matrices (`seenRow[9][10]`, `seenCol[9][10]`, `seenBox[9][10]`) over constant 81 cells; avoids dynamic heap containers and bitwise shifts with 270 bytes on the stack. |
| NeetCode | Arrays & Hashing | [Longest Consecutive Sequence]() | $O(N)$ | $O(N)$ | Full hash set pre-population with sequence-head (num - 1) lookup ensuring each element is traversed at most twice. |
| NeetCode | Stack | [Valid Parentheses]() | $O(N)$ | $O(N)$ | Parity pre-check with push-expected closing symbol stack matching over contiguous std::vector<char> buffer. |
| NeetCode | Stack | [Min Stack]() | $O(1)$ all ops | $O(N)$ | Synchronized parallel LIFO buffer tracking running prefix minimum per stack frame depth. |
| NeetCode | Stack | [Evaluate Reverse Polish Notation]() | $O(N)$ | $O(N)$ | Postfix stream parsing using reserved vector stack with in-place top-of-stack scalar mutation. |
| NeetCode | Stack | [Daily Temperatures]() | $O(N)$ | $O(N)$ | Monotonic decreasing index stack using pre-reserved `std::vector<int>`; resolves next warmer day in amortized $O(1)$ per pop with contiguous cache residency. |

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
│   └── NOTE_TEMPLATE.md    # Standardised problem note template
├── README.md               # This file
├── extra-help.md           # Supplementary reference notes
├── hackerrank/             # HackerRank solutions by domain
└── leetcode/               # LeetCode solutions by domain
└── neetcode-roadmap/       # NeetCode solutions by domain
```