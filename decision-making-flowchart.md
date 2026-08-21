1. Is it an Array/String problem?
   ├─ Ask: Is order required to be contiguous?
   │    ├─ YES ──> Does it have negative values?
   │    │            ├─ YES ──> Prefix Sum + Hash Map
   │    │            └─ NO  ──> Sliding Window / Two Pointers
   │    └─ NO  ──> Can we sort?
   │                 ├─ YES ──> Sort + Greedy / Binary Search
   │                 └─ NO  ──> Hash Set / Hash Map / Frequency Array
   │
2. Is it asking for Min/Max or Feasibility?
   ├─ Can a greedy choice at step i never hurt later steps? ──> Greedy
   ├─ Does step i depend on optimal choices of smaller subproblems? ──> DP
   └─ Is the answer monotonic ("if X works, all > X work")? ──> Binary Search on Answer