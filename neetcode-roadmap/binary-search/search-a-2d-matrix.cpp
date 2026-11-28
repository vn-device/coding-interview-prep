#include <vector>

//==============================================================================
// LeetCode #74 / NeetCode: Search a 2D Matrix
// Strategy: Single-Pass Virtual 1D Flattened Binary Search (O(log(M * N)))
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(log(M * N)) where M = rows and N = columns.
      - Treats the strictly sorted M x N matrix as a single contiguous 1D array
        of length M * N, eliminating the O(M) linear row scan.
    - Auxiliary Space: O(1) strictly register-resident scalar indices.
      - Zero heap allocations or auxiliary row buffers.

    Algorithmic & Hardware Invariants:
    1. Bijective 1D-to-2D Coordinate Mapping:
       - Any linear index mid in [0, M * N - 1] maps uniquely to:
         row = mid / width, col = mid % width.
    2. Overflow-Safe Midpoint & Bounds Guard:
       - Guards against empty matrices before dereferencing matrix[0].
       - Computes mid via left + ((right - left) / 2) to prevent signed overflow.
       - Note: With M, N <= 100 on LeetCode, M * N <= 10,000 fits in 32-bit int;
         for arbitrary large matrices, cast M * N to int64_t.
*/
bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target)
{
    if (matrix.empty() || matrix[0].empty())
    {
        return false;
    }

    const int height = static_cast<int>(matrix.size());
    const int width = static_cast<int>(matrix[0].size());

    int left = 0;
    int right = (height * width) - 1;

    while (left <= right)
    {
        const int mid = left + ((right - left) / 2);
        const int val = matrix[mid / width][mid % width];

        if (val < target)
        {
            left = mid + 1;
        }
        else if (val > target)
        {
            right = mid - 1;
        }
        else
        {
            return true;
        }
    }

    return false;
}

// bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target)
// {
//     const int height = static_cast<int>(matrix.size());
//     const int width = static_cast<int>(matrix[0].size());

//     for (int i = 0; i < height; ++i)
//     {
//         if (target >= matrix[i].front() && target <= matrix[i].back())
//         {
//             int left = 0;
//             int right = width - 1;

//             while (left <= right)
//             {
//                 int mid = left + ((right - left) / 2);
//                 int value = matrix[i][mid];

//                 if (value < target)
//                 {
//                     left = mid + 1;
//                 }
//                 else if (value > target)
//                 {
//                     right = mid - 1;
//                 }
//                 else
//                 {
//                     return true;
//                 }
//             }
//         }
//     }

//     return false;
// }