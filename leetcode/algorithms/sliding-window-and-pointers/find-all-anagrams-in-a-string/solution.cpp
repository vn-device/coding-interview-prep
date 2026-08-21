#include <string>
#include <vector>
#include <array>

//==============================================================================
// LeetCode #438: Find All Anagrams in a String
//==============================================================================
/*
    Complexity Analysis:
    - Initial Approach: O(|S| * |P|) Time | O(|P|) Space
      - Triggered heavy heap fragmentation via repeated s.substr() string copies.
      - Repeated full re-evaluations and array resets on every index step.
    - Optimized Sliding Window: O(|S|) Time | O(1) Space (52 ints on stack)
      - Incremental O(1) window shift: +1 right incoming char, -1 left outgoing char.
      - Eliminates all dynamic heap allocations inside the loop.
*/
std::vector<int> findAnagrams(const std::string &s, const std::string &p)
{
    const size_t sLen = s.length();
    const size_t pLen = p.length();

    if (sLen < pLen)
    {
        return {};
    }

    std::array<int, 26> pFreq{};
    std::array<int, 26> sFreq{};

    // Populate baseline frequency for p and initial window in s
    for (size_t i = 0; i < pLen; ++i)
    {
        pFreq[p[i] - 'a']++;
        sFreq[s[i] - 'a']++;
    }

    std::vector<int> result;
    // Upper bound on possible anagram start locations
    result.reserve(sLen - pLen + 1);

    // Check initial window at index 0
    if (sFreq == pFreq)
    {
        result.push_back(0);
    }

    // Slide the window across s one character at a time
    for (size_t i = pLen; i < sLen; ++i)
    {
        // Add incoming character from the right
        sFreq[s[i] - 'a']++;

        // Remove outgoing character from the left
        sFreq[s[i - pLen] - 'a']--;

        // O(1) comparison (26 elements)
        if (sFreq == pFreq)
        {
            result.push_back(static_cast<int>(i - pLen + 1));
        }
    }

    return result;
}

//==============================================================================
// LeetCode #438: Find All Anagrams in a String
// Implementation: Naive Substring Extraction & Full Window Rescan
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(|S| * |P|) where |S| is the length of s and |P| is the length of p[cite: 7].
      - Outer loop executes (|S| - |P| + 1) times[cite: 7].
      - Inside the loop, s.substr(i, size2) copies |P| characters[cite: 7].
      - The inner verification loop iterates up to |P| characters to decrement frequencies[cite: 7].
      - Full reset loop executes 26 iterations per window position to restore state[cite: 7].
    - Auxiliary Space: O(|P|) auxiliary heap space (excluding the output vector)[cite: 7].
      - Repeatedly allocates dynamic heap buffers for temporary substring copies[cite: 7].
      - Maintains two 26-element stack arrays (charTracker, backupTracker)[cite: 7].

    Systems Bottlenecks & Failure Modes:
    1. Dynamic Memory Allocation Inside Hot Loop:
       - Invoking std::string::substr() on every iteration forces repeated dynamic heap 
         allocations and deallocations[cite: 7], introducing substantial heap fragmentation 
         and memory allocator locks.
    2. Redundant Full-Window Recomputation:
       - Recalculates frequency counts from scratch for every window instead of 
         incrementally sliding the window boundary (adding right, removing left).
    3. State Restoration Overhead:
       - Requires copying the entire backupTracker array back into charTracker on every step[cite: 7], 
         leading to unnecessary memory writes across iterations.
*/
// std::vector<int> findAnagrams(const std::string& s, const std::string& p)
// {
//     size_t size1 = s.length();
//     size_t size2 = p.length();

//     if (size1 == 0 || size2 == 0 || size1 < size2)
//     {
//         return {};
//     }

//     std::array<int, 26> charTracker{};
//     std::array<int, 26> backupTracker{};
//     for (char c : p)
//     {
//         charTracker[c - 'a']++;
//         backupTracker[c - 'a']++;
//     }

//     std::vector<int> indices;
//     indices.reserve(size1);

//     for (size_t i = 0; i + size2 <= size1; i++)
//     {
//         std::string sub = s.substr(i, size2);
//         bool isAnagram = true;

//         for (char c : sub)
//         {
//             charTracker[c - 'a']--;
//             if (charTracker[c - 'a'] < 0)
//             {
//                 isAnagram = false;
//                 break;
//             }
//         }

//         // Reset charTracker
//         for (size_t j = 0; j < charTracker.size(); j++)
//         {
//             charTracker[j] = backupTracker[j];
//         }

//         if (isAnagram)
//         {
//             indices.push_back(static_cast<int>(i));
//         }
//     }

//     return indices;
// }