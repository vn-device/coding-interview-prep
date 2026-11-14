#include <string>

//==============================================================================
// LeetCode #125 / NeetCode: Valid Palindrome
// Strategy: Converging Two-Pointer In-Place Scan with Branch-Minimized ASCII Folding
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = s.length().
      - Single converging pass where 'left' and 'right' each visit at most N/2 bytes.
    - Auxiliary Space: O(1) strictly stack-resident scalar indices.
      - Zero heap allocations or string copies.

    Algorithmic & Hardware Invariants:
    1. Disjoint ASCII Domain Preservation:
       - Folding uppercase letters ('A'-'Z') into lowercase ('a'-'z') via (+32)
         preserves disjoint ASCII intervals for digits [48..57] and letters [97..122],
         eliminating explicit letter-vs-digit collision checks.
    2. Locale-Free Inline Classification:
       - Direct range comparisons avoid <cctype> global locale table indirection.
*/
inline bool isAlphaNumeric(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9');
}

inline char toLowerAscii(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return static_cast<char>(c + ('a' - 'A'));
    }

    return c;
}

bool isPalindrome(const std::string& s)
{
    int left = 0;
    int right = static_cast<int>(s.length()) - 1;

    while (left < right)
    {
        // Advance left pointer past non-alphanumeric characters
        while (left < right && !isAlphaNumeric(s[left]))
        {
            ++left;
        }

        // Retreat right pointer past non-alphanumeric characters
        while (left < right && !isAlphaNumeric(s[right]))
        {
            --right;
        }

        if (toLowerAscii(s[left]) != toLowerAscii(s[right]))
        {
            return false;
        }

        ++left;
        --right;
    }

    return true;
}

// bool isAlphabet(char c)
// {
//     bool b1 = (c >= 'A' && c <= 'Z');
//     bool b2 = (c >= 'a' && c <= 'z');
//     return b1 || b2;
// }

// bool isNumeric(char c)
// {
//     return (c >= '0' && c <= '9');
// }

// bool isPalindrome(const std::string& s)
// {
//     const int len = static_cast<int>(s.length());
//     int left = 0;
//     int right = len - 1;

//     while (left < right)
//     {
//         char c1 = s[left];
//         char c2 = s[right];

//         if (!isAlphabet(c1) && !isNumeric(c1))
//         {
//             ++left;
//             continue;
//         }
//         else if (!isAlphabet(c2) && !isNumeric(c2))
//         {
//             --right;
//             continue;
//         }

//         if (isAlphabet(c1) && isNumeric(c2) ||
//             isAlphabet(c2) && isNumeric(c1))
//         {
//             return false;
//         }

//         if (c1 >= 'A' && c1 <= 'Z')
//         {
//             c1 -= 'A';
//         }
//         else if (c1 >= 'a' && c1 <= 'z')
//         {
//             c1 -= 'a';
//         }
//         else // if (c1 >= '0' && c1 <= '9')
//         {
//             c1 -= '0';
//         }

//         if (c2 >= 'A' && c2 <= 'Z')
//         {
//             c2 -= 'A';
//         }
//         else if (c2 >= 'a' && c2 <= 'z')
//         {
//             c2 -= 'a';
//         }
//         else // if (c2 >= '0' && c2 <= '9')
//         {
//             c2 -= '0';
//         }

//         if (c1 != c2)
//         {
//             return false;
//         }

//         ++left;
//         --right;
//     }

//     return true;
// }