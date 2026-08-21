#include <string>
#include <unordered_map>
#include <array>

//==============================================================================
// Implementation #2: Fixed-Size Direct-Mapped Stack Array (Optimized)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N is the length of the strings.
      - Single unified loop scans both strings simultaneously in N iterations.
      - Final verification loop runs in constant time O(Σ) = O(26) = O(1).
    - Auxiliary Space: O(1) auxiliary memory.
      - Requires exactly 104 bytes (26 * sizeof(int)) on the program call stack.

    Key Performance & Architectural Optimizations:
    1. Zero Heap Allocations:
       - Replaces node-based associative containers with std::array<int, 26>.
       - Completely eliminates malloc/free syscalls and heap fragmentation.
    2. Optimal L1 Cache Locality & Vectorization:
       - The contiguous 26-integer buffer fits entirely within a single L1 data 
         cache line (64 bytes typically span 16 ints; array spans < 2 cache lines).
       - Enables tight register reuse and potential SIMD vectorization by modern compilers.
    3. Direct Arithmetic Indexing:
       - Replaces hashing algorithms, modulus bucket distribution, and collision handling 
         with a single O(1) pointer/offset calculation: (char - 'a').
    4. Dual Delta Balancing:
       - Simultaneously increments for string s and decrements for string t, reducing 
         the required tracking buffers from two maps down to a single delta array.
*/
bool isAnagram(const std::string &s, const std::string &t)
{
    if (s.length() != t.length())
    {
        return false;
    }

    // Direct-mapped frequency array for 'a' through 'z'
    std::array<int, 26> freqDelta{};

    const size_t n = s.length();
    for (size_t i = 0; i < n; ++i)
    {
        freqDelta[s[i] - 'a']++;
        freqDelta[t[i] - 'a']--;
    }

    // If s and t are valid anagrams, all frequency deltas must balance to 0
    for (int count : freqDelta)
    {
        if (count != 0)
        {
            return false;
        }
    }

    return true;
}

//==============================================================================
// Implementation #1: Dual Hash Map Approach (Initial Implementation)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N) where N is the length of strings s and t.
      - O(N) to traverse both strings and populate the hash maps.
      - O(K) to iterate through the unique keys (where K <= 26 for lowercase English letters).
    - Auxiliary Space: O(K) where K is the number of distinct characters.
      - Uses two separate dynamic std::unordered_map instances.

    Key Trade-offs & Systems Bottlenecks:
    1. Dynamic Heap Allocations:
       - std::unordered_map is a node-based hash table. Inserting elements 
         triggers heap allocations for buckets and linked-list node wrappers.
       - Maintaining two distinct map instances doubles dynamic memory overhead.
    2. Pointer Chasing & Cache Misses:
       - Bucket collisions and linked node chains reside in scattered heap locations, 
         reducing L1/L2 data cache locality during iteration.
    3. Redundant Map Probing:
       - Performing charDB1[key] inside the verification loop repeats a hash 
         computation and lookup even though iter1->second already holds the value.
    4. Generalization:
       - Handles arbitrary character sets (Unicode, UTF-8, symbols) without requiring 
         prior knowledge of alphabet bounds.
*/
// bool isAnagram(const std::string& s, const std::string& t)
// {
//     size_t size1 = s.length();
//     size_t size2 = t.length();

//     if (size1 != size2 || size1 == 0 || size2 == 0)
//     {
//         return false;
//     }

//     std::unordered_map<char, int> charDB1;
//     std::unordered_map<char, int> charDB2;

//     for (size_t i = 0; i < size1; i++)
//     {
//         charDB1[s[i]]++;
//         charDB2[t[i]]++;
//     }

//     for (auto iter1 = charDB1.begin(); iter1 != charDB1.end(); iter1++)
//     {
//         char key = iter1->first;
//         int count1 = charDB1[key];
//         int count2 = (charDB2.find(key) != charDB2.end()) ? charDB2[key] : 0;

//         if (count1 != count2)
//         {
//             return false;
//         }
//     }

//     return true;
// }