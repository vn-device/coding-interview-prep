#include <iostream>
#include <vector>
#include <algorithm>

//---------- Implementation #2 (Refactored Bounds & Standard Swap) ----------
/*
    Optimal Strategy: O(N^2) Time | O(1) Auxiliary Space

    Improvements over Implementation #1:

    1. Pruned Inner Loop Traversal:
       Initializes inner column loop at c = r + 1 to strictly traverse elements above 
       the main diagonal. This eliminates the explicit branch check (r < c) present in 
       Implementation #1, cutting total inner loop iterations and branch checks in half.

    2. Natural Boundary Handling & Guard Elimination:
       Relying directly on matrix.size() and loop bound invariants (r < n) naturally 
       handles empty matrix inputs (N = 0) without requiring redundant early return 
       guard clauses or risk of out-of-bounds access.

    3. Standard Library Move Semantics:
       Replaces manual temporary variable assignments with std::swap(matrix[r][c], matrix[c][r]), 
       improving code clarity while leveraging low-level value exchange semantics.
*/
void rotate(std::vector<std::vector<int>>& matrix)
{
    const size_t dimension = matrix.size();
    for (size_t rows = 0; rows < dimension; rows++)
    {
        for (size_t cols = rows + 1; cols < dimension; cols++)
        {
            std::swap(matrix[rows][cols], matrix[cols][rows]);
        }
    }

    for (std::vector<int>& row : matrix)
    {
        std::reverse(row.begin(), row.end());
    }
}

//---------- Implementation #1 (Matrix Transpose & Horizontal Row Reversal) ----------
/*
    Optimal Strategy: O(N^2) Time | O(1) Auxiliary Space

    1. In-Place Linear Algebraic Transformation Invariant:
       A 90-degree clockwise matrix rotation is mathematically equivalent to:
         Rotate(M) = ReverseRows(Transpose(M))
       Performing these operations sequentially achieves the exact transformation 
       in-place with zero auxiliary heap allocations (O(1) space).

    2. Theoretical Lower Bound:
       Since an N x N matrix contains N^2 elements that must each change memory 
       locations, O(N^2) time complexity is the strict theoretical minimum bound.

    3. Refactoring & Optimization Targets:
       - Inner Transpose Loop: Uses a conditional check (r < c) across all indices. 
         Starting the inner column index at c = r + 1 prunes redundant loop 
         iterations and branch evaluations completely.
       - Modern Utilities: Manual temp variable assignment can be replaced with 
         std::swap for better readability and move semantics.
*/
// void rotate(std::vector<std::vector<int>>& matrix)
// {
//     if (matrix.empty())
//     {
//         return;
//     }

//     size_t rows = matrix.size();
//     size_t cols = matrix[0].size();

//     // First transpose process
//     for (int r = 0; r < rows; r++)
//     {
//         for (int c = 0; c < cols; c++)
//         {
//             if (r < c)
//             {
//                 int temp = matrix[r][c];
//                 matrix[r][c] = matrix[c][r];
//                 matrix[c][r] = temp;
//             }
//         }
//     }

//     // Reversal for each row
//     for (std::vector<int>& sub : matrix)
//     {
//         std::reverse(sub.begin(), sub.end());
//     }
// }

int main()
{
    // Test Case #1
    std::vector<std::vector<int>> matrix1 = { {1,2,3} , {4,5,6} , {7,8,9} };
    std::cout << "Expected Test #1 Output = [ {7,4,1} {8,5,2} {9,6,3} ]" << std::endl;
    std::cout << "  Actual Test #1 Output = [ ";
    rotate(matrix1);
    for (std::vector<int>& ref : matrix1)
    {
        std::cout << "{";        
        for (size_t i = 0; i < ref.size(); i++)
        {
            if (i < ref.size() - 1)
            {
                std::cout << ref[i] << ",";
            }
            else
            {
                std::cout << ref[i];
            }
        }
        std::cout << "} ";
    }
    std::cout << "]" << std::endl << std::endl;

    // Test Case #2
    std::vector<std::vector<int>> matrix2 = { {5,1,9,11} , {2,4,8,10} , {13,3,6,7} , {15,14,12,16} };
    std::cout << "Expected Test #2 Output = [ {15,13,2,5} {14,3,4,1} {12,6,8,9} {16,7,10,11} ]" << std::endl;
    std::cout << "  Actual Test #2 Output = [ ";
    rotate(matrix2);
    for (std::vector<int>& ref : matrix2)
    {
        std::cout << "{";        
        for (size_t i = 0; i < ref.size(); i++)
        {
            if (i < ref.size() - 1)
            {
                std::cout << ref[i] << ",";
            }
            else
            {
                std::cout << ref[i];
            }
        }
        std::cout << "} ";
    }
    std::cout << "]" << std::endl << std::endl;

    return 0;
}