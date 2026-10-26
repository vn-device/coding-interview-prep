#include <string>
#include <vector>

//==============================================================================
// LeetCode #20 / NeetCode: Valid Parentheses
// Strategy: LIFO Contiguous Stack Buffer with Direct Closing-Match Dispatch
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = s.length().
      - Early return for odd-length inputs: O(1).
      - Single forward linear scan across the character buffer: O(N).
    - Auxiliary Space: O(N) worst-case stack capacity.
      - Pre-allocating buffer storage eliminates mid-traversal vector growth.

    Algorithmic & Hardware Invariants:
    1. Odd-Length Parity Pruning:
       - Any valid matching sequence must contain an even number of characters.
         Rejecting (s.length() % 2 != 0) immediately skips loop execution.
    2. Contiguous Cache Locality:
       - std::vector<char> maintains contiguous memory backing, ensuring L1/L2
         cache hit rates and avoiding node allocations from std::stack / std::deque.
    3. Push-Expected Pattern:
       - Pushing the expected closing bracket when an opener is encountered simplifies
         the closing branch to a single equality comparison (buffer.back() != c).
*/
bool isValid(const std::string& s)
{
    // Parity check: valid parentheses strings must have an even length
    if ((s.length() & 1) != 0)
    {
        return false;
    }

    std::vector<char> buffer;
    buffer.reserve(s.length());

    for (const char c : s)
    {
        if (c == '(')
        {
            buffer.push_back(')');
        }
        else if (c == '{')
        {
            buffer.push_back('}');
        }
        else if (c == '[')
        {
            buffer.push_back(']');
        }
        else
        {
            if (buffer.empty() || buffer.back() != c)
            {
                return false;
            }

            buffer.pop_back();
        }
    }
}

// bool isValid(const std::string& s)
// {
//     std::vector<char> buffer;
//     buffer.reserve(s.length());

//     for (char c : s)
//     {
//         if (c == '(' || c == '{' || c == '[')
//         {
//             buffer.push_back(c);
//         }
//         else
//         {
//             if (buffer.empty() ||
//                 (buffer.back() == '(' && c != ')') ||
//                 (buffer.back() == '{' && c != '}') ||
//                 (buffer.back() == '[' && c != ']'))
//             {
//                 return false;
//             }

//             buffer.pop_back();
//         }
//     }

//     return buffer.empty() ? true : false;
// }