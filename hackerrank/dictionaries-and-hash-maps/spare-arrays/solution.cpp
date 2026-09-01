#include <vector>
#include <string>
#include <unordered_map>

//==============================================================================
// HackerRank: Sparse Arrays
// Strategy: Hash Map Frequency Aggregation with Single-Lookup Iterator Querying
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N * L + Q * L) where N = stringList.size(), Q = queries.size(),
      and L is the maximum string length.
      - Populating freqMap takes O(N * L) for string hashing and insertion.
      - Processing Q queries takes O(Q * L) using single-pass iterator lookups.
    - Auxiliary Space: O(U * L) auxiliary heap memory where U <= N is the number of 
      unique strings in stringList.
      - freqMap stores up to U unique string keys and their integer frequency counts.

    Algorithmic Invariants & State Design:
    1. Single Hash Traversal Invariant:
       - Captures find() iterator results directly (it->second), eliminating redundant 
         secondary hash computations caused by operator[].
    2. Lookup Safety Invariant:
       - Safely maps missing keys to 0 without mutating the underlying hash table.
*/
std::vector<int> matchingStrings(
    const std::vector<std::string>& stringList,
    const std::vector<std::string>& queries
)
{
    std::unordered_map<std::string, int> queryDB;
    queryDB.reserve(stringList.size());
    
    for (const std::string& str : stringList)
    {
        queryDB[str]++;
    }
    
    std::vector<int> results;
    results.reserve(queries.size());
    
    for (const std::string& str : queries)
    {
        const auto it = queryDB.find(str);
        results.push_back(it != queryDB.end() ? it->second : 0);
    }
    
    return results;
}