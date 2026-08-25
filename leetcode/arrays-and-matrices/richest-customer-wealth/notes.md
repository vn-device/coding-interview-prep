# 1672. Richest Customer Wealth

## Core Concept
* Return the maximum wealth among all customers in an $M \times N$ matrix `accounts`.
* **Row Summation Invariant:** Sum all elements in each customer row and track the running maximum scalar.

## Algorithmic Strategy
1. Handle base case: `if (accounts.empty()) return 0;`.
2. Initialize `maxWealth = 0`.
3. Iterate through each row `customer` in `accounts`:
   * Calculate `currentWealth = std::accumulate(customer.begin(), customer.end(), 0)`.
   * Update `maxWealth = std::max(maxWealth, currentWealth)`.
4. Return `maxWealth`.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(M \times N)$ — Visits every matrix element exactly once.
* **Space Complexity:** $\mathcal{O}(1)$ — Auxiliary memory overhead.