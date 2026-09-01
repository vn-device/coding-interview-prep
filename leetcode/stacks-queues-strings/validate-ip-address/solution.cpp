#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

//---------- Implementation #2 (Stream Tokenization & Inline Rule Validation) ----------
/*
    Optimal Strategy: O(N) Time | O(1) Auxiliary Space

    Improvements over Implementation #1:

    1. Stream-Based Tokenization (std::getline):
       Leverages std::stringstream and std::getline with delimiter controls ('.' / ':') 
       to cleanly extract octets and hextets, eliminating manual character-by-character 
       buffer pushing and dual-pass validation logic.

    2. Elimination of std::stoi & Exception Hazards:
       Replaces std::stoi conversion calls with arithmetic character accumulation: 
       value = value * 10 + (c - '0'). This completely bypasses std::out_of_range 
       exceptions on malformed numerical strings while retaining strict range checks [0, 255].

    3. Early Candidate Pruning:
       Counts period and colon delimiters up front to isolate protocol paths (dotCount == 3 
       vs colonCount == 7). Automatically rejects invalid edge cases such as trailing 
       delimiters (e.g., "172.16.254.1.") prior to token evaluation.
*/
std::string validIPAddress(const std::string& queryIP)
{
    if (queryIP.empty())
    {
        return "Neither";
    }

    size_t dotCount = 0;
    size_t colonCount = 0;

    for (char c : queryIP)
    {
        if (c == '.')
        {
            dotCount++;
        }
        else if (c == ':')
        {
            colonCount++;
        }
    }

    // Process IPv4 Candidate (Exactly 3 dots)
    if (dotCount == 3 && colonCount == 0)
    {
        if (queryIP.back() == '.')
        {
            return "Neither";
        }

        std::stringstream ss(queryIP);
        std::string octet;
        int segmentCount = 0;

        while (std::getline(ss, octet, '.'))
        {
            segmentCount++;

            // Inline IPv4 Octet Validation
            if (octet.empty() || octet.length() > 3)
            {
                return "Neither";
            }

            if (octet.length() > 1 && octet[0] == '0')
            {
                return "Neither";
            }

            int value = 0;
            for (char c : octet)
            {
                if (c < '0' || c > '9')
                {
                    return "Neither";
                }
                value = value * 10 + (c - '0');
            }

            if (value < 0 || value > 255)
            {
                return "Neither";
            }
        }

        return (segmentCount == 4) ? "IPv4" : "Neither";
    }

    // Process IPv6 Candidate (Exactly 7 colons)
    if (colonCount == 7 && dotCount == 0)
    {
        if (queryIP.back() == ':')
        {
            return "Neither";
        }

        std::stringstream ss(queryIP);
        std::string hextet;
        int segmentCount = 0;

        while (std::getline(ss, hextet, ':'))
        {
            segmentCount++;

            // Inline IPv6 Hextet Validation
            if (hextet.empty() || hextet.length() > 4)
            {
                return "Neither";
            }

            for (char c : hextet)
            {
                bool isDigit = (c >= '0' && c <= '9');
                bool isLowerHex = (c >= 'a' && c <= 'f');
                bool isUpperHex = (c >= 'A' && c <= 'F');

                if (!isDigit && !isLowerHex && !isUpperHex)
                {
                    return "Neither";
                }
            }
        }

        return (segmentCount == 8) ? "IPv6" : "Neither";
    }

    return "Neither";
}

