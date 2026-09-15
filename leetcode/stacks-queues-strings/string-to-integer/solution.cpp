#include <string>

int myAtoi(const std::string &s)
{
    // Account for (a - z) | (A - Z) | (0 - 9) | ( ) | (+) | (-) | (.)
    // Using sliding window to find valid substring
    const int len = static_cast<int>(s.length());
    int idx = 0;

    // Skip leading whitespace
    while (idx < len && s[idx] == ' ')
    {
        idx++;
    }

    // Search for optional value sign
    int sign = 1;

    if (s[idx] == '+' || s[idx] == '-')
    {
        sign = (s[idx] == '-') ? -1 : sign;
        idx++;
    }

    // Loop through digits and clamp overflow
    int value = 0;

    while (idx < len && s[idx] >= '0' && s[idx] <= '9')
    {
        int digit = s[idx] - '0';

        if (value > (INT_MAX - digit) / 10)
        {
            return (sign == 1) ? INT_MAX : INT_MIN;
        }

        value = value * 10 + digit;
        idx++;
    }

    return value * sign;
}