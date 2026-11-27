#include <string>
#include <algorithm>
#include <cstring>

//==============================================================================
// LeetCode #3 / NeetCode: Longest Substring Without Repeating Characters
// Strategy: Dynamic Sliding Window with Direct-Address ASCII Last-Seen Jump Table
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N = s.length().
      - Single forward pass; 'right' visits each byte once and 'left' jumps
        monotonically forward in O(1) without inner contraction loops.
    - Auxiliary Space: O(1) strictly stack-resident 512-byte lookup table.
      - Replaces std::unordered_map<char, int> heap buckets with a 128-int array
        fitting inside 8 L1 cache lines.

    Algorithmic & Hardware Invariants:
    1. Monotonic Left-Boundary Jump:
       - If s[right] was previously seen at an index >= left, 'left' jumps directly
         to lastSeen[c] + 1, evicting the duplicate and all preceding characters
         in a single assignment.
    2. Direct-Address ASCII Indexing:
       - Indexing via static_cast<unsigned char>(s[right]) avoids hash computation,
         bucket collision probing, and signed-char negative offset UB.
*/
int lengthOfLongestSubstring(const std::string& s)
{
    int lastSeen[256];
    std::memset(lastSeen, -1, sizeof(lastSeen));

    const int len = static_cast<int>(s.length());
    int left = 0;
    int longest = 0;

    for (int right = 0; right < len; ++right)
    {
        const unsigned char c = static_cast<unsigned char>(s[right]);

        if (lastSeen[c] >= left)
        {
            left = lastSeen[c] + 1;
        }

        lastSeen[c] = right;
        longest = std::max(longest, right - left + 1);
    }

    return longest;
}