# 121. Best Time to Buy and Sell Stock

## Core Concept
* Find the maximum profit achievable by buying on one day and selling on a future day in an array of `prices`.
* **Running Minimum Invariant:** The maximum profit obtainable on day $i$ is guaranteed to be $prices[i] - \min(prices[0 \dots i])$.

## Algorithmic Strategy
1. Initialize `maxProfit = 0` and `minPrice = INT_MAX`.
2. Iterate through each `price` in `prices`:
   * Update `minPrice = std::min(minPrice, price)`.
   * Calculate current day profit: `currentProfit = price - minPrice`.
   * Update global maximum: `maxProfit = std::max(maxProfit, currentProfit)`.
3. Return `maxProfit`.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ — Single pass through the `prices` array.
* **Space Complexity:** $\mathcal{O}(1)$ — Scalar storage for `minPrice` and `maxProfit`.