#include <vector>
#include <string>
#include <unordered_map>
#include <array>

//==============================================================================
// LeetCode #49 / NeetCode: Group Anagrams
// Strategy: 26-Bin Character Frequency Serialization + True Move Semantics
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N * K) where N = strs.size() and K = maximum string length.
      - Frequency array counting runs in O(K) without sorting overhead.
      - Key serialization and hash probe runs in O(1) amortized time.
    - Auxiliary Space: O(N * K) bounded by anagramTable and returned groups.

    Algorithmic & Hardware Invariants:
    1. Elimination of O(K log K) Sorting:
       - Generates a delimiter-separated 26-element frequency key, ensuring O(K) linear
         fingerprinting per string.
    2. Zero-Copy Drain (Move Semantics):
       - Iterating over non-const auto& allows std::move to steal internal heap
         pointers directly into 'groups', completely eliminating deep string copies.
    3. Rehash Prevention:
       - anagramTable.reserve(strs.size()) pre-allocates bucket capacity to prevent
         dynamic map reallocations during insertion.
*/
std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs)
{
    std::unordered_map<std::string, std::vector<std::string>> anagramTable;
    anagramTable.reserve(strs.size());

    for (const std::string& str : strs)
    {
        std::array<int, 26> count{};
        for (const char c : str)
        {
            ++count[static_cast<unsigned char>(c) - 'a'];
        }

        // Build a unique serialized key: e.g. "#1#0#2..."
        std::string key;
        key.reserve(52);
        for (const int freq : count)
        {
            key.push_back('#');
            key.append(std::to_string(freq));
        }

        anagramTable[key].push_back(str);
    }

    std::vector<std::vector<std::string>> groups;
    groups.reserve(anagramTable.size());

    // Iterate by non-const reference to ensure std::move invokes the move constructor
    for (auto& pair : anagramTable)
    {
        groups.push_back(std::move(pair.second));
    }

    return groups;
}

// std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string> &strs)
// {
//     std::unordered_map<std::string, std::vector<std::string>> anagramsTable;
//     anagramsTable.reserve(strs.size());

//     for (const std::string &str : strs)
//     {
//         std::string temp = str;
//         std::sort(temp.begin(), temp.end());
//         anagramsTable[temp].push_back(str);
//     }

//     std::vector<std::vector<std::string>> groups;
//     groups.reserve(anagramsTable.size());

//     for (const auto &iter : anagramsTable)
//     {
//         groups.push_back(std::move(iter.second));
//         // groups.push_back(iter.second);
//     }

//     return groups;
// }