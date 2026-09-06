#include <string>

//==============================================================================
// LeetCode #20: Valid Parentheses
// Strategy: Contiguous LIFO Stack with Expected-Char Mirroring & Parity Pruning
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) worst case, O(1) best case on parity or prefix mismatch.
      - Traverses the input string in a single linear pass.
      - Each token is pushed and popped at most once.
      - Immediate O(1) rejection on odd length or first unmatched closing token.
    - Auxiliary Space: O(N) worst case (e.g., all open tokens), O(1) best case.
      - Pre-allocates contiguous memory via std::string::reserve to guarantee zero 
        dynamic reallocations and avoid std::deque block-node overhead.

    Algorithmic & Hardware Invariants:
    1. Direct Expected-Closing Mirroring:
       - Pushing the expected closing bracket instead of the matched opening bracket 
         simplifies the validation step to a direct scalar comparison ('stack.back() != c'), 
         eliminating branching tables or nested conditional matching.
    2. Bitwise Stream Parity Check:
       - Evaluates '(s.size() & 1) != 0' to reject odd-length streams in a single CPU cycle 
         before touching the heap or traversing string elements.
    3. Cache-Line Contiguity:
       - Eliminates std::stack's underlying std::deque heap indirection, pinning LIFO 
         mutations to sequential contiguous bytes on a single cache line.
*/
bool isValid(const std::string &s)
{
    if ((s.length() & 1) != 0)
    {
        return false;
    }

    std::string stack;
    stack.reserve(s.length());

    for (char c : s)
    {
        switch (c)
        {
        case '(':
            stack.push_back(')');
            break;
        case '{':
            stack.push_back('}');
            break;
        case '[':
            stack.push_back(']');
            break;
        default:
            if (stack.empty() || c != stack.back())
            {
                return false;
            }
            stack.pop_back();
            break;
        }
    }

    return (stack.empty()) ? true : false;
}