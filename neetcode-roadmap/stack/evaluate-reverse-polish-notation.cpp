#include <vector>
#include <string>

//==============================================================================
// LeetCode #150 / NeetCode: Evaluate Reverse Polish Notation
// Strategy: LIFO Contiguous Operand Stack with Switch Dispatch & std::stoi
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = tokens.size().
      - Single linear pass processing each token in O(1) amortized time.
    - Auxiliary Space: O(N) bounded to (tokens.size() / 2 + 1) integer entries.

    Algorithmic Invariants:
    1. Operand Pre-allocation Bound:
       - Reserving (tokens.size() / 2 + 1) prevents dynamic vector reallocations.
    2. Switch Dispatch:
       - Lowers operator branch handling to direct jump dispatch.
    3. In-Place Top Modification:
       - Mutates numbers.back() directly with the popped right operand.
*/

int evalRPN(const std::vector<std::string>& tokens)
{
    std::vector<int> numbers;
    numbers.reserve((tokens.size() / 2) + 1);

    for (const std::string &tok : tokens)
    {
        if (tok.size() == 1 && (tok[0] == '+' || tok[0] == '-' || tok[0] == '*' || tok[0] == '/'))
        {
            int temp = numbers.back();
            numbers.pop_back();

            switch (tok[0])
            {
                case '+':
                    numbers.back() += temp;
                    break;
                case '-':
                    numbers.back() -= temp;
                    break;
                case '*':
                    numbers.back() *= temp;
                    break;
                case '/':
                    numbers.back() /= temp;
                    break;
                default:
                    break;
            }
        }
        else
        {
            numbers.push_back(std::stoi(tok));
        }
    }

    return numbers.back();
}