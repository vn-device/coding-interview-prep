#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

//-------------- Brute Force Method - Time Complexity O(N^2) --------------
// int subarraySum(vector<int>& nums, int k)
// {
//     if (nums.size() == 0) return 0;

//     int subCount = 0;
//     for (size_t i = 0; i < nums.size(); i++)
//     {
//         int sum = 0;
//         for (size_t j = i; j < nums.size(); j++)
//         {
//             sum += nums[j];
//             if (sum == k)
//                 subCount++;
//         }
//     }
    
//     return subCount;
// }

//-------------- Optimized Method - Time Complexity O(?) --------------
int subarraySum(vector<int>& nums, int k)
{
    // Worst edge case scenario
    if (nums.size() == 0) return 0;

    // Hash map configuration: <prefixSum, frequency>
    unordered_map<int, int> sumTracker;
    
    // Base case: A cumulative prefix sum of 0 has occurred once prior to index 0
    sumTracker[0] = 1;

    int runningSum = 0, subCount = 0;
    for (size_t i = 0; i < nums.size(); i++)
    {
        // Search for current target in hash table -> add full freq to subCount if exists 
        runningSum += nums[i];
        if (sumTracker.find(runningSum - k) != sumTracker.end())
        {
            subCount += sumTracker[runningSum - k];
        }

        // unordered_map::operator[] auto inits missing keys to 0
        // Increment frequency count for current runningSum
        sumTracker[runningSum]++;
    }

    return subCount;
}

int main()
{
    // Test case #1 - Expected Result = 2
    vector<int> nums1 = {1, 1, 1};
    int k1 = 2;
    cout << "Test #1 subarraySum(nums1, k1), output: " << subarraySum(nums1, k1) << "\n";

    // Test case #2 - Expected Result = 2
    vector<int> nums2 = {1, 2, 3};
    int k2 = 3;
    cout << "Test #2 subarraySum(nums2, k2), output: " << subarraySum(nums2, k2) << "\n";

    return 0;
}