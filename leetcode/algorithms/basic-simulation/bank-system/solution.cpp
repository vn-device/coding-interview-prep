#include <vector>

//---------- Implementation #2 (Helper Validation & Direct Initializer List) ----------
/*
    Optimal Strategy: O(1) Per Transaction Operation | O(N) Space

    Improvements over Implementation #1:

    1. DRY Bounds Validation (isValidAccount):
       Encapsulates repeated boundary checks (1 <= account && account <= N) into a private 
       helper method, reducing code duplication across all transaction handlers.

    2. Direct Vector Member Initialization:
       Replaces manual for-loop element copying with direct constructor member initialization 
       list (accountBalances(balance)).

    3. Unsigned Size Casting Safety:
       Prevents signed/unsigned comparison warnings (-Wsign-compare) when validating 
       integer indices against vector sizes.
*/
class Bank
{
private:
    std::vector<long long> accountBalances;

    // Helper method to validate 1-based account index boundaries
    bool isValidAccount(int account) const
    {
        return account >= 1 && static_cast<size_t>(account) <= accountBalances.size();
    }

public:
    // Direct member initialization
    Bank(const std::vector<long long>& balance) : accountBalances(balance) {}

    bool transfer(int account1, int account2, long long money)
    {
        if (!isValidAccount(account1) || !isValidAccount(account2))
        {
            return false;
        }

        int idx1 = account1 - 1;
        int idx2 = account2 - 1;

        if (accountBalances[idx1] < money)
        {
            return false;
        }

        accountBalances[idx1] -= money;
        accountBalances[idx2] += money;
        return true;
    }

    bool deposit(int account, long long money)
    {
        if (!isValidAccount(account))
        {
            return false;
        }

        accountBalances[account - 1] += money;
        return true;
    }

    bool withdraw(int account, long long money)
    {
        if (!isValidAccount(account))
        {
            return false;
        }

        int idx = account - 1;
        if (accountBalances[idx] < money)
        {
            return false;
        }

        accountBalances[idx] -= money;
        return true;
    }
};

//---------- Implementation #1 (Explicit Loop Copy & Inline Bounds Check) ----------
/*
    Optimal Strategy: O(1) Per Transaction Operation | O(N) Space

    1. Correctness & Precision:
       Uses long long precision across all methods to prevent arithmetic overflow on 
       large monetary transactions.

    2. Index Normalization:
       Subtracts 1 from 1-based input parameters (account - 1) to map correctly to 
       0-indexed vector storage.

    3. Refactoring Targets:
       - Constructor initializes storage via manual element loop rather than direct vector initialization.
       - Repeats bound validation logic across transfer, deposit, and withdraw.
*/
// class Bank
// {
// private:
//     std::vector<long long> accountBalances;

// public:
//     Bank(std::vector<long long> &balance)
//     {
//         accountBalances.reserve(balance.size());

//         for (const long long &value : balance)
//         {
//             accountBalances.push_back(value);
//         }
//     }

//     bool transfer(int account1, int account2, long long money)
//     {
//         int accIndex1 = account1 - 1;
//         int accIndex2 = account2 - 1;

//         if ((accIndex1 >= 0 && accIndex1 < accountBalances.size()) &&
//             (accIndex2 >= 0 && accIndex2 < accountBalances.size()) &&
//             accountBalances[accIndex1] - money >= 0)
//         {
//             accountBalances[accIndex1] -= money;
//             accountBalances[accIndex2] += money;
//             return true;
//         }

//         return false;
//     }

//     bool deposit(int account, long long money)
//     {
//         int accountIndex = account - 1;
//         if (accountIndex >= 0 && accountIndex < accountBalances.size())
//         {
//             accountBalances[accountIndex] += money;
//             return true;
//         }
//         return false;
//     }

//     bool withdraw(int account, long long money)
//     {
//         int accountIndex = account - 1;
//         if (accountIndex >= 0 && accountIndex < accountBalances.size() &&
//             accountBalances[accountIndex] - money >= 0)
//         {
//             accountBalances[accountIndex] -= money;
//             return true;
//         }
//         return false;
//     }
// };