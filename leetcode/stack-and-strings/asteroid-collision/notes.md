# 735. Asteroid Collision

## Core Concept
* Simulate a linear sequence of moving asteroids where positive values represent right-moving asteroids and negative values represent left-moving asteroids.
* **Collision Invariant:** A collision only occurs when the top of the stack is moving right (`> 0`) and the incoming asteroid is moving left (`< 0`).
* A **Stack** naturally maintains the order of surviving asteroids and resolves multi-stage collisions in amortized linear time.

## Algorithmic Strategy
1. Initialize a `std::vector<int>` as a stack accumulator and reserve memory up front.
2. Iterate through each asteroid `curr`:
   * Set a boolean flag `destroyed = false`.
   * While the stack is not empty, `stack.back() > 0`, and `curr < 0`:
     * If `stack.back() < abs(curr)`: Pop the stack and continue checking against the next top element.
     * If `stack.back() == abs(curr)`: Pop the stack, mark `destroyed = true`, and break.
     * If `stack.back() > abs(curr)`: Mark `destroyed = true` and break.
   * If `!destroyed`, push `curr` onto the stack.
3. Return the populated stack vector.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ — Each asteroid is pushed and popped at most once across all loop iterations.
* **Space Complexity:** $\mathcal{O}(N)$ — Auxiliary space used for the output stack in cases with no opposing collisions.