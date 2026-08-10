# 2011. Final Value of Variable After Performing Operations

## Core Concept
* Given an array of operation strings (`"++X"`, `"X++"`, `"--X"`, `"X--"`), determine the final integer result starting from 0.
* **Middle-Character Invariant:** All operation strings are fixed length (3 characters). Regardless of prefix or postfix notation, the character at index 1 (`op[1]`) uniquely identifies the operation (`'+'` or `'-'`).

## Algorithmic Strategy
1. Initialize `result = 0`.
2. Iterate through `operations` using a range-based `const std::string&` loop to avoid heap allocations/string copies.
3. Inspect `op[1]`:
   * If `op[1] == '+'`, increment `result`.
   * Otherwise, decrement `result`.
4. Return `result`.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ — Single pass through $N$ operation strings, doing an $\mathcal{O}(1)$ character check per element.
* **Space Complexity:** $\mathcal{O}(1)$ — Zero auxiliary space allocated beyond a loop counter.