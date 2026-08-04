# Jesse and Cookies

## Core Concept
* Order-book style dynamic priority tracking using a min-heap (`std::priority_queue<int, vector<int>, greater<int>>`).

## Algorithmic Strategy & Trade-offs
* **Min-Heap Selection:** Standard vectors or arrays require $\mathcal{O}(N \log N)$ continuous sorting upon each operation. A binary min-heap allows $\mathcal{O}(1)$ top access and $\mathcal{O}(\log N)$ insertion/deletion.
* **Iterator Construction:** Initializing the `priority_queue` directly from vector iterators `(A.begin(), A.end())` executes in linear $\mathcal{O}(N)$ time via Floyd's heap construction algorithm, rather than $\mathcal{O}(N \log N)$ sequentially pushing elements.

## Pitfalls & Edge Cases
* **Empty / Single Element Queue:** If the heap size drops to 1 and the top element is still $< K$, no further combinations are possible—return `-1`.
* **Integer Overflow:** If element values approach $2 \times 10^9$, combining `least + 2 * secondLeast` can exceed signed 32-bit `int` range ($2.14 \times 10^9$). Use `long long` for the combined total if limits permit large inputs.

## Complexity Breakdown
* **Time Complexity:** 
  * Heap Construction: $\mathcal{O}(N)$
  * Operations: $\mathcal{O}(M \log N)$ where $M$ is the number of combinations executed ($M \le N$).
* **Space Complexity:** $\mathcal{O}(N)$ to maintain heap structure.