#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include <unordered_map>

using namespace std;

//-------------- Brute Force Method # 1- Time Complexity O(N^3) --------------
// int lengthOfLongestSubstring(string s)
// {
//     // Worst edge case
//     if (s.empty()) return 0;

//     string substr = "";
//     int maxLen = INT_MIN;

//     for (size_t i = 0; i < s.length(); i++)
//     {
//         substr += s[i];

//         for (size_t j = i + 1; j < s.length(); j++)
//         {
//             // While dupe char not found, continue concatenating to string
//             if (substr.find_first_of(s[j]) == string::npos)
//             {
//                 // Note: string::find_first_of is a linear search which will cause the O(N^3) worst case
//                 substr += s[j];
//             }
//             // If dupe found, break from inner loop
//             else
//             {
//                 break;
//             }
//         }

//         maxLen = max(maxLen, static_cast<int>(substr.length()));
//         substr.erase();
//     }

//     return (maxLen == INT_MIN) ? 1 : maxLen;
// }

//-------------- Brute Force Method #2 - Time Complexity O(N^2) --------------
// int lengthOfLongestSubstring(string s)
// {
//     // Worst edge case
//     if (s.empty()) return 0;

//     string substr = "";
//     int maxLen = 0;

//     for (size_t i = 0; i < s.length(); i++)
//     {
//         // O(1) space direct-address table to check character existence in O(1) time
//         bool seen[256] = {false};
//         int currentLen = 0;

//         for (size_t j = i; j < s.length(); j++)
//         {
//             unsigned char currentChar = static_cast<unsigned char>(s[j]);

//             // Duplicate found in current window starting at i
//             if (seen[currentChar])
//             {
//                 break;
//             }

//             seen[currentChar] = true;
//             currentLen++;
//         }

//         maxLen = max(maxLen, currentLen);
//     }

//     return maxLen;
// }

//-------------- Optimized Method - Time Complexity O(N) --------------
int lengthOfLongestSubstring(string s)
{
    // Worst edge case
    if (s.empty()) return 0;

    unordered_map<char, int> lastSeen;
    int maxLen = 0, leftBound = 0;

    for (size_t i = 0; i < s.length(); i++)
    {
        char currentChar = s[i];

        // Only update leftBound if currentChar seen prior and its index >= leftBound
        if (lastSeen.find(currentChar) != lastSeen.end() && lastSeen[currentChar] >= leftBound)
        {
            leftBound = lastSeen[currentChar] + 1;
        }

        lastSeen[currentChar] = (int)i;
        maxLen = max(maxLen, (int)i - leftBound + 1);
    }

    return maxLen;
}

int main()
{
    // Test Case #1 - Expected Output = 3
    string s1 = "abcabcbb";
    cout << "Test #1 Actual Output: " << lengthOfLongestSubstring(s1) << "\n";

    // Test Case #2 - Expected Output = 1
    string s2 = "bbbbb";
    cout << "Test #2 Actual Output: " << lengthOfLongestSubstring(s2) << "\n";

    // Test Case #3 - Expected Output = 3
    string s3 = "pwwkew";
    cout << "Test #3 Actual Output: " << lengthOfLongestSubstring(s3) << "\n";

    // Test Case #4 - Expected Output = 2
    string s4 = "mq";
    cout << "Test #4 Actual Output: " << lengthOfLongestSubstring(s4) << "\n";

    // Test Case #5 - Expected Output = 4
    string s5 = "1R1T7";
    cout << "Test #5 Actual Output: " << lengthOfLongestSubstring(s5) << "\n";

    // Test Case #6 - Expected Output = 4
    string s6 = "bccddadcb";
    cout << "Test #6 Actual Output: " << lengthOfLongestSubstring(s6) << "\n";

    // Test Case #7 - Expected Output = 2
    string s7 = "edd";
    cout << "Test #7 Actual Output: " << lengthOfLongestSubstring(s7) << "\n";

    return 0;
}