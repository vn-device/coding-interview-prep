#include <vector>

//==============================================================================
// LeetCode #238 / NeetCode: Product of Array Except Self
// Strategy: Dual Accumulator Single Buffer Traversal (O(1) Auxiliary Space)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - Forward pass: N iterations.
      - Backward pass: N iterations.
      - Total operations: 2N arithmetic multiplications.
    - Auxiliary Space: O(1) beyond the output vector.
      - Eliminates prefix and postfix heap buffers entirely.

    Algorithmic & Hardware Invariants:
    1. Single Allocation Footprint:
       - Directly writes left prefix products into 'result', reusing the output
         vector to accumulate the final answer in-place.
    2. Register-Bounded Suffix Tracking:
       - Accumulates the right suffix product into a single scalar register (suffixProd),
         maintaining strict L1 cache residency and eliminating memory traffic.
    3. Branchless Loop Structure:
       - Eliminates boundary conditionals (if i == 0, if i == len - 1) across the hot loop.
*/
std::vector<int> productExceptSelf(const std::vector<int>& nums)
{
    const size_t len = nums.size();
    std::vector<int> result(len, 1);

    // Pass 1: Accumulate prefix products directly into result
    // result[i] will contain the product of all elements to the left of i
    int prefixProd = 1;
    for (size_t i = 0; i < len; ++i)
    {
        result[i] = prefixProd;
        prefixProd *= nums[i];
    }

    // Pass 2: Accumulate suffix products into a single scalar and multiply in-place
    // result[i] becomes (prefix product to the left) * (suffix product to the right)
    int suffixProd = 1;
    for (size_t i = len; i-- > 0;)
    {
        result[i] *= suffixProd;
        suffixProd *= nums[i];
    }

    return result;
}

// std::vector<int> productExceptSelf(const std::vector<int> &nums)
// {
//     const int len = static_cast<int>(nums.size());
//     std::vector<int> prefix(len, 0);
//     int running = 1;

//     for (int i = 0; i < len; ++i)
//     {
//         running *= nums[i];
//         prefix[i] = running;
//     }

//     std::vector<int> postfix(len, 0);
//     running = 1;

//     for (int i = len - 1; i >= 0; --i)
//     {
//         running *= nums[i];
//         postfix[i] = running;
//     }

//     std::vector<int> result(len, 0);

//     for (int i = 0; i < len; ++i)
//     {
//         if (i == 0)
//         {
//             result[i] = postfix[i + 1];
//         }
//         else if (i == len - 1)
//         {
//             result[i] = prefix[i - 1];
//         }
//         else
//         {
//             result[i] = prefix[i - 1] * postfix[i + 1];
//         }
//     }

//     return result;
// }