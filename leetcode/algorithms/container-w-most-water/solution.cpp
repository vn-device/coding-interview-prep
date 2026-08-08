#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//-------------- Brute Force Method - Time Complexity O(N^2) --------------
// int maxArea(vector<int>& height)
// {
//     // Worst edge case scenarios (Must have min of 2 heights to find area)
//     if (height.size() < 2) return 0;

//     // Start at area = 0, since area will never be negative
//     int largestArea = 0;
//     for (size_t leftBound = 0; leftBound < height.size(); leftBound++)
//     {
//         int leftHeight = height[leftBound];

//         // Offset rightBound by 1 at beginning to skip current index
//         for (size_t rightBound = leftBound + 1; rightBound < height.size(); rightBound++)
//         {
//             int usableHeight = min(leftHeight, height[rightBound]);
//             int width = rightBound - leftBound;
//             largestArea = max(largestArea, usableHeight * width);
//         }
//     }

//     return largestArea;
// }
//-------------- Brute Force Method - Failed LeetCode's Time Limit Exceeding Test --------------

//-------------- Optmized Method - Time Complexity O(N) --------------
int maxArea(vector<int>& height)
{
    // Worst edge case scenarios (Must have min of 2 heights to find area)
    if (height.size() < 2) return 0;

    // Using 2-Pointer Method
    // Start at area = 0, since area will never be negative
    int largestArea = 0;
    size_t leftBound = 0, rightBound = height.size() - 1;
    
    // leftBound must never cross over or equal to rightBound, otherwise width = 0
    while (leftBound < rightBound)
    {
        int usableHeight = min(height[leftBound], height[rightBound]);
        int width = static_cast<int>(rightBound - leftBound);
        int newArea = usableHeight * width;

        // We need to shift our boundaries
        if (height[leftBound] < height[rightBound])
        {
            leftBound++;
        }
        else if (height[leftBound] >= height[rightBound])
        {
            rightBound--;
        }

        // Update regardless of shifting
        largestArea = max(largestArea, newArea);
    }

    return largestArea;
}

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Test Case #1 - Expected Result = 49
    vector<int> heights1 = {1,8,6,2,5,4,8,3,7};
    cout << "Test Case #1 Actual Output = " << maxArea(heights1) << ", Expected Output = 49\n";

    // Test Case #2 - Expected Result = 1
    vector<int> heights2 = {1,1};
    cout << "Test Case #2 Actual Output = " << maxArea(heights2) << ", Expected Output = 1\n";

    // Test Case #3 - Expected Result = 7
    vector<int> heights3 = {8,7,2,1};
    cout << "Test Case #3 Actual Output = " << maxArea(heights3) << ", Expected Output = 7\n";

    // Test Case #4 - Expected Result = 7
    vector<int> heights4 = {1,3,2,5,25,24,5};
    cout << "Test Case #4 Actual Output = " << maxArea(heights4) << ", Expected Output = 24\n";

    return 0;
}