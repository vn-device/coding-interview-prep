#include <iostream>
#include <string>
#include <math.h>

using namespace std;

//-------------- Brute Force Method - Time Complexity O(N) --------------
string makeGood(const string& s)
{
    // Worst edge case scenario
    if (s.length() < 2) return s;

    // Using string stacking concept to check for adjacent upper/lower-case dupes 
    // Note: return string may (not) be same length as const string& s
    string stack = "";
    stack.reserve(s.length());

    for (char c : s)
    {
        // The decimal gap b/w upper/lower-case is 32 via ASCII
        if (!stack.empty() && abs(stack.back() - c) == 32)
        {
            stack.pop_back();
        }
        else
        {
            stack.push_back(c);
        }
    }

    return stack;
}

int main()
{
    // Test Case #1 - Expected Output = "leetcode"
    string s1 = "leEeetcode";
    cout << "Expected Test Case #1 Output = \"leetcode\"\n";
    cout << "  Actual Test Case #1 Output = \"" << makeGood(s1) << "\"\n\n";

    // Test Case #2 - Expected Output = ""
    string s2 = "abBAcC";
    cout << "Expected Test Case #2 Output = \"\"\n";
    cout << "  Actual Test Case #2 Output = \"" << makeGood(s2) << "\"\n\n";

    // Test Case #3 - Expected Output = "s"
    string s3 = "s";
    cout << "Expected Test Case #3 Output = \"s\"\n";
    cout << "  Actual Test Case #3 Output = \"" << makeGood(s3) << "\"\n\n";

    return 0;
}