#include <vector>
#include <string>

int compress(std::vector<char>& chars)
{
    const int n = static_cast<int>(chars.size());
    int write = 0;
    int read = 0;

    while (read < n)
    {
        const char currentChar = chars[read];
        int count = 0;

        // Count contiguous duplicates
        while (read < n && chars[read] == currentChar)
        {
            ++read;
            ++count;
        }

        // Write the character
        chars[write++] = currentChar;

        // If count > 1, write each digit of the count
        if (count > 1)
        {
            std::string countStr = std::to_string(count);
            for (char digit : countStr)
            {
                chars[write++] = digit;
            }
        }
    }

    // write is the new effective size of the compressed sequence
    return write;
}