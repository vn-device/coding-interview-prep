#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

//---------- Implementation #5 ----------
/*
    Optimal Strategy: O(N) Time | O(N) Auxiliary Space

    1. Arbitrary Precision & Numeric Bounds:
       Input numbers can exceed 1000 digits, rendering primitive integer conversions 
       (e.g., std::stoi, std::stoull) invalid due to arithmetic overflow (std::out_of_range). 
       Numerical equality is instead preserved directly in string representation.

    2. Leading Zero Normalization Invariant:
       Equivalence between numeric representations (e.g., "01", "001", "1") is maintained 
       by trimming leading '0' characters via std::string::find_first_not_of('0'). 
       All-zero substrings evaluate to npos and are normalized to "0".

    3. Deduplication & Allocations:
       Uses std::unordered_set<std::string> to achieve amortized O(1) deduplication.
       Processes word via const-reference traversal and in-place token buffering to 
       minimize auxiliary heap allocations.
*/
int numDifferentIntegers(const std::string& word)
{
    std::unordered_set<std::string> uniqueNums;
    std::string token;

    for (char c : word)
    {
        // Using '0' or its ASCII decimal #48 doesn't matter
        if (c >= '0' && c <= '9')
        {
            token.push_back(c);
        }
        else if (!token.empty())
        {
            size_t nonzeroPos = token.find_first_not_of('0');
            uniqueNums.insert((nonzeroPos == std::string::npos) ? "0" : token.substr(nonzeroPos));
    
            token.clear();
        }
    }

    if (!token.empty())
    {
        size_t nonzeroPos = token.find_first_not_of('0');
        uniqueNums.insert((nonzeroPos == std::string::npos) ? "0" : token.substr(nonzeroPos));
    }

    return static_cast<int>(uniqueNums.size());
}

//---------- Implementation #4 ----------
/*
    Same as implementation #3, but changed from std::stoi to std::stoull.
    Able to pass 23/86 cases, but failed at 'std::out_of_range' for std::stoull.
*/
// int numDifferentIntegers(const std::string& word)
// {
//     if (word.empty())
//     {
//         return 0;
//     }

//     std::string token = "";
//     std::unordered_map<size_t, int> numsTable;

//     for (size_t i = 0; i < word.size(); i++)
//     {
//         if (word[i] >= 48 && word[i] <= 57)
//         {
//             token.push_back(word[i]);
//             if (i == word.size() - 1)
//             {
//                 numsTable[std::stoull(token, nullptr)]++;
//             }
//         }
//         else
//         {
//             if (!token.empty())
//             {
//                 numsTable[std::stoull(token, nullptr)]++;
//                 token.clear();
//             }
//         }
//     }

//     return static_cast<int>(numsTable.size());
// }

//---------- Implementation #3 ----------
/*
    Changed for loop implementation to using std::string indexing
    to check for current index when reaching for final character.
    Able to pass 3/3 starter cases, but failed LeetCode submissions
    at case = "167278959591294" for 'std::out_of_range'.
*/
// int numDifferentIntegers(const std::string& word)
// {
//     if (word.empty())
//     {
//         return 0;
//     }

//     std::string token = "";
//     std::unordered_map<int, int> numsTable;

//     for (size_t i = 0; i < word.size(); i++)
//     {
//         if (word[i] >= 48 && word[i] <= 57)
//         {
//             token.push_back(word[i]);
//             if (i == word.size() - 1)
//             {
//                 numsTable[std::stoi(token, nullptr)]++;
//             }
//         }
//         else
//         {
//             if (!token.empty())
//             {
//                 numsTable[std::stoi(token, nullptr)]++;
//                 token.clear();
//             }
//         }
//     }

//     return static_cast<int>(numsTable.size());
// }

//---------- Implementation #2 ----------
/*
    Keeping hash table concept from implementation #1, but slightly
    tuned how to convert from std::string to int using std::stoi rather
    then atoi. Added nested condition to convert non-empty token
    then clear after hash table updated, but only able to pass 2/3 starting cases.
*/
// int numDifferentIntegers(const std::string& word)
// {
//     if (word.empty())
//     {
//         return 0;
//     }

//     std::string token = "";
//     std::unordered_map<int, int> numsTable;
//     for (const char& c : word)
//     {
//         if (c >= 48 && c <= 57)
//         {
//             token += c;
//         }
//         else
//         {
//             if (!token.empty())
//             {
//                 numsTable[std::stoi(token, nullptr)]++;
//                 token.clear();
//             }
//         }
//     }

//     return static_cast<int>(numsTable.size());
// }

//---------- Implementation #1 ----------
/*
    Using std::unordered_map as hash table to track how instances of
    a specific int has occurred. Parsing each char in word to see if
    char is a number via ASCII value. Implementation passed 1/3 starting cases.
*/
// int numDifferentIntegers(const std::string& word)
// {
//     if (word.empty())
//     {
//         return 0;
//     }

//     std::string token = "";
//     std::unordered_map<int, int> numsTable;
//     for (const char& c : word)
//     {
//         if (c >= 48 && c <= 57)
//         {
//             token += c;
//         }
//         else
//         {
//             numsTable[atoi(token.c_str())]++;
//         }
//     }

//     return static_cast<int>(numsTable.size());
// }

int main()
{
    // Test Case #1
    std::string word1 = "a123bc34d8ef34";
    std::cout << "Expected Test Case #1 Output = 3" << std::endl;
    std::cout << "  Actual Test Case #1 Output = " << numDifferentIntegers(word1) << std::endl << std::endl;

    // Test Case #2
    std::string word2 = "leet1234code234";
    std::cout << "Expected Test Case #2 Output = 2" << std::endl;
    std::cout << "  Actual Test Case #2 Output = " << numDifferentIntegers(word2) << std::endl << std::endl;

    // Test Case #2
    std::string word3 = "a1b01c001";
    std::cout << "Expected Test Case #3 Output = 1" << std::endl;
    std::cout << "  Actual Test Case #3 Output = " << numDifferentIntegers(word3) << std::endl << std::endl;

    return 0;
}