//---------- Implementation #1 (Single-Pass Character Stream & Dual-Branch Check) ----------
/*
    Naive Strategy: Functional (Passed 79/79 cases), but contains refactoring targets.

    1. Redundant Condition Statements & DRY Violations:
       Octet/hextet validation checks (length bounds, leading zero invariants, numeric ranges) 
       are duplicated—executed once inside the character-by-character loop upon delimiter 
       encounter, and repeated again post-loop for trailing tokens.

    2. Potential Conversions & Exception Overhead:
       Uses std::stoi(octet) directly within conditional checks. While protected by previous 
       length checks (length <= 3), raw character-to-integer accumulators avoid std::string 
       conversion overhead entirely and prevent out-of-range exceptions on unbounded strings.

    3. Protocol Candidate Separation:
       Maintains separate IPv4 and IPv6 parsing blocks within an if/else if structure. 
       Modularizing segment verification into helper functions (isValidOctet, isValidHextet) 
       and leveraging string-splitting utilities (std::getline) decouples control flow from 
       character validation.
*/
// std::string validIPAddress(std::string& queryIP)
// {
//     size_t dotPos = queryIP.find('.');
//     size_t colonPos = queryIP.find(':');
//     if (queryIP.empty() || (dotPos == std::string::npos && colonPos == std::string::npos))
//     {
//         return "Neither";
//     }

//     // Start by testing for IPv4
//     if (dotPos != std::string::npos && dotPos != 0 && colonPos == std::string::npos)
//     {        
//         int totalOctets = 0, totalDots = 0;
//         std::string octet;

//         for (const char& c : queryIP)
//         {
//             if (c == '.')
//             {
//                 totalDots++;
                
//                 if ((octet.length() >= 1 && octet.length() <= 3) &&
//                     !(octet.length() >= 2 && octet[0] == '0') &&
//                     (std::stoi(octet) >= 0 && std::stoi(octet) <= 255))
//                 {
//                     totalOctets++;
//                     octet.clear();
//                 }
//             }
//             else if (c >= '0' && c <= '9')
//             {
//                 octet.push_back(c);
//             }
//             else
//             {
//                 return "Neither";
//             }
//         }

//         if (!octet.empty() && (octet.length() >= 1 && octet.length() <= 3) &&
//             !(octet.length() >= 2 && octet[0] == '0') &&
//             (std::stoi(octet) >= 0 && std::stoi(octet) <= 255))
//         {
//             totalOctets++;
//         }

//         if (totalOctets == 4 && totalDots == 3)
//         {
//             return "IPv4";
//         }
//     }
//     // Second testing for IPv6
//     else if (dotPos == std::string::npos && colonPos != std::string::npos && colonPos != 0)
//     {
//         int totalHextets = 0, totalColons = 0;
//         std::string hextet;

//         for (const char& c : queryIP)
//         {
//             if (c == ':')
//             {
//                 totalColons++;
                
//                 if (hextet.length() >= 1 && hextet.length() <= 4)
//                 {
//                     totalHextets++;
//                     hextet.clear();
//                 }
//             }
//             else if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
//             {
//                 hextet.push_back(c);
//             }
//             else
//             {
//                 return "Neither";
//             }
//         }

//         if (hextet.length() >= 1 && hextet.length() <= 4)
//         {
//             totalHextets++;
//         }

//         if (totalHextets == 8 && totalColons == 7)
//         {
//             return "IPv6";
//         }
//     }

//     return "Neither";
// }

int main()
{
    // Test Case #1
    std::string queryIP1 = "172.16.254.1";
    std::cout << "Expected Test #1 Output = IPv4" << std::endl;
    std::cout << "  Actual Test #1 Output = " << validIPAddress(queryIP1) << std::endl << std::endl;

    // Test Case #2
    std::string queryIP2 = "2001:0db8:85a3:0:0:8A2E:0370:7334";
    std::cout << "Expected Test #2 Output = IPv6" << std::endl;
    std::cout << "  Actual Test #2 Output = " << validIPAddress(queryIP2) << std::endl << std::endl;

    // Test Case #3
    std::string queryIP3 = "256.256.256.256";
    std::cout << "Expected Test #3 Output = Neither" << std::endl;
    std::cout << "  Actual Test #3 Output = " << validIPAddress(queryIP3) << std::endl << std::endl;

    return 0;
}