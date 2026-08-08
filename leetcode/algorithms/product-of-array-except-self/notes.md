# 238. Product of Array Except Self

## Core Concept
* Calculate an array where each index $i$ contains the product of all elements in `nums` except `nums[i]`.
* **Constraint:** Must run in $\mathcal{O}(N)$ time without using the division operator.
* **Decomposition Strategy:** Break total product into prefix (left) product and suffix (right) product:
  $$\text{answer}[i] = \text{prefixProduct}[i] \times \text{suffixProduct}[i]$$

## Algorithmic Strategy
1. **Left Accumulation Pass:** Initialize `answer` vector of size $N$ with `answer[0] = 1`. Iterate $i = 1 \dots N-1$:
   $$\text{answer}[i] = \text{answer}[i-1] \times \text{nums}[i-1]$$
2. **Right Accumulation Pass:** Maintain a scalar `rightProduct = 1`. Iterate backwards $i = N-1 \dots 0$:
   * Multiply accumulated prefix product: `answer[i] *= rightProduct`.
   * Accumulate suffix product: `rightProduct *= nums[i]`.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ over two linear sweeps (one forward, one backward).
* **Space Complexity:** $\mathcal{O}(1)$ auxiliary space (excluding the output array `answer` per problem specification).