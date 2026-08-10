#include <iostream>
#include <string>

using namespace std;

//-------------- Optimized Method - Time Complexity O(N) --------------
string removeDuplicates(const string& s)
{
    // Worst edge case scenario
    if (s.length() < 2) return s;

    // String stack may (not) be of equal length to const string& s
    string stack = "";
    stack.reserve(s.length());

    for (char c : s)
    {
        if (!stack.empty() && stack.back() == c)
            stack.pop_back();
        else
            stack.push_back(c);
    }

    return stack;
}

int main()
{
    // Test Case #1 - Expected Output = "ca"
    string s1 = "abbaca";
    cout << "Expected Test Case #1 Output = \"ca\"\n";
    cout << "  Actual Test Case #1 Output = \"" << removeDuplicates(s1) << "\"\n\n";

    // Test Case #2 - Expected Output = "ay"
    string s2 = "azxxzy";
    cout << "Expected Test Case #2 Output = \"ay\"\n";
    cout << "  Actual Test Case #2 Output = \"" << removeDuplicates(s2) << "\"\n\n";

    return 0;
}