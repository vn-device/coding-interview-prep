# 468. Validate IP Address

## Core Concept
* Determine whether an input string matches valid **IPv4** rules, **IPv6** rules, or **Neither**.
* **IPv4 Octet Invariants:**
  * Exactly 4 octets separated by 3 period (`.`) delimiters.
  * Each octet length is between 1 and 3 characters without leading zeros (except for `"0"`).
  * Numeric value falls strictly within $[0, 255]$.
* **IPv6 Hextet Invariants:**
  * Exactly 8 hextets separated by 7 colon (`:`) delimiters.
  * Each hextet length is between 1 and 4 valid hexadecimal characters (`'0'`–`'9'`, `'a'`–`'f'`, `'A'`–`'F'`).

## Algorithmic Strategy
1. Perform a single pass across `queryIP` to count delimiter periods (`.`) and colons (`:`).
2. If `dotCount == 3` and `colonCount == 0`:
   * Ensure `queryIP.back() != '.'`.
   * Tokenize by `.` using `std::getline`.
   * Validate every token against IPv4 octet rules.
3. If `colonCount == 7` and `dotCount == 0`:
   * Ensure `queryIP.back() != ':'`.
   * Tokenize by `:` using `std::getline`.
   * Validate every token against IPv6 hextet rules.
4. Return `"IPv4"`, `"IPv6"`, or `"Neither"` accordingly.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(N)$ — Single linear pass to inspect character set and count delimiters, where $N$ is the length of `queryIP`.
* **Space Complexity:** $\mathcal{O}(1)$ — Fixed auxiliary memory allocated for token buffers and string constants.