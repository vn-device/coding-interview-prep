#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

//---------- Implementation #2 (Direct Substring Indexing & Direct Bucket Accumulation) ----------
/*
    Optimal Strategy: Amortized O(N) Time | O(N) Auxiliary Space

    Improvements over Implementation #1:

    1. Stream Elimination:
       Replaced std::stringstream with std::string::find(' ') and std::stoi. This 
       eliminates dynamic formatted I/O stream construction overhead on every iteration.

    2. Single-Pass Map Lookups:
       Replaced double-lookup checks (find() + operator[]) with direct map accumulation:
       domainsDB[...] += count. std::unordered_map::operator[] automatically zero-initializes 
       missing domain keys, halving hash computations and bucket traversals per domain.

    3. Direct Substring Traversal:
       Uses std::string::find('.', dotPos + 1) to locate domain boundaries sequentially 
       without mutating or erasing base string memory.
*/
std::vector<std::string> subDomainVisits(const std::vector<std::string>& cpdomains)
{
    std::vector<std::string> allDomains;
    std::unordered_map<std::string, int> domainsDB;

    for (const std::string& cpdomain : cpdomains)
    {
        size_t whitespacePos = cpdomain.find(' ');
        int count = std::stoi(cpdomain.substr(0, whitespacePos));

        domainsDB[cpdomain.substr(whitespacePos + 1)] += count;

        size_t dotPos = cpdomain.find('.');
        while (dotPos != std::string::npos)
        {
            domainsDB[cpdomain.substr(dotPos + 1)] += count;
            dotPos = cpdomain.find('.', dotPos + 1);
        }
    }

    for (auto iter = domainsDB.begin(); iter != domainsDB.end(); iter++)
    {
        allDomains.push_back(std::to_string(iter->second) + " " + iter->first);
    }

    return allDomains;
}

//---------- Implementation #1 (Stream Parsing & Naive Map Checks) ----------
/*
    Naive Strategy: Functional, but contains multiple performance bottlenecks.

    1. Stream Instantiation Overhead:
       Constructing a std::stringstream on every loop iteration allocates dynamic 
       memory and incurs formatted I/O parsing overhead. Direct std::string::find(' ') 
       and std::stoi calls avoid stream allocations completely.

    2. Dynamic Memory Slicing via Mutation:
       Calling domain = domain.substr(dotPos + 1) continuously mutates and re-allocates 
       heap memory for intermediate string objects on every dot split. 

    3. Double-Lookup Hash Inefficiency:
       Using find() followed by operator[] performs two separate hash computations 
       and bucket traversals per domain key. C++ std::unordered_map::operator[] 
       automatically zero-initializes non-existent keys, allowing direct accumulation:
       map[key] += count.
*/
// std::vector<std::string> subDomainVisits(const std::vector<std::string>& cpdomains)
// {
//     if (cpdomains.empty())
//     {
//         return {};
//     }

//     std::vector<std::string> allDomains;
//     std::unordered_map<std::string, int> domainsDB;

//     for (const std::string& cpdomain : cpdomains)
//     {
//         int count;
//         std::string domain;
//         std::stringstream ss1(cpdomain);

//         ss1 >> count >> domain;
        
//         if (domainsDB.find(domain) == domainsDB.end())
//         {
//             domainsDB[domain] = count;
//         }
//         else
//         {
//             domainsDB[domain] += count;
//         }

//         size_t dotPos = domain.find_first_of('.');
//         while (dotPos != std::string::npos)
//         {
//             domain = domain.substr(dotPos + 1);

//             if (domainsDB.find(domain) == domainsDB.end())
//             {
//                 domainsDB[domain] = count;
//             }
//             else
//             {
//                 domainsDB[domain] += count;
//             }

//             dotPos = domain.find_first_of('.');
//         }
//     }

//     for (auto iter = domainsDB.begin(); iter != domainsDB.end(); iter++)
//     {
//         int count = iter->second;
//         std::string domain = iter->first;
//         allDomains.push_back(std::to_string(count) + " " + domain);
//     }

//     return allDomains;
// }

int main()
{
    // Test Case #1
    std::vector<std::string> cpdomains1 = {"9001 discuss.leetcode.com"};
    std::vector<std::string> result1 = subDomainVisits(cpdomains1);
    // std::cout << "Expected Case #1 Output = [9001 leetcode.com,9001 discuss.leetcode.com,9001 com]" << std::endl;
    std::cout << "  Actual Case #1 Output = [";
    for (size_t i = 0; i < result1.size(); i++)
    {
        if (i < result1.size() - 1)
        {
            std::cout << result1[i] << ";";
        }
        else
        {
            std::cout << result1[i] << "]" << std::endl << std::endl;
        }
    }

    // Test Case #2
    std::vector<std::string> cpdomains2 = {"900 google.mail.com", "50 yahoo.com", "1 intel.mail.com", "5 wiki.org"};
    std::vector<std::string> result2 = subDomainVisits(cpdomains2);
    // std::cout << "Expected Case #2 Output = [901 mail.com,50 yahoo.com,900 google.mail.com,5 wiki.org,5 org,1 intel.mail.com,951 com]" << std::endl;
    std::cout << "  Actual Case #2 Output = [";
    for (size_t i = 0; i < result2.size(); i++)
    {
        if (i < result2.size() - 1)
        {
            std::cout << result2[i] << ";";
        }
        else
        {
            std::cout << result2[i] << "]" << std::endl << std::endl;
        }
    }

    return 0;
}