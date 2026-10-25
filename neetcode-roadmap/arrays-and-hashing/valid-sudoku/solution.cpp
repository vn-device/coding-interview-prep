#include <vector>
#include <unordered_map>
#include <unordered_set>

//==============================================================================
// LeetCode #36: Valid Sudoku
// Strategy: Direct-Address Lookup via 2D Boolean State Tables
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(1) strictly bounded by the fixed 9x9 (81 cells) grid.
      - Exactly 81 constant-time indexed array lookups and updates.
    - Auxiliary Space: O(1) stack allocation.
      - 3 tables * 9 * 10 booleans = 270 bytes residing entirely on the call stack.
      - Zero dynamic memory allocations and zero heap pointer chasing.

    Algorithmic Invariants:
    1. Direct Semantic Mapping:
       - seenRow[r][digit] tracks presence directly by index, eliminating hash collisions.
    2. Zero Memory Allocation:
       - Fixed compile-time storage avoids container creation and heap fragmentation.
*/
bool isValidSudoku(const std::vector<std::vector<char>>& board)
{
    // Tracking matrices initialized to false: [entityIndex 0..8][digit 1..9]
    bool seenRow[9][10] = {false};
    bool seenCol[9][10] = {false};
    bool seenBox[9][10] = {false};

    for (int r = 0; r < 9; ++r)
    {
        for (int c = 0; c < 9; ++c)
        {
            const char cell = board[r][c];
            if (cell == '.')
            {
                continue;
            }

            const int digit = cell - '0';
            const int boxIdx = (r / 3) * 3 + (c / 3);

            // Check if this digit has already appeared in the current row, column, or 3x3 box
            if (seenRow[r][digit] || seenCol[c][digit] || seenBox[boxIdx][digit])
            {
                return false;
            }

            // Record digit presence across all three boundaries
            seenRow[r][digit] = true;
            seenCol[c][digit] = true;
            seenBox[boxIdx][digit] = true;
        }
    }

    return true;
}

// bool isValidSudoku(const std::vector<std::vector<char>>& board)
// {
//     std::unordered_map<int, std::unordered_set<char>> rowsDB;
//     std::unordered_map<int, std::unordered_set<char>> colsDB;
//     std::unordered_map<int, std::unordered_set<char>> squrDB;

//     for (int rows = 0; rows < 9; ++rows)
//     {
//         for (int cols = 0; cols < 9; ++cols)
//         {
//             char val = board[rows][cols];
//             int squrIdx = (rows / 3) * 3 + (cols / 3);

//             if (val != '.')
//             {
//                 bool rowsDupe = rowsDB[rows].insert(val).second;
//                 bool colsDupe = colsDB[cols].insert(val).second;
//                 bool squrDupe = squrDB[squrIdx].insert(val).second;

//                 if (!rowsDupe || !colsDupe || !squrDupe)
//                 {
//                     return false;
//                 }
//             }
//         }
//     }

//     return true;
// }