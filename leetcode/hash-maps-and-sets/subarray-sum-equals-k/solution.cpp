#include <vector>
#include <unordered_map>

//==============================================================================
// LeetCode #560: Subarray Sum Equals K
// Implementation: Initial Running Prefix Sum with Direct Hash Map Lookups (31 ms)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size().
      - Single-pass linear scan across the vector.
      - Performs two O(1) average hash lookups per element: find() and operator[].
    - Auxiliary Space: O(N) auxiliary heap memory.
      - std::unordered_map stores up to N + 1 distinct prefix sums.

    Key Invariants & Mechanism:
    1. Prefix Sum Identity:
       - Any contiguous subarray sum(i, j) equals prefix[j] - prefix[i - 1].
       - Setting sum(i, j) = k yields the target equation: prefix[i - 1] = prefix[j] - k.
    2. Online Directional Traversal:
       - Updating prefixSumFreq on the fly ensures that only valid prefixes appearing 
         before the current index (i <= j) are counted as matching starting points.
    3. Base Case Initialization:
       - Setting prefixSumFreq[0] = 1 accounts for valid subarrays starting at index 0.
*/
int subarraySum(const std::vector<int> &nums, int k)
{
    if (nums.empty())
    {
        return 0;
    }

    std::unordered_map<int, int> prefixSumFreq;

    int matches = 0;
    int runningSum = 0;
    prefixSumFreq[runningSum] = 1;

    for (const int &num : nums)
    {
        runningSum += num;

        int target = runningSum - k;
        auto iter = prefixSumFreq.find(target);
        if (iter != prefixSumFreq.end())
        {
            matches += iter->second;
        }

        prefixSumFreq[runningSum]++;
    }

    return matches;
}

//==============================================================================
// LeetCode #560: Subarray Sum Equals K
// Implementation: Initial Running Prefix Sum with Direct Hash Map Lookups (31 ms)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = nums.size()[cite: 5].
      - Single-pass linear scan across the vector[cite: 5].
      - Performs two O(1) average hash lookups per element: find() and operator[][cite: 5].
    - Auxiliary Space: O(N) auxiliary heap memory[cite: 5].
      - std::unordered_map stores up to N + 1 distinct prefix sums[cite: 5].

    Key Invariants & Mechanism:
    1. Prefix Sum Identity:
       - Any contiguous subarray sum(i, j) equals prefix[j] - prefix[i - 1][cite: 5].
       - Setting sum(i, j) = k yields the target equation: prefix[i - 1] = prefix[j] - k[cite: 5].
    2. Online Directional Traversal:
       - Updating prefixSumFreq on the fly ensures that only valid prefixes appearing 
         before the current index (i <= j) are counted as matching starting points[cite: 5].
    3. Base Case Initialization:
       - Setting prefixSumFreq[0] = 1 accounts for valid subarrays starting at index 0[cite: 5].
*/
// int subarraySum(const std::vector<int> &nums, int k)
// {
//     if (nums.size() <= 1)
//     {
//         return (nums.empty()) ? 0 : (nums[0] == k) ? 1 : 0;
//     }

//     std::unordered_map<int, int> prefixSumFreq;

//     int matches = 0;
//     int runningSum = 0;
//     prefixSumFreq[runningSum] = 1;

//     for (const int &num : nums)
//     {
//         runningSum += num;

//         int target = runningSum - k;
//         if (prefixSumFreq.find(target) != prefixSumFreq.end())
//         {
//             matches += prefixSumFreq[target];
//         }

//         prefixSumFreq[runningSum]++;
//     }

//     return matches;
// }