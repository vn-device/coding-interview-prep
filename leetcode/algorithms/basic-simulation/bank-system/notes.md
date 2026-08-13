# 2043. Simple Bank System

## Core Concept
* Design a class to simulate basic banking transactions (`transfer`, `deposit`, `withdraw`) for $N$ accounts.
* **Validation Invariant:** All operations must validate account index boundaries ($1 \le \text{account} \le N$) and ensure sufficient balance before mutating any account state.

## Algorithmic Strategy
1. Store account balances in `std::vector<long long> accountBalances`.
2. Implement private helper `isValidAccount(int account)` to check $1$-based boundary validity safely against `accountBalances.size()`.
3. For `transfer(account1, account2, money)`:
   * Verify both accounts are valid.
   * Verify `accountBalances[account1 - 1] >= money`.
   * Subtract from `account1` and add to `account2`.
4. For `deposit(account, money)`:
   * Verify account validity and add `money`.
5. For `withdraw(account, money)`:
   * Verify account validity and sufficient balance, then subtract `money`.

## Complexity Breakdown
* **Time Complexity:** $\mathcal{O}(1)$ per transaction operation (`transfer`, `deposit`, `withdraw`). Constructor takes $\mathcal{O}(N)$ to copy/initialize balances.
* **Space Complexity:** $\mathcal{O}(N)$ — Storage for $N$ account balances in `std::vector<long long>`.