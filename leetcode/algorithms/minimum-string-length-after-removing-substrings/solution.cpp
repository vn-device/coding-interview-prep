#include <iostream>
#include <string>

using namespace std;

//-------------- Optimized Method - Time Complexity O(N) --------------
int minLength(const string& s)
{
    // Problem goal: remove any occurrence of substr "AB" or "CD",
    //               then return the min possible string len after.

    // Worst edge case scenario
    if (s.length() < 2) return s.length();

    // Create string stack to track what length will be returned
    // Note: the returned string length may (not) be the same as s.length()
    string stack = "";
    stack.reserve(s.length());

    for (char c : s)
    {
        if (!stack.empty() && 
            ((stack.back() == 'A' && c == 'B') ||
            (stack.back() == 'C' && c == 'D')))
        {
            stack.pop_back();
        }
        else
        {
            stack.push_back(c);
        }
    }

    return static_cast<int>(stack.length());
}

int main()
{
    // Test Case #1 - Expected Output = 2
    string s1 = "ABFCACDB";
    cout << "Expected Test Case #1 Output = 2\n";
    cout << "  Actual Test Case #1 Output = " << minLength(s1) << "\n\n";

    // Test Case #2 - Expected Output = 5
    string s2 = "ACBBD";
    cout << "Expected Test Case #2 Output = 5\n";
    cout << "  Actual Test Case #2 Output = " << minLength(s2) << "\n\n";

    return 0;
}