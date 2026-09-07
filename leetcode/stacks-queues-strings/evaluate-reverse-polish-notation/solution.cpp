#include <vector>
#include <string>

//==============================================================================
// LeetCode #150: Evaluate Reverse Polish Notation
// Strategy: Contiguous LIFO Stack with In-Place Top Mutation
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = tokens.size().
      - Processes each token sequentially in a single pass.
      - Each token incurs O(1) stack operations and arithmetic evaluations.
    - Auxiliary Space: O(N) auxiliary memory.
      - Maximum stack depth is bounded by (N + 1) / 2 operands.
      - Pre-allocated contiguously to eliminate reallocations and segmented deque overhead.

    Algorithmic & Hardware Invariants:
    1. Postfix Operand Preservation:
       - Every binary operator consumes the top two elements (latter, then prior)
         and folds the result back to the top of the stack, maintaining strict left-to-right
         evaluation order for non-commutative operations ('-' and '/').
    2. Zero-Allocation Token Classification:
       - Single-character check '(token.size() == 1 && isOperator)' discriminates between
         operators and signed negative numbers (e.g., "-11") in O(1) without string allocations.
    3. In-Place Vector Mutation:
       - Replaces 'double pop + push' with 'single pop + reference mutation' on 'stack.back()',
         reducing write traffic to the vector's size metadata.
*/
static int fastAtoI(const std::string &s)
{
    int val = 0;
    const bool negative = (s[0] == '-');
    const size_t start = (negative || s[0] == '+') ? 1 : 0;

    for (size_t i = start; i < s.size(); ++i)
    {
        val = val * 10 + (s[i] - '0');
    }

    return negative ? -val : val;
}

int evalRPN(const std::vector<std::string> &tokens)
{
    std::vector<int> stack;
    // The maximum stack depth cannot exceed the total number of operands
    stack.reserve((tokens.size() + 1) >> 1);

    for (const std::string &token : tokens)
    {
        // Operators are strictly 1 byte: "+", "-", "*", "/"
        // Negative numbers like "-12" have token.size() > 1
        if (token.size() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/'))
        {
            const int latter = stack.back();
            stack.pop_back();
            int &prior = stack.back();

            switch (token[0])
            {
            case '+':
                prior += latter;
                break;
            case '-':
                prior -= latter;
                break;
            case '*':
                prior *= latter;
                break;
            case '/':
                prior /= latter;
                break;
            }
        }
        else
        {
            // Fast-path integer parsing without exception frames
            stack.push_back(fastAtoI(token));
        }
    }

    return stack.back();
}

//==============================================================================
// LeetCode #150: Evaluate Reverse Polish Notation
// Implementation: Linear Scan with Vector-Backed Operand Stack
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N * L) where N = tokens.size() and L is average token length.
      - Single forward traversal over the vector of token strings.
      - String equality checks and std::stoi parsing scale linearly with token length L.
      - Pushes and pops on the vector operand stack operate in O(1) amortized time.
    - Auxiliary Space: O(N) auxiliary memory.
      - Pre-allocates contiguous storage via 'intStack.reserve(tokens.size())' to eliminate reallocations.
      - Maximum operand stack depth never exceeds (N + 1) / 2 integers.

    Algorithmic & Evaluation Invariants:
    1. Postfix Operand Ordering Invariant:
       - Binary operations are non-commutative for subtraction and division.
       - The first value popped represents the right operand ('latter'), and the
         second value popped represents the left operand ('prior'), preserving
         strict arithmetic evaluation: (prior - latter) and (prior / latter).
    2. Stream Reduction Invariant:
       - Every valid operator consumes two operands and pushes exactly one result,
         monotonically reducing the net stream balance toward a single final scalar.

    Design Considerations & Optimizations:
    - Operator Parsing Latency:
      - Multi-branch string literal comparisons ('token == "+"') introduce repeated
        string comparisons; inspecting scalar characters directly ('token[0]') via a
        jump table avoids string matching overhead.
    - Exception Overhead:
      - 'std::stoi' incurs exception handling and locale parsing frames; a lightweight
        inline integer parser lowers CPU instruction counts.
    - Top-of-Stack Mutation:
      - Popping both operands followed by 'push_back' can be streamlined to a single pop
        and an in-place mutation of the preceding top element ('intStack.back()').
*/
int evalRPN(const std::vector<std::string> &tokens)
{
    std::vector<int> intStack;
    intStack.reserve(tokens.size());

    for (const std::string &token : tokens)
    {
        // Push integer tokens onto stack
        if (token != "+" && token != "-" && token != "*" && token != "/")
        {
            intStack.push_back(std::stoi(token));
        }
        // Operation token reached -> calculate, then push onto stack
        else
        {
            int latter = intStack.back();
            intStack.pop_back();
            int prior = intStack.back();
            intStack.pop_back();

            if (token == "+")
            {
                intStack.push_back(prior + latter);
            }
            else if (token == "-")
            {
                intStack.push_back(prior - latter);
            }
            else if (token == "*")
            {
                intStack.push_back(prior * latter);
            }
            else // token == "/"
            {
                intStack.push_back(prior / latter);
            }
        }
    }

    return intStack.back();
}