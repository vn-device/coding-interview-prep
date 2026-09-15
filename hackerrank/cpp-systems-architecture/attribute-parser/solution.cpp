//==============================================================================
// HackerRank: Attribute Parser (HRML Document Model)
// Strategy: Hierarchical Prefix Stack & In-Place Lexical Tokenizer
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - Ingestion & Parsing: O(N * L) where N is totalLines and L is max line length.
        Tokenizing tag names and attribute key-value pairs operates in a single linear pass.
      - Query Resolution: O(Q * K) average time, where Q is totalQueries and K is query string length.
        Each lookup hits 'attributesDB' via O(K) hash computation and equality comparison.
      - Total Time: O(N * L + Q * K).
    - Auxiliary Space: O(U * M)
      - 'attributesDB' stores U unique fully-qualified attribute paths of average length M.
      - 'tagStack' depth is bounded by maximum nesting depth D <= N.

    Algorithmic & Structural Invariants:
    1. Scope Invariant:
       - An opening tag pushes to 'tagStack' and extends the current hierarchical prefix.
       - A closing tag ('</...>') pops the top tag and restores the parent scope.
    2. Attribute Address Uniqueness:
       - Every valid attribute is uniquely indexed by the composite key "<tag1>.<tag2>...<tagN>~<attr>".

    Architectural Observations & Systems Considerations:
    - Zero-Allocation Tokenization:
      - Replacing 'std::stringstream' and whole-line character erasures with direct index
        or 'std::string_view' scans preserves whitespace inside quoted attribute values
        while avoiding stream buffer allocations.
    - Path Construction Optimization:
      - Maintaining an incremental path string amortizes hierarchical string concatenation.
*/
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main()
{
    // Get user input for # of HRML lines and queries
    int totalLines = 0;
    int totalQueries = 0;
    std::cin >> totalLines >> totalQueries;
    std::cin.ignore();

    // Get HRML lines and parse them into hashmap
    std::unordered_map<std::string, std::string> attributesDB;
    std::string hrmlLine;

    std::vector<std::string> stack;
    stack.reserve(totalLines);

    while (totalLines-- && std::getline(std::cin, hrmlLine))
    {
        // Strip away unncessary characters
        for (char &c : hrmlLine)
        {
            if (c == '<' || c == '>' || c == '"')
            {
                c = ' ';
            }
        }

        std::stringstream ss(hrmlLine);
        std::string tag;

        while (!(ss >> tag))
        {
            // Try parsing tag if leading whitespace
            continue;
        }

        if (tag[0] == '/')
        {
            stack.pop_back();
        }
        else
        {
            stack.push_back(tag);
            std::string path = stack[0];

            for (size_t i = 1; i < stack.size(); i++)
            {
                path += ("." + stack[i]);
            }

            std::string attribute;
            std::string equal;
            std::string value;

            while (ss >> attribute >> equal >> value)
            {
                std::string key = path + "~" + attribute;
                attributesDB[key] = value;
            }
        }
    }

    // Get user queries and return appropriate outputs
    std::string query;

    while (totalQueries-- && std::getline(std::cin, query))
    {
        auto iter = attributesDB.find(query);

        if (iter != attributesDB.end())
        {
            std::cout << iter->second << "\n";
        }
        else
        {
            std::cout << "Not Found!\n";
        }
    }

    return 0;
}
