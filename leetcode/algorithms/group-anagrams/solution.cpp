#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

//---------- Implementation #3 (In-Place Key Construction & Natural Boundary Handling) ----------
/*
    Optimal Strategy: O(N * K log K) Time | O(N * K) Auxiliary Space

    Improvements over Implementation #2:

    1. Temporary Array Allocation Elimination:
       Replaces the full std::vector<std::string> copy of the input array with a 
       lightweight local key variable during range-based iteration. This avoids 
       O(N * K) heap memory allocation up front and eliminates vector index tracking.

    2. Edge-Case Boundary Normalization:
       Removes the if (strs.size() < 2) guard clause entirely. This fixes a subtle bug 
       where an empty input vector (strs.size() == 0) incorrectly returned [{" "}] 
       instead of an empty container []. The map-building loop naturally handles 
       N = 0 and N = 1 cleanly.

    3. Cleaner Range-Based Syntax:
       Replaces iterator pointer dereferencing (iter->second) with const auto& pair 
       iteration over anagramsDB for improved readability and C++14/17 compliance.
*/
std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs)
{
    std::unordered_map<std::string, std::vector<std::string>> anagramsDB;
    for (const std::string& word : strs)
    {
        std::string key = word;
        std::sort(key.begin(), key.end());
        anagramsDB[key].push_back(word);
    }

    std::vector<std::vector<std::string>> anagramGroups;
    anagramGroups.reserve(anagramsDB.size());
    
    for (const auto& pair : anagramsDB)
    {
        anagramGroups.push_back(pair.second);
    }

    return anagramGroups;
}

//---------- Implementation #2 (Sorted Canonical Key Map Aggregation) ----------
/*
    Optimal Strategy: O(N * K log K) Time | O(N * K) Auxiliary Space

    Improvements over Implementation #1:

    1. Map Bucket Aggregation:
       Maps each string's sorted character sequence (canonical key) directly to its 
       vector bucket in std::unordered_map<std::string, std::vector<std::string>>. 
       This eliminates the nested pairwise loop and reduces runtime to O(N * K log K).

    2. Duplicate Value Resilience:
       Automatically handles identical duplicate strings (e.g., ["eat", "eat"]) without 
       failing inequality checks or requiring suppression sets, as duplicates append 
       naturally to the matching key vector.

    3. Memory Footprint Optimization:
       Replaces the full vector copy (std::vector<std::string> anagrams(strs)) with 
       in-place string key sorting during iteration, avoiding redundant array allocations.
*/
// std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs)
// {
//     if (strs.size() < 2)
//     {
//         return {strs};
//     }

//     std::vector<std::string> anagrams(strs);
//     std::unordered_map<std::string, std::vector<std::string>> anagramsDB;

//     for (size_t i = 0; i < anagrams.size(); i++)
//     {
//         std::sort(anagrams[i].begin(), anagrams[i].end());
//         anagramsDB[anagrams[i]].push_back(strs[i]); 
//     }

//     std::vector<std::vector<std::string>> anagramGroups;
//     anagramGroups.reserve(anagramsDB.size());

//     for (auto iter = anagramsDB.begin(); iter != anagramsDB.end(); iter++)
//     {
//         anagramGroups.push_back(iter->second);
//     }

//     return anagramGroups;
// }

//---------- Implementation #1 (Nested Pairwise Matching & Set Suppression) ----------
/*
    Sub-Optimal Strategy: O(N^2 * K log K) Time | O(N * K) Auxiliary Space
    Test Case Result: Passed 66 / 129 Cases

    1. Failure Modes:
       - Duplicate Raw Strings: The condition (strs[i] != strs[j]) skips duplicate word 
         entries in the input array (e.g., ["eat", "eat"]), dropping identical anagram 
         instances from output groups.
       - Raw Value Suppression: Tracking processed strings via std::unordered_set<std::string> 
         prevents duplicate values at different indices from being grouped correctly.
       - O(N^2) Pairwise Loop: Compares every word against all other words in an outer/inner 
         loop structure, creating severe execution bottlenecks on large inputs.
*/
// std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs)
// {
//     if (strs.size() < 2)
//     {
//         return {strs};
//     }

//     std::vector<std::string> sortedChars(strs);
//     std::unordered_map<std::string, int> anagramsDB;

//     for (std::string& word : sortedChars)
//     {
//         std::sort(word.begin(), word.end());
//         anagramsDB[word]++;
//     }

//     std::vector<std::vector<std::string>> groups;
//     groups.reserve(anagramsDB.size());
//     std::unordered_set<std::string> stringsAdded;
//     stringsAdded.reserve(strs.size());

//     for (size_t i = 0; i < strs.size(); i++)
//     {
//         if (stringsAdded.find(strs[i]) == stringsAdded.end())
//         {
//             std::vector<int> indices = {static_cast<int>(i)};
//             stringsAdded.insert(strs[i]);
//             bool isAnagram = false;

//             for (size_t j = 0; j < strs.size(); j++)
//             {
//                 if (strs[i] != strs[j] && sortedChars[i] == sortedChars[j])
//                 {
//                     stringsAdded.insert(strs[j]);
//                     indices.push_back(static_cast<int>(j));
//                     isAnagram = true;
//                 }
//             }

//             if (!isAnagram)
//             {
//                 groups.push_back({strs[i]});
//             }
//             else
//             {
//                 groups.push_back({});
//                 for (size_t k = 0; k < indices.size(); k++)
//                 {
//                     groups.back().push_back(strs[indices[k]]);
//                 }
//             }
//         }
//     }

//     return groups;
// }

int main()
{
    // Test Case #1
    std::vector<std::string> strs1 = {"eat","tea","tan","ate","nat","bat"};
    std::vector<std::vector<std::string>> results1 = groupAnagrams(strs1);
    std::cout << "Expected Test #1 Output = [ {bat} {nat,tan} {ate,eat,tea} ]" << std::endl;
    std::cout << "  Actual Test #1 Output = [ ";
    for (const std::vector<std::string> group : results1)
    {
        std::cout << "{";
        for (size_t i = 0; i < group.size(); i++)
        {
            if (i < group.size() - 1)
            {
                std::cout << group[i] << ",";
            }
            else
            {
                std::cout << group[i];
            }
        }
        std::cout << "} ";
    }
    std::cout << "]" << std::endl << std::endl;
    
    return 0;
}