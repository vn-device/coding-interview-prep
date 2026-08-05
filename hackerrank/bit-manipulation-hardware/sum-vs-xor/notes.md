# Sum vs XOR

## Core Concept
* Exploiting bitwise carry invariants: $n + x = (n \oplus x) + 2(n \text{ AND } x)$. 
* Equality holds if and only if $n \text{ AND } x = 0$, meaning $n$ and $x$ cannot share a set bit (`1`) at any position.

## Algorithmic Strategy
* **Combinatorial Bit Choices:** Every set bit (`1`) in $n$ forces the corresponding bit in $x$ to be `0`. Every unset bit (`0`) in $n$ offers two valid choices (`0` or `1`) for $x$.
* **Bit-Shifting Reduction:** Instead of a linear $\mathcal{O}(n)$ iteration, inspect the significant bits of $n$ right-to-left using bitwise AND (`n & 1`) and right shifts (`n >>= 1`).
* **Power of Two via Left Shift:** Total combinations equal $2^{\text{unset\_bits}}$, calculated in a single clock cycle using `1L << unsetBits`.

## Pitfalls & Edge Cases
* **Zero Boundary:** When $n = 0$, there are zero significant bits, yielding $2^0 = 1$ (since $x = 0$ is the only valid candidate).
* **Integer Limits:** For $n = 10^{15}$, shift operations and loop counters must use 64-bit integer types (`long` / `int64_t`) to prevent bit truncation.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(\log_2 n)$ using bit-shift loop (at most 64 iterations for a 64-bit integer), or $\mathcal{O}(1)$ using CPU intrinsics (`__builtin_clzll` / `POPCNT`).
* **Space Complexity:** $\mathcal{O}(1)$ auxiliary space.