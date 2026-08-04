# coding-interview-prep

> **Vision:** General technical interview preparation with a focus on systems programming, algorithmic efficiency, and memory optimization — targeting FAANG, HFT, and systems-level engineering roles.

---

## Master Scorecard

| Platform | Domain | Problem | Time Complexity | Space Complexity | Core Concept |
|---|---|---|---|---|---|
| — | — | — | — | — | — |

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
├── hackerrank/             # HackerRank solutions by domain
└── leetcode/               # LeetCode solutions by domain
```