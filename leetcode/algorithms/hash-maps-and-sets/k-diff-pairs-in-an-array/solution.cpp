#include <vector>
#include <unordered_map>
#include <algorithm>

//==============================================================================
// LeetCode #532: K-diff Pairs in an Array
// Strategy: In-Place Sort with Monotonic Two-Pointer Window & Duplicate Skip
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log N) where N = nums.size().
      - std::sort requires O(N log N) preprocessing time.
      - Two-pointer scan advances left and right at most N steps each -> O(N) scan.
    - Auxiliary Space: O(1) auxiliary stack space.
      - Modifies the input vector in-place with zero dynamic memory allocation.

    Algorithmic Invariants:
    1. Monotonic Difference Step:
       - For sorted array A, D(left, right) = A[right] - A[left] is monotonic.
       - Incrementing right increases D; incrementing left decreases D.
    2. Duplicate Pruning:
       - Advancing left past duplicate consecutive values guarantees every recorded (A[left], A[right]) pair is unique.
*/
int findPairs(std::vector<int>& nums, int k)
{
    if (nums.size() <= 1 || k < 0)
    {
        return 0;
    }

    std::sort(nums.begin(), nums.end());

    int uniquePairs = 0;
    size_t left = 0;
    size_t right = 1;
    const size_t n = nums.size();

    while (left < n && right < n)
    {
        // Avoid self-pairing or advancing right past left
        if (left == right || nums[right] - nums[left] < k)
        {
            right++;
        }
        else if (nums[right] - nums[left] > k)
        {
            left++;
        }
        else // nums[right] - nums[left] == k
        {
            uniquePairs++;
            left++;
            right++;

            // Skip duplicate left values to enforce uniqueness
            while (left < n && nums[left] == nums[left - 1])
            {
                left++;
            }
        }
    }

    return uniquePairs;
}

//==============================================================================
// LeetCode #532: K-diff Pairs in an Array
// Implementation: Frequency Hash Map with Direct Complement Lookup (5 ms)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - Pass 1: O(N) linear sweep to construct the frequency hash map.
      - Pass 2: O(U) average time scanning unique keys (where U <= N).
      - Hash table lookup and insertion run in O(1) amortized time.
    - Auxiliary Space: O(N) auxiliary heap memory.
      - std::unordered_map stores up to N unique key-value pairs.

    Key Invariants & Mechanism:
    1. Value-Based Uniqueness:
       - Problem counts unique value pairs (a, b) rather than unique index pairs.
       - Building a frequency map naturally deduplicates candidate keys.
    2. Directed Complement Search:
       - For k > 0, querying strictly (val + k) guarantees each unique difference is counted exactly once.
    3. Zero-Difference Special Case (k == 0):
       - A self-pair (x, x) requires the value x to appear at least twice (count >= 2).
*/
// int findPairs(std::vector<int> &nums, int k)
// {
//     const size_t n = nums.size();
//     if (n <= 1 || k < 0)
//     {
//         return 0;
//     }

//     int uniquePairs = 0;
//     std::unordered_map<int, int> numsFreq;

//     for (const int &num : nums)
//     {
//         numsFreq[num]++;
//     }

//     for (const auto &[val, count] : numsFreq)
//     {
//         if ((k == 0 && count >= 2) ||
//             (k > 0 && numsFreq.find(val + k) != numsFreq.end()))
//         {
//             uniquePairs++;
//         }
//     }

//     return uniquePairs;
// }

// int findPairs(std::vector<int> &nums, int k)
// {
//     const size_t n = nums.size();
//     if (n <= 1 || k < 0)
//     {
//         return 0;
//     }

//     int uniquePairs = 0;
//     std::unordered_map<int, int> numsFreq;

//     for (const int &num : nums)
//     {
//         numsFreq[num]++;
//     }

//     if (k == 0)
//     {
//         for (const auto &iter : numsFreq)
//         {
//             if (iter.second >= 2)
//             {
//                 uniquePairs++;
//             }
//         }
//     }
//     else
//     {
//         for (const auto &iter : numsFreq)
//         {
//             int target = iter.first + k;
//             if (numsFreq.find(target) != numsFreq.end())
//             {
//                 uniquePairs++;
//             }
//         }
//     }

//     return uniquePairs;
// }