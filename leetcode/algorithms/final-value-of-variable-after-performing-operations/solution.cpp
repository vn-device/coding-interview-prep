#include <iostream>
#include <vector>
#include <string>

//---------- Implementation #3 ----------
/*
    Optimal Method: O(N) Time, O(1) Auxiliary Space
    Avoids unncessary std::string object copying and uses shared
    std::string indexing to check for '+' or '-' at only 1 index
    using 2 conditions rather than 4.
*/
int finalValueAfterOperations(const std::vector<std::string>& operations)
{
    if (operations.empty())
    {
        return 0;
    }

    int result = 0;
    for (const std::string& op : operations)
    {
        result = (op[1] == '+') ? result + 1 : result - 1;
    }

    return result;
}

//---------- Implementation #2 ----------
/*
    Avoids string copies, but relies on multiple branch evaluations 
    (checking both .front() and .back()) per element. Can be simplified 
    by leveraging the fixed string length invariant op[1].
*/
// int finalValueAfterOperations(const std::vector<std::string>& operations)
// {
//     if (operations.empty())
//     {
//         return 0;
//     }

//     int result = 0;
//     for (size_t i = 0; i < operations.size(); i++)
//     {
//         if (operations[i].front() == '+' || operations[i].back() == '+')
//         {
//             result++;
//         }
//         else if (operations[i].front() == '-' || operations[i].back() == '-')
//         {
//             result--;
//         }
//     }

//     return result;
// }

//---------- Implementation #1 ----------
/*
    Functional, but inefficient:
    1. Pass-by-value in range loop creates redundant std::string stack copies per iteration.
    2. full string operator== comparisons incur overhead compared to single-byte char checks.
*/
// int finalValueAfterOperations(const std::vector<std::string>& operations)
// {
//     if (operations.empty())
//     {
//         return 0;
//     }

//     int result = 0;
//     for (std::string op : operations)
//     {
//         if (op == "++X" || op == "X++")
//         {
//             result++;
//         }
//         else if (op == "--X" || op == "X--")
//         {
//             result--;
//         }
//     }

//     return result;
// }

int main()
{
    // Test Case #1
    std::vector<std::string> op1 = {"--X","X++","X++"};
    std::cout << "Expected Test Case #1 Output = 1" << std::endl;
    std::cout << "  Actual Test Case #1 Output = " << finalValueAfterOperations(op1) << std::endl << std::endl;

    // Test Case #2
    std::vector<std::string> op2 = {"++X","++X","X++"};
    std::cout << "Expected Test Case #2 Output = 3" << std::endl;
    std::cout << "  Actual Test Case #2 Output = " << finalValueAfterOperations(op2) << std::endl << std::endl;

    // Test Case #3
    std::vector<std::string> op3 = {"X++","++X","--X","X--"};
    std::cout << "Expected Test Case #3 Output = 0" << std::endl;
    std::cout << "  Actual Test Case #3 Output = " << finalValueAfterOperations(op3) << std::endl << std::endl;

    return 0;
}