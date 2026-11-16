#include <vector>
#include <algorithm>

//==============================================================================
// LeetCode #15 / NeetCode: 3Sum
// Strategy: In-Place Sort + Fixed Pivot with Deduplicated Converging Two-Pointers
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N^2) where N = nums.size().
      - std::sort executes in O(N log N).
      - Outer pivot loop runs N times; inner converging two-pointer scan takes O(N).
    - Auxiliary Space: O(1) beyond the output vector (O(log N) internal sort stack).
      - Zero hash sets or auxiliary lookup tables required for deduplication.

    Algorithmic & Hardware Invariants:
    1. Suffix-Only Search Space (j = i + 1):
       - Prevents index reuse (i != j != k) and eliminates permutation duplicates.
    2. Pivot Deduplication & Positive Pruning:
       - Skipping nums[i] == nums[i - 1] avoids re-running identical target searches.
       - Breaking when nums[i] > 0 prunes impossible positive-only suffixes.
    3. Match-Boundary Fast-Forwarding:
       - Advancing j and k past equal neighbors upon a valid match guarantees
         unique triplets without secondary hash-set filtering.
*/
std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
{
    const int len = static_cast<int>(nums.size());
    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> result;

    for (int i = 0; i < len - 2; ++i)
    {
        // Sorted array invariant: if the smallest element is > 0, sum cannot reach 0
        if (nums[i] > 0)
        {
            break;
        }

        // Skip duplicate pivot values to prevent duplicate triplets
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue;
        }

        int j = i + 1;
        int k = len - 1;

        while (j < k)
        {
            int sum = nums[j] + nums[k];

            if (sum < -nums[i])
            {
                ++j;
            }
            else if (sum > -nums[i])
            {
                --k;
            }
            else
            {
                result.push_back({nums[i], nums[j], nums[k]});
                ++j;
                --k;

                // Fast-forward j past duplicate values
                while (j < k && nums[j] == nums[j - 1])
                {
                    ++j;
                }

                // Fast-forward k past duplicate values
                while (j < k && nums[k] == nums[k + 1])
                {
                    --k;
                }
            }
        }
    }

    return result;
}

// std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
// {
//     const int len = static_cast<int>(nums.size());
//     std::sort(nums.begin(), nums.end());
//     std::vector<std::vector<int>> result;

//     for (int i = 0; i < len; ++i)
//     {
//         int j = 0;
//         int k = len - 1;

//         while (j < k)
//         {
//             int sum = nums[j] + nums[k];
//             if (sum < -nums[i])
//             {
//                 ++j;
//             }
//             else if (sum > -nums[i])
//             {
//                 --k;
//             }
//             else
//             {
//                 result.push_back({nums[i], nums[j], nums[k]});
//                 ++j;
//                 --k;
//             }
//         }
//     }

//     return result;
// }