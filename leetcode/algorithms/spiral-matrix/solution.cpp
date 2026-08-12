#include <iostream>
#include <vector>

//---------- Implementation #2 (Pre-Allocated Buffer & Signed Bound Safety) ----------
/*
    Optimal Strategy: O(M * N) Time | O(1) Auxiliary Space

    Improvements over Implementation #1:

    1. Heap Allocation Elimination (std::vector::reserve):
       Pre-allocates the vector capacity to (rows * cols) up front. This guarantees 
       a single heap allocation and eliminates logarithmic capacity doublings during 
       push_back calls, reducing runtime overhead on large grids.

    2. Static Bound Casting (size_t -> int):
       Converts unsigned matrix sizes (rows, cols) into signed integers (topBound, 
       botBound, leftBound, rightBound) prior to loop entry. This prevents underflow 
       warnings or infinite loop hazards when decremented bounds (rightBound--, botBound--) 
       interact with comparison conditions under strict compiler flags.

    3. C++14/17 Standard Traversal Formatting:
       Maintains identical linear time complexity O(M * N) while adopting standardized 
       loop iterator syntax and ternary output formatting for maximum assessment compatibility.
*/
std::vector<int> spiralOrder(const std::vector<std::vector<int>>& matrix)
{
    if (matrix.empty() || matrix[0].empty())
    {
        return {};
    }

    const size_t rows = matrix.size();
    const size_t cols = matrix[0].size();

    std::vector<int> sequence;
    sequence.reserve(rows * cols);

    int topBound = 0;
    int botBound = static_cast<int>(rows) - 1;
    int leftBound = 0;
    int rightBound = static_cast<int>(cols) - 1;

    while (topBound <= botBound && leftBound <= rightBound)
    {
        // 1. Traverse Left to Right along Top Row
        for (int c = leftBound; c <= rightBound; ++c)
        {
            sequence.push_back(matrix[topBound][c]);
        }
        topBound++;

        // 2. Traverse Top to Bottom along Right Column
        for (int r = topBound; r <= botBound; ++r)
        {
            sequence.push_back(matrix[r][rightBound]);
        }
        rightBound--;

        // 3. Traverse Right to Left along Bottom Row (if row bound remains valid)
        if (topBound <= botBound)
        {
            for (int c = rightBound; c >= leftBound; --c)
            {
                sequence.push_back(matrix[botBound][c]);
            }
            botBound--;
        }

        // 4. Traverse Bottom to Top along Left Column (if column bound remains valid)
        if (leftBound <= rightBound)
        {
            for (int r = botBound; r >= topBound; --r)
            {
                sequence.push_back(matrix[r][leftBound]);
            }
            leftBound++;
        }
    }

    return sequence;
}

//---------- Implementation #1 (4-Boundary Shrinking Traversal) ----------
/*
    Optimal Strategy: O(M * N) Time | O(1) Auxiliary Space

    1. Boundary Shrinking Invariant:
       Tracks four dynamic boundaries (topBound, botBound, leftBound, rightBound) 
       that shrink inward after each side traversal. This eliminates directional 
       state machine logic or visited-cell grid markers.

    2. Asymmetric Matrix Boundary Guards:
       Explicitly checks (topBound <= botBound) before traversing right-to-left 
       and (leftBound <= rightBound) before traversing bottom-to-top. This guards 
       against duplicate element visits on non-square M x N matrices or single-row/col layers.

    3. Memory Optimization Target:
       Adding sequence.reserve(rows * cols) up front avoids dynamic std::vector 
       heap re-allocations during push_back iterations.
*/
// std::vector<int> spiralOrder(const std::vector<std::vector<int>>& matrix)
// {
//     if (matrix.empty())
//     {
//         return {};
//     }

//     int topBound = 0;
//     int botBound = matrix.size() - 1;
//     int leftBound = 0;
//     int rightBound = matrix[0].size() - 1;
//     std::vector<int> sequence;

//     while (topBound <= botBound && leftBound <= rightBound)
//     {
//         // Traverse Left to Right Along Top Row
//         for (int i = leftBound; i <= rightBound; i++)
//         {
//             sequence.push_back(matrix[topBound][i]);
//         }
//         topBound++;

//         // Traverse Top to Bottom Along Right Column
//         for (int i = topBound; i <= botBound; i++)
//         {
//             sequence.push_back(matrix[i][rightBound]);
//         }
//         rightBound--;

//         if (topBound <= botBound)
//         {
//             // Traverse Right to Left Along Bottom Row
//             for (int i = rightBound; i >= leftBound; i--)
//             {
//                 sequence.push_back(matrix[botBound][i]);
//             }
//             botBound--;
//         }

//         if (leftBound <= rightBound)
//         {
//             // Traverse Bottom to Top Along Left Column
//             for (int i = botBound; i >= topBound; i--)
//             {
//                 sequence.push_back(matrix[i][leftBound]);
//             }
//             leftBound++;
//         }
//     }

//     return sequence;
// }

int main()
{
    // Test Case #1
    std::vector<std::vector<int>> matrix1 = {{1,2,3},{4,5,6},{7,8,9}};
    std::vector<int> result1 = spiralOrder(matrix1);
    std::cout << "Expected Test #1 Output = [1,2,3,6,9,8,7,4,5]" << std::endl;
    std::cout << "  Actual Test #1 Output = [";
    for (auto iter = result1.begin(); iter != result1.end(); iter++)
    {
        if (iter != result1.end() - 1)
        {
            std::cout << *iter << ",";
        }
        else
        {
            std::cout << *iter;
        }
    }
    std::cout << "]" << std::endl << std::endl;

    // Test Case #2
    std::vector<std::vector<int>> matrix2 = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    std::vector<int> result2 = spiralOrder(matrix2);
    std::cout << "Expected Test #2 Output = [1,2,3,4,8,12,11,10,9,5,6,7]" << std::endl;
    std::cout << "  Actual Test #2 Output = [";
    for (auto iter = result2.begin(); iter != result2.end(); iter++)
    {
        if (iter != result2.end() - 1)
        {
            std::cout << *iter << ",";
        }
        else
        {
            std::cout << *iter;
        }
    }
    std::cout << "]" << std::endl << std::endl;
    
    return 0;
}