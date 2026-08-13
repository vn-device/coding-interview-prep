#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

//---------- Implementation #2 (std::accumulate & Range-Based Traversal) ----------
/*
    Optimal Strategy: O(M * N) Time | O(1) Auxiliary Space

    Improvements over Implementation #1:

    1. Reduction of Indexing Boilerplate (std::accumulate):
       Replaces the nested inner column loop (for c = 0; c < cols; c++) with 
       std::accumulate(customer.begin(), customer.end(), 0). This leverages standard 
       library algorithms to perform row summation cleanly in a single line.

    2. Range-Based Row Iteration:
       Iterates over rows via const auto& customer instead of manual index management 
       (for r = 0; r < rows; r++), eliminating raw size_t loop counter overhead and 
       out-of-bounds indexing hazards.

    3. Explicit Base-Case Return Value:
       Fixes the empty matrix guard return from return {} to an explicit return 0, 
       ensuring clear primitive integer return semantics under strict compiler settings.
*/
int maximumWealth(const std::vector<std::vector<int>>& accounts)
{
    int maxWealth = 0;
    for (const std::vector<int>& acc : accounts)
    {
        int currentWealth = std::accumulate(acc.begin(), acc.end(), 0);
        maxWealth = std::max(maxWealth, currentWealth);
    }

    return maxWealth;
}

//---------- Implementation #1 (Linear Row Accumulation & Max Tracking) ----------
/*
    Optimal Strategy: O(M * N) Time | O(1) Auxiliary Space

    1. Matrix Row Summation Invariant:
       Iterates through each customer row to aggregate bank account balances, 
       updating the global maximum wealth scalar in O(M * N) time across all elements.

    2. Space Optimization:
       Performs single-pass accumulation without secondary data structure allocations, 
       achieving O(1) auxiliary space complexity.

    3. Refactoring Target:
       Replaces explicit index-based loops (for r, for c) with C++ range-based loops 
       or std::accumulate to reduce boilerplate code during assessment speed runs.
*/
// int maximumWealth(const std::vector<std::vector<int>>& accounts)
// {
//     if (accounts.empty())
//     {
//         return 0;
//     }

//     int maxWealth = 0;
//     size_t rows = accounts.size();
//     size_t cols = accounts[0].size();

//     for (size_t r = 0; r < rows; r++)
//     {
//         int currentWealth = 0;
        
//         for (size_t c = 0; c < cols; c++)
//         {
//             currentWealth += accounts[r][c];
//         }

//         maxWealth = std::max(maxWealth, currentWealth);
//     }

//     return maxWealth;
// }

int main()
{
    // Test Case #1
    std::vector<std::vector<int>> accounts1 = { {1,2,3}, {3,2,1} };
    std::cout << "Expected Test #1 Output = 6" << std::endl;
    std::cout << "  Actual Test #1 Output = " << maximumWealth(accounts1) << std::endl << std::endl;

    // Test Case #2
    std::vector<std::vector<int>> accounts2 = { {1,5}, {7,3}, {3,5} };
    std::cout << "Expected Test #2 Output = 10" << std::endl;
    std::cout << "  Actual Test #2 Output = " << maximumWealth(accounts2) << std::endl << std::endl;

    // Test Case #3
    std::vector<std::vector<int>> accounts3 = { {2,8,7}, {7,1,3}, {1,9,5} };
    std::cout << "Expected Test #3 Output = 17" << std::endl;
    std::cout << "  Actual Test #3 Output = " << maximumWealth(accounts3) << std::endl << std::endl;
    
    return 0;
}