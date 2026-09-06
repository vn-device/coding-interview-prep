#include <vector>

//==============================================================================
// LeetCode #260: Single Number III
// Strategy: Bitwise XOR Partitioning via Lowest Set Bit Isolation
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - Executes two linear scans over the input vector.
      - Pass 1 computes the XOR sum of all elements to yield (x ^ y).
      - Pass 2 partitions the array using the extracted bit and folds each subset.
    - Auxiliary Space: O(1) auxiliary memory.
      - Operates entirely within scalar registers (xorSum, diffBit, num1, num2).
      - The return vector of size 2 is mandated by the interface.

    Bitwise & Hardware Invariants:
    1. Paired Cancellation via Nilpotence:
       - Every duplicate number appears twice and cancels out to zero (k ^ k = 0) 
         across the cumulative XOR sum, leaving xorSum = x ^ y.
    2. Bit Difference Invariant:
       - Because x != y, xorSum != 0. At least one bit in xorSum must be 1, indicating 
         a bit position where x and y have opposing values (one is 1, the other is 0).
    3. Safe Two's Complement Lowest Set Bit Isolation:
       - Computing 'diffBit = static_cast<unsigned int>(xorSum) & -static_cast<unsigned int>(xorSum)' 
         safely isolates the least significant set bit while preventing undefined behavior 
         from signed integer overflow when xorSum == INT_MIN.
    4. Deterministic Stream Partitioning:
       - Grouping values by '(val & diffBit) != 0' splits the stream into two independent sets. 
         Duplicate pairs always fall into the same partition and negate, while x and y are 
         strictly segregated into distinct accumulators.

    Operator Precedence Gotcha (Bitwise AND vs. Relational Operators):
    - In C++, equality and relational operators ('!=', '==', '<', '>') have higher 
      precedence than bitwise operators ('&', '^', '|').
    - Writing 'val & diffBit != 0' implicitly evaluates as 'val & (diffBit != 0)'.
      Because '(diffBit != 0)' yields boolean true (promoted to integer 1), the expression 
      collapses into a parity test ('val & 1') rather than masking against 'diffBit'.
    - Mandatory Rule: Always explicitly parenthesize bitwise masking expressions when 
      comparing results: '((val & diffBit) != 0)'.
*/
std::vector<int> singleNumber(const std::vector<int> &nums)
{
    // XOR all elements to find xorSum = x XOR(^) y
    int xorSum = 0;
    for (int val : nums)
    {
        xorSum ^= val;
    }

    // Extract lowest set bit
    unsigned int diffBit = static_cast<unsigned int>(xorSum) & -static_cast<unsigned int>(xorSum);

    // Go thru all elements again
    int num1 = 0;
    int num2 = 0;

    for (int val : nums)
    {
        // if (val & diffBit != 0)
        if ((val & diffBit) != 0)
        {
            num1 ^= val;
        }
        else
        {
            num2 ^= val;
        }
    }

    return {num1, num2};
}