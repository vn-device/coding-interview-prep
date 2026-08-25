#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

//---------- Implementation #1 (Single-Pass Running Minimum Tracking) ----------
/*
    Optimal Strategy: O(N) Time | O(1) Auxiliary Space

    1. Monotonic Running Minimum Invariant:
       Maintains a scalar 'minPrice' (initialized to INT_MAX) to track the absolute lowest 
       purchase price seen prior to or on the current day. This avoids the nested O(N^2) 
       pairwise loops.

    2. Local vs. Global Profit Maximization:
       Evaluates the potential yield of selling on the current day (price - minPrice) 
       and updates the global 'maxProfit' scalar in O(1) time per element.

    3. Single-Pass Memory Efficiency:
       Traverses the input vector linearly without secondary heap allocations, achieving 
       strict O(1) auxiliary space complexity.
*/
int maxProfit(const std::vector<int>& prices)
{
    int maxProfit = 0;
    int buy = INT_MAX;

    for (const int& price : prices)
    {
        buy = std::min(buy, price);
        int currentProfit = price - buy;
        maxProfit = std::max(maxProfit, currentProfit);
    }

    return maxProfit;
}

int main()
{
    // Test Case #1
    std::vector<int> prices1 = {7,1,5,3,6,4};
    std::cout << "Expected Test #1 Output = 5" << std::endl;
    std::cout << "  Actual Test #1 Output = " << maxProfit(prices1) << std::endl << std::endl;

    // Test Case #2
    std::vector<int> prices2 = {7,6,4,3,1};
    std::cout << "Expected Test #2 Output = 0" << std::endl;
    std::cout << "  Actual Test #2 Output = " << maxProfit(prices2) << std::endl << std::endl;
    
    return 0;
}