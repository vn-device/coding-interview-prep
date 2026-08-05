#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'largestRectangle' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts INTEGER_ARRAY h as parameter.
 */

long largestRectangle(vector<int> h)
{   
    // Stack stores indices of buildings to maintain a monotonic strictly increasing height order
    stack<int> indices;
    long maxArea = 0;
    
    for (size_t i = 0; i < h.size(); i++)
    {
        // When encountering a bar shorter than the bar at stack top, the taller bar's expansion stops.
        // Process all preceding taller bars to compute their maximum bounded areas.
        while (!indices.empty() && h[i] < h[indices.top()])
        {
            int height = h[indices.top()];
            indices.pop();
            
            // Right boundary is current index 'i' (first shorter element on the right)
            int rightBound = i;
            
            // Left boundary is index of new top element (first shorter element on the left)
            int leftBound = (indices.empty()) ? -1 : indices.top();

            long currentArea = (long)height * (rightBound - leftBound - 1);
            maxArea = max(maxArea, currentArea);
        }
        
        indices.push(i);
    }

    // Cleanup phase: Process remaining elements in stack whose rightward expansion was never blocked
    while (!indices.empty())
    {
        int height = h[indices.top()];
        indices.pop();

        // Right boundary extends to the end of the histogram array
        int rightBound = h.size();
        int leftBound = (indices.empty()) ? -1 : indices.top();

        long currentArea = (long)height * (rightBound - leftBound - 1);
        maxArea = max(maxArea, currentArea);
    }

    return maxArea;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string h_temp_temp;
    getline(cin, h_temp_temp);

    vector<string> h_temp = split(rtrim(h_temp_temp));

    vector<int> h(n);

    for (int i = 0; i < n; i++) {
        int h_item = stoi(h_temp[i]);

        h[i] = h_item;
    }

    long result = largestRectangle(h);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
