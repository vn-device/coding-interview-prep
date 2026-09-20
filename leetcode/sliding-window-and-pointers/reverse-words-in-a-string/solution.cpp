#include <string>
#include <algorithm>

std::string reverseWords(std::string &s)
{
    const int len = static_cast<int>(s.length());
    int read = 0;
    int write = 0;

    while (read < len)
    {
        // Continue traverse if leading whitespace
        while (read < len && s[read] == ' ')
        {
            read++;
        }

        // Boundary check
        if (read >= len)
        {
            break;
        }

        // Add single whitespace b/w words
        if (write > 0)
        {
            s[write++] = ' ';
        }

        // Copy current word to write cursor
        while (read < len && s[read] != ' ')
        {
            s[write++] = s[read++];
        }
    }

    // Resize input buffer after truncating extra whitespace
    s.resize(write);

    // Reverse entire input buffer
    std::reverse(s.begin(), s.end());

    // Reverse individual words to be legible
    int start = 0;
    for (int i = 0; i <= write; i++)
    {
        if (i == write || s[i] == ' ')
        {
            std::reverse(s.begin() + start, s.begin() + i);
            start = i + 1;
        }
    }

    return s;
}