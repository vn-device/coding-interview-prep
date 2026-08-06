#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

//-------------- Brute Force Method - Time Complexity O(N^2) --------------
// int maxSubArray(vector<int>& nums)
// {
//     if (nums.empty() || nums.size() == 1)
//         return nums.empty() ? 0 : nums[0];

//     int maxSum = INT_MIN;
//     for (size_t i = 0; i < nums.size(); i++)
//     {
//         int currentSum = 0;
//         for (size_t j = i; j < nums.size(); j++)
//         {
//             currentSum += nums[j];
//             maxSum = max(maxSum, currentSum);
//         }
//     }

//     return maxSum;
// }
//-------------- Brute Force Method - Failed LeetCode's Time Limit Exceeding Test --------------

//-------------- Optimized Method - Time Complexity O(N) --------------
int maxSubArray(vector<int>& nums)
{
    // Worst edge case scenario and very easy to consider
    if (nums.empty() || nums.size() == 1)
        return nums.empty() ? 0 : nums[0];

    int maxSum = nums[0], currentSum = nums[0];
    
    // Using "Kadane's Algorithm"
    for (size_t i = 1; i < nums.size(); i++)
    {
        // Reset to nums[i] if currentSum was negative/dragging, else extend contiguous sum
        currentSum = max(nums[i], nums[i] + currentSum);
        maxSum = max(maxSum, currentSum);
    }

    return maxSum;
}

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Test Case #1 - Expected Output = 6
    vector<int> nums1 = {-2,1,-3,4,-1,2,1,-5,4};
    cout << "Test Case #1 Output = " << maxSubArray(nums1) << "\n";

    // Test Case #2 - Expected Output = 1
    vector<int> nums2 = {1};
    cout << "Test Case #2 Output = " << maxSubArray(nums2) << "\n";

    // Test Case #3 - Expected Output = 23
    vector<int> nums3 = {5,4,-1,7,8};
    cout << "Test Case #3 Output = " << maxSubArray(nums3) << "\n";
    return 0;
}