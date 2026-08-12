# 48. Rotate Image

## Core Concept
* Rotate an $N \times N$ 2D matrix 90 degrees clockwise **in-place** (without allocating another $N \times N$ matrix).
* **Linear Algebra Invariant:** A 90-degree clockwise rotation decomposes into two in-place steps:
  1. **Transpose Matrix:** Swap element `matrix[r][c]` with `matrix[c][r]` across the main diagonal.
  2. **Reverse Rows:** Reverse elements horizontally in each row `matrix[r]`.

## Algorithmic Strategy
1. Iterate over the matrix rows $r$ from `0` to $N-1$.
2. For each row, iterate columns $c$ starting from $r + 1$ to $N-1$ (strictly above the diagonal) and execute `std::swap(matrix[r][c], matrix[c][r])`.
3. Iterate through each row in `matrix` and invoke `std::reverse(row.begin(), row.end())`.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N^2)$ — Visits each element twice in an $N \times N$ grid ($N^2$ total cells).
* **Space Complexity:** $\mathcal{O}(1)$ — In-place transformations with zero auxiliary heap allocations.