#include <string>

int myAtoi(const std::string &s)
{
    // Traverse thru leading whitespaces
    const int len = static_cast<int>(s.length());
    int read = 0;
    while (read < len && s[read] == ' ')
    {
        read++;
    }

    // Check for optional int signs & advance traversal if sign found
    int sign = 1;
    if (read < len && (s[read] == '+' || s[read] == '-'))
    {
        if (s[read] == '-')
        {
            sign = -1;
        }
        read++;
    }

    // Traverse thru valid digits
    int result = 0;

    while (read < len && s[read] >= '0' && s[read] <= '9')
    {
        int digit = s[read++] - '0';
        if (result > (INT_MAX - digit) / 10)
        {
            return (sign == 1) ? INT_MAX : INT_MIN;
        }

        result = result * 10 + digit;
    }

    return result * sign;
}