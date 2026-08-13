#include <iostream>
#include <vector>

using namespace std;

//-------------- Brute Force Method - Time Complexity O(N^2) --------------
// vector<int> productExceptSelf(vector<int>& nums)
// {
//     // Worst edge case scenario
//     if (nums.empty()) return {};

//     // Based on 1st 2 cases, returning vector is same size as input nums?
//     vector<int> answer;
//     answer.reserve(nums.size());

//     for (size_t i = 0; i < nums.size(); i++)
//     {
//         int product = 1;

//         for (size_t j = 0; j < nums.size(); j++)
//         {
//             if (i != j) product *= nums[j];
//         }

//         answer.push_back(product);
//     }

//     return answer;
// }
//-------------- Brute Force Method - Failed LeetCode's Time Limit Exceeding Test --------------

//-------------- Optimized Method - Time Complexity O(N) --------------
vector<int> productExceptSelf(vector<int>& nums)
{
    // Worst edge case scenario
    if (nums.empty()) return {};

    // Start prefix product container with answer[0] = 1
    vector<int> answer = {1};

    // Forward Pass: Calculate prefix products (left of element i)
    for (size_t i = 1; i < nums.size(); i++)
    {
        answer.push_back(answer[i - 1] * nums[i - 1]);
    }

    // Backward Pass: Multiply by running suffix product (right of element i)
    int rightProduct = 1;
    for (int i = answer.size() - 1; i >= 0; i--)
    {
        answer[i] *= rightProduct;
        rightProduct *= nums[i];
    }

    return answer;
}

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Test Case #1 - Expected Result = {24,12,8,6}
    vector<int> nums1 = {1, 2, 3, 4};
    vector<int> result1 = productExceptSelf(nums1);
    cout << "Case #1 - Actual Output =   {";
    for (size_t i = 0; i < result1.size(); i++)
    {
        if (i == result1.size() - 1)
            cout << result1[i] << "}\n";
        else
            cout << result1[i] << ",";
    }
    cout << "Case #1 - Expected Output = {24,12,8,6}\n\n";

    // Test Case #2 - Expected Result = {0,0,9,0,0}
    vector<int> nums2 = {-1,1,0,-3,3};
    vector<int> result2 = productExceptSelf(nums2);
    cout << "Case #2 - Actual Output =   {";
    for (size_t i = 0; i < result2.size(); i++)
    {
        if (i == result2.size() - 1)
            cout << result2[i] << "}\n";
        else
            cout << result2[i] << ",";
    }
    cout << "Case #2 - Expected Output = {0,0,9,0,0}\n\n";

    return 0;
}