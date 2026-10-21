#include <string>
#include <vector>
#include <charconv>

//==============================================================================
// LeetCode #271 / NeetCode: Encode and Decode Strings
// Strategy: Length-Prefixed Frame Serialization with Zero-Copy Scanning
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - encode(): O(N) linear sweep across total serialized character stream length.
      - decode(): O(N) single linear scan parsing length headers and bulk slicing.
    - Auxiliary Space:
      - encode(): O(1) beyond the reserved destination buffer.
      - decode(): O(1) beyond the reserved output vector.

    Algorithmic & Hardware Invariants:
    1. Zero Mid-Traversal Buffer Reallocation:
       - encode() computes total byte payload upfront to reserve exact storage,
         preventing heap reallocations and pointer chasing.
    2. Substring & Memory Copy Optimization:
       - decode() parses integer headers in-place via string search and extracts
         payload chunks using direct range construction (underlying memcpy) rather
         than character-by-character concatenation.
    3. Delimiter Ambiguity Immunity:
       - Escapes arbitrary payload characters (including '#', whitespace, and null bytes)
         by bounding reading boundaries strictly by parsed length headers.
*/

std::string encode(const std::vector<std::string>& strs)
{
    size_t totalBytes = 0;
    for (const std::string& str : strs)
    {
        // Account for length digits + '#' delimiter + payload bytes
        totalBytes += std::to_string(str.size()).size() + 1 + str.size();
    }

    std::string result;
    result.reserve(totalBytes);

    for (const std::string& str : strs)
    {
        result += std::to_string(str.size());
        result.push_back('#');
        result += str;
    }

    return result;
}

std::vector<std::string> decode(const std::string& s)
{
    std::vector<std::string> result;
    const size_t len = s.length();
    size_t i = 0;

    while (i < len)
    {
        // Locate delimiter directly using contiguous memory search
        const size_t delimiterPos = s.find('#', i);
        if (delimiterPos == std::string::npos)
        {
            break;
        }

        // Parse integer frame length directly from string slice without temp string allocations
        size_t strLen = 0;
        std::from_chars(s.data() + i, s.data() + delimiterPos, strLen);

        // Advance index past delimiter
        const size_t payloadStart = delimiterPos + 1;

        // Extract payload using bulk range construction (SIMD memcpy)
        result.emplace_back(s.data() + payloadStart, strLen);

        // Shift index to the next frame header
        i = payloadStart + strLen;
    }

    return result;
}

// std::string encode(const std::vector<std::string> &strs)
// {
//     std::string result;

//     for (const std::string &str : strs)
//     {
//         result += (std::to_string(str.size()) + "#" + str);
//     }

//     return result;
// }

// std::vector<std::string> decode(const std::string &s)
// {
//     const int len = static_cast<int>(s.length());
//     int i = 0;
//     std::vector<std::string> result;

//     while (i < len)
//     {
//         std::string temp;
//         while (i < len && s[i] != '#')
//         {
//             temp += s[i];
//             ++i;
//         }

//         int size = std::stoi(temp);
//         temp.clear();
//         int j = 0;
//         ++i; // Skip separator character

//         while (i < len && j < size)
//         {
//             temp += s[i];
//             ++i;
//             ++j;
//         }

//         result.push_back(temp);
//     }

//     return result;
// }