#include <string>
#include <stack>

//==============================================================================
// HackerRank: Balanced Brackets
// Strategy: Contiguous LIFO Stack with Expected-Char Matching & Early Pruning
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) worst case, O(1) best case on parity or prefix mismatch.
      - Each character is pushed and popped at most once.
    - Auxiliary Space: O(N) contiguous buffer pre-allocated to avoid reallocations.

    Algorithmic Invariants & State Invariants:
    1. Direct Expected-Closing Mapping:
       - Pushing the expected closing bracket instead of the opening bracket allows 
         O(1) direct equality checks (stack.back() != c), avoiding compound conditionals.
    2. Immediate Fail-Fast Invariant:
       - Finding an unexpected closing token or encountering a closing token on an empty 
         stack halts execution immediately, avoiding redundant downstream iterations.
    3. Parity Pre-Condition:
       - Any odd-length stream cannot form complete pairs ((s.size() & 1) != 0) and is 
         pruned in O(1) before touching memory.
*/
std::string isBalanced(const std::string& s)
{
    // Bitwise odd-length check for instant rejection
    if ((s.size() & 1) != 0)
    {
        return "NO";
    }

    std::string stack;
    stack.reserve(s.size());

    for (const char c : s)
    {
        switch (c)
        {
            case '(':
                stack.push_back(')');
                break;
            case '[':
                stack.push_back(']');
                break;
            case '{':
                stack.push_back('}');
                break;
            default:
                // Closing bracket encountered: check empty or mismatch immediately
                if (stack.empty() || stack.back() != c)
                {
                    return "NO";
                }
                stack.pop_back();
                break;
        }
    }

    return stack.empty() ? "YES" : "NO";
}

//==============================================================================
// HackerRank: Balanced Brackets
// Implementation: Fall-Through Error Push Anti-Pattern (Non-Pruning)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = s.size().
      - Traverses the entire string unconditionally even when corruption is detected early.
    - Auxiliary Space: O(N) heap memory managed via std::stack default deque blocks.

    Defects & Failure Modes:
    1. Lack of Early Termination:
       - Pushes invalid closing characters back onto the stack on mismatch rather 
         than immediately returning "NO".
    2. Empty Stack Push Fall-Through:
       - Evaluates brackets.empty() at the top, incorrectly accepting initial 
         closing tokens into the stack instead of fast-failing.
*/
// std::string isBalanced(const std::string &s)
// {
//     std::stack<char> brackets;

//     for (char c : s)
//     {
//         // Push when empty stack or encounter opening bracket
//         if (brackets.empty() || c == '{' || c == '[' || c == '(')
//         {
//             brackets.push(c);
//         }
//         // Try pop when encounter closing bracket
//         else
//         {
//             char stackTop = brackets.top();
//             if ((stackTop == '{' && c == '}') ||
//                 (stackTop == '[' && c == ']') ||
//                 (stackTop == '(' && c == ')'))
//             {
//                 brackets.pop();
//             }
//             else
//             {
//                 brackets.push(c);
//             }
//         }
//     }

//     return (brackets.empty()) ? "YES" : "NO";
// }