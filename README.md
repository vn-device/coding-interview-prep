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
| NeetCode | Stack | [Car Fleet]() | $O(N \log N)$ | $O(N)$ | Contiguous `(position, speed)` pair buffer sorted descending; compresses monotonic stack into scalar `slowestTime` register tracking. |
| NeetCode | Stack | [Largest Rectangle In Histogram]() | $O(N)$ | $O(N)$ | Single-pass monotonic increasing index stack with virtual zero-height sentinel (`i == len`) resolving left/right smaller boundaries on eviction. |
| NeetCode | Two Pointers | [Valid Palindrome]() | $O(N)$ | $O(1)$ | Converging two-pointer scan using locale-free inline ASCII classification and disjoint lowercase folding; zero heap allocations. |
| NeetCode | Two Pointers | [Two Integer Sum II]() | $O(N)$ | $O(1)$ | Converging two-pointer scan leveraging sorted monotonicity to eliminate candidate rows/columns in $O(1)$ auxiliary space. |
| NeetCode | Two Pointers | [3Sum]() | $O(N^2)$ | $O(1)$ | In-place sort with suffix two-pointer scan (`j = i + 1`), positive pivot pruning, and adjacent-element skip loops for $O(1)$ space deduplication. |
| NeetCode | Two Pointers | [Container W/ Most Water]() | $O(N)$ | $O(1)$ | Converging two-pointer greedy contraction advancing the shorter boundary with sub-threshold height fast-forwarding. |
| NeetCode | Two Pointers | [Trapping Rain Water]() | $O(N)$ | $O(1)$ | Converging two-pointer scan tracking running `leftMax` and `rightMax` scalars; advances the smaller boundary ceiling in $O(1)$ auxiliary space. |
| NeetCode | Linked List | [Reverse Linked List]() | $O(N)$ | $O(1)$ | Iterative three-pointer (`prev`, `curr`, `nextTemp`) in-place link reversal; avoids $O(N)$ recursive call-stack overhead. |
| NeetCode | Linked List | [Merge Two Sorted Linked Lists]() | $O(N + M)$ | $O(1)$ | Stack-allocated sentinel node with in-place pointer splicing and $O(1)$ remaining suffix attachment; zero heap allocations. |
| NeetCode | Linked List | [Linked List Cycle Detection]() | $O(N)$ | $O(1)$ | Floyd's tortoise-and-hare fast/slow pointer traversal comparing node memory addresses (`slow == fast`) with `fast && fast->next` null guards. |
| NeetCode | Sliding Window | [Best Time to Buy & Sell Stock]() | $O(N)$ | $O(1)$ | Single-pass dynamic sliding window snapping `left` purchase anchor to new minimums (or scalar `minBuy` tracking); zero heap allocations. |
| NeetCode | Sliding Window | [Longest Substring W/out Repeating Characters]() | $O(N)$ | $O(1)$ | Single-pass dynamic sliding window with stack-allocated 256-entry `lastSeen` direct-address table; jumps `left` directly past duplicates in $O(1)$. |
| NeetCode | Binary Search | [Binary Search]() | $O(\log N)$ | $O(1)$ | Iterative closed-interval `[left, right]` search using overflow-safe midpoint `left + ((right - left) / 2)` and direct early return. |
| NeetCode | Binary Search | [Search a 2D Matrix]() | $O(\log(M \cdot N))$ | $O(1)$ | Single-pass binary search over virtual 1D flattened range `[0, M * N - 1]` using `mid / width` and `mid % width` coordinate mapping. |

---

## Repository Layout

```
coding-interview-prep/
├── .github/
│   └── NOTE_TEMPLATE.md    # Standardised problem note template
├── README.md               # This file
├── hackerrank/             # HackerRank solutions by domain
└── leetcode/               # LeetCode solutions by domain
└── neetcode-roadmap/       # NeetCode solutions by domain
```