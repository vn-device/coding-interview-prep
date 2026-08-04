#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <sstream>

using namespace std;

int main()
{
    // Fast I/O configuration
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int totalLines;
    int totalQueries;

    if (!(cin >> totalLines >> totalQueries))
    {
        return 0;
    }

    // Flush the trailing newline character left in the stream buffer by cin
    cin.ignore();

    unordered_map<string, string> attributesTable;
    vector<string> tagsStack;

    while (totalLines--)
    {
        string line;
        getline(cin, line);

        // In-place delimiter stripping via Erase-Remove idiom
        line.erase(remove(line.begin(), line.end(), '<'), line.end());
        line.erase(remove(line.begin(), line.end(), '"'), line.end());
        line.erase(remove(line.begin(), line.end(), '>'), line.end());

        stringstream ss(line);
        string word;
        ss >> word;

        if (word[0] == '/')
        {
            // Closing tag reduces active nesting level
            tagsStack.pop_back();
        }
        else
        {
            // Opening tag increases active nesting level
            tagsStack.push_back(word);

            // Serialize current stack depth into a path prefix
            string tagsPath = "";
            for (size_t i = 0; i < tagsStack.size(); ++i)
            {
                tagsPath += tagsStack[i];
                if (i != tagsStack.size() - 1)
                {
                    tagsPath += ".";
                }
            }

            string attributeType;
            string equalSign;
            string attributeVal;

            // Extract remaining key-value pairs from stream
            while (ss >> attributeType >> equalSign >> attributeVal)
            {
                // Construct temporary key without mutating base tagsPath
                string key = tagsPath + "~" + attributeType;
                attributesTable[key] = attributeVal;
            }
        }
    }

    // Process queries against pre-indexed hash table
    while (totalQueries--)
    {
        string query;
        getline(cin, query);

        if (attributesTable.find(query) == attributesTable.end())
        {
            cout << "Not Found!\n";
        }
        else
        {
            cout << attributesTable[query] << "\n";
        }
    }

    return 0;
}