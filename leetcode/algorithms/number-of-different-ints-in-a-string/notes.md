# 1805. Number of Different Integers in a String

## Core Concept
* Parse continuous digit sequences out of a string `word` and count how many unique numerical values exist.
* **Large Integer Limitation:** Input digits can span up to 1000 characters, rendering standard C++ integer conversions (`std::stoi`, `std::stoull`) unusable due to `std::out_of_range` exceptions.
* **String Invariant Normalization:** Numbers must be normalized as strings by stripping leading `'0'` characters using `token.find_first_not_of('0')`. If no non-zero character exists (i.e., the token is `"000"`), normalize the value to `"0"`.

## Algorithmic Strategy
1. Initialize a `std::unordered_set<std::string>` to store unique normalized numerical strings.
2. Iterate through `word` character by character:
   * If the character is between `'0'` and `'9'`, append it to `token`.
   * If a non-digit character is encountered and `token` is non-empty:
     * Find the first non-zero character index `nonzeroPos`.
     * Insert `token.substr(nonzeroPos)` (or `"0"` if `nonzeroPos == npos`) into the set.
     * Clear `token`.
3. Perform a final flush after the loop to handle any trailing token at the end of `word`.
4. Return `uniqueNums.size()`.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ — Single pass over `word` of length $N$. Substring extraction and hash set operations execute in linear time overall.
* **Space Complexity:** $\mathcal{O}(N)$ — Auxiliary space required for string tokens and hash set keys in worst-case non-overlapping digit inputs.