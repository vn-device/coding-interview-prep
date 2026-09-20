#include <string>

bool isNumber(const std::string &s)
{
    const int len = static_cast<int>(s.length());

    bool seenDigit = false;
    bool seenDot = false;
    bool seenExponent = false;

    for (int i = 0; i < len; ++i)
    {
        const char c = s[i];

        if (c >= '0' && c <= '9')
        {
            seenDigit = true;
        }
        else if (c == '+' || c == '-')
        {
            // Sign is valid ONLY at index 0 or immediately following 'e'/'E'
            if (i > 0 && s[i - 1] != 'e' && s[i - 1] != 'E')
            {
                return false;
            }
        }
        else if (c == '.')
        {
            // Dot is invalid if we already saw a dot OR an exponent
            if (seenDot || seenExponent)
            {
                return false;
            }
            seenDot = true;
        }
        else if (c == 'e' || c == 'E')
        {
            // Exponent is invalid if already seen, or if no digits preceded it
            if (seenExponent || !seenDigit)
            {
                return false;
            }
            seenExponent = true;
            // Must have at least one digit AFTER the exponent
            seenDigit = false;
        }
        else
        {
            // Any other character (letters, spaces) is invalid
            return false;
        }
    }

    // A valid number must end having consumed at least one valid digit in the active section
    return seenDigit;
}