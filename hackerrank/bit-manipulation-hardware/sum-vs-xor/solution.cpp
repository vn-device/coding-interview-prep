#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'sumXor' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts LONG_INTEGER n as parameter.
 */

long sumXor(long n)
{
    // Special boundary condition
    if (n == 0) return 1;

    int unsetBits = 0;

    // Process bits of n from right to left
    while (n > 0)
    {
        // (n & 1) checks the lowest bit. 
        // If it's 0, we increment our free choices.
        if ((n & 1) == 0) unsetBits++;
        
        // Bit-shift n right by 1 to inspect the next bit
        n >>= 1;
    }

    // 1L << unsetBits computes 2^(unsetBits) using a bitwise shift
    return 1L << unsetBits;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    long n = stol(ltrim(rtrim(n_temp)));

    long result = sumXor(n);

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
