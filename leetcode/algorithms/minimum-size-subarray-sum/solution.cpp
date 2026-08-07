#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

//-------------- Brute Force Method - Time Complexity O(N^2) --------------
// int minSubArrayLen(int target, vector<int>& nums)
// {
//     // Worst edge cases and easy to consider scenarios
//     if (nums.empty() || (nums.size() == 1 && nums[0] < target))
//         return 0;

//     // Using climits INT_MAX macro to start tracking subarray lengths
//     int runningSum, currentSubLen, minSubLen = INT_MAX;

//     for (size_t i = 0; i < nums.size(); i++)
//     {
//         runningSum = 0, currentSubLen = 0;
//         for (size_t j = i; j < nums.size(); j++)
//         {
//             runningSum += nums[j];
//             currentSubLen++;

//             if (runningSum >= target)
//             {
//                 minSubLen = min(minSubLen, currentSubLen);
//                 break;
//             }
//         }
//     }

//     return (minSubLen == INT_MAX) ? 0 : minSubLen;
// }
//-------------- Brute Force Method - Failed LeetCode's Time Limit Exceeding Test --------------

//-------------- Optimized Method #1 - Time Complexity O(N) --------------
// int minSubArrayLen(int target, vector<int>& nums)
// {
//     // Using Sliding Window Technique
//     int windowSum = 0, leftBound = 0, minSubLen = INT_MAX;

//     // Dynamic Two-Pointer Sliding Window: Amortized O(N) Time
//     for (size_t i = 0; i < nums.size(); i++)
//     {
//         windowSum += nums[i];
//         while (windowSum >= target)
//         {
//             minSubLen = min(minSubLen, static_cast<int>(i - leftBound + 1));
//             windowSum -= nums[leftBound++];
//         }
//     }

//     return (minSubLen == INT_MAX) ? 0 : minSubLen;
// }

//-------------- Optimized Method #2 - Time Complexity O(N log(N)) --------------
int minSubArrayLen(int target, vector<int>& nums)
{
    // Using Binary Search Technique
    // Find all prefix nums first (Start w/ prefixSums[0] = 0)
    vector<int> prefixSums(nums.size() + 1, 0);
    for (size_t i = 0; i < nums.size(); i++)
    {
        prefixSums[i + 1] = prefixSums[i] + nums[i];
    }

    int minSubLen = INT_MAX;
    for (size_t i = 0; i < prefixSums.size(); i++)
    {
        // Use std::lower_bound to find first prefix < requiredPrefix 
        int requiredPrefix = target + prefixSums[i];
        auto iter = lower_bound(prefixSums.begin() + i + 1, prefixSums.end(), requiredPrefix);

        if (iter != prefixSums.end())
        {
            int subLen = (iter - prefixSums.begin()) - i;
            minSubLen = min(minSubLen, subLen);
        }
    }

    return (minSubLen == INT_MAX) ? 0 : minSubLen;
}

int main()
{
    // Test Case #1 - Expected Output = 2
    vector<int> nums1 = {2,3,1,2,4,3};
    int target1 = 7;
    cout << "Test #1 Actual Output: " << minSubArrayLen(target1, nums1) << "\n";

    // Test Case #2 - Expected Output = 1
    vector<int> nums2 = {1,4,4};
    int target2 = 4;
    cout << "Test #2 Actual Output: " << minSubArrayLen(target2, nums2) << "\n";

    // Test Case #3 - Expected Output = 0
    vector<int> nums3 = {1,1,1,1,1,1,1,1};
    int target3 = 11;
    cout << "Test #3 Actual Output: " << minSubArrayLen(target3, nums3) << "\n";

    // Test Case #4 - Expected Output = 3
    vector<int> nums4 = {1,2,3,4,5};
    int target4 = 11;
    cout << "Test #4 Actual Output: " << minSubArrayLen(target4, nums4) << "\n";

    return 0;
}    