#include <array>
#include <string>

//==============================================================================
// LeetCode #383: Ransom Note
// Strategy: Direct-Mapped Stack Frequency Inventory & Early Pruning
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(M + N) where M is magazine length and N is ransomNote length.
      - O(M) to build the frequency inventory of available characters in the magazine.
      - O(N) worst-case scan through ransomNote to validate availability.
      - Early termination occurs immediately upon encountering any character deficit (< 0).
    - Auxiliary Space: O(1) auxiliary space (O(Σ) where alphabet size Σ = 26).
      - Allocates exactly 104 bytes on the call stack using std::array<int, 26>.
      - Zero dynamic memory allocations (no heap fragmentation or syscalls).

    Architectural & Hardware Notes:
    1. Direct-Offset Indexing:
       - Eliminates hash computation overhead and bucket collision resolution 
         by utilizing pointer/scalar offset indexing: (char - 'a').
    2. Cache Efficiency:
       - The contiguous 26-integer buffer fits entirely within a single 64-byte L1 
         data cache line pair, ensuring minimal L1/L2 cache miss latency.
    3. Structural Invariant:
       - Short-circuits in O(1) time if ransomNote.length() > magazine.length(), 
         as a multiset subset cannot exceed the source cardinality.
*/
bool canConstruct(const std::string& ransomNote, const std::string& magazine)
{
    size_t ransomSize = ransomNote.length();
    size_t magazineSize = magazine.length();

    if (ransomSize == 0 || magazineSize == 0 || ransomSize > magazineSize)
    {
        return false;
    }

    std::array<int, 26> charTracker{};
    for (size_t i = 0; i < magazineSize; i++)
    {
        // Track the freq of an occurring character
        charTracker[magazine[i] - 'a']++;
    }

    for (const char &c : ransomNote)
    {
        charTracker[c - 'a']--;
        if (charTracker[c - 'a'] < 0)
        {
            return false;
        }
    }

    return true;
}