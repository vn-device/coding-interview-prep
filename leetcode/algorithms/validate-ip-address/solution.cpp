#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

std::string validIPAddress(std::string& queryIP)
{
    size_t dotPos = queryIP.find('.');
    size_t colonPos = queryIP.find(':');
    if (queryIP.empty() || (dotPos == std::string::npos && colonPos == std::string::npos))
    {
        return "Neither";
    }

    // Start by testing for IPv4
    if (dotPos != std::string::npos && dotPos != 0 && colonPos == std::string::npos)
    {        
        int totalOctets = 0, totalDots = 0;
        std::string octet;

        for (const char& c : queryIP)
        {
            if (c == '.')
            {
                totalDots++;
                
                if ((octet.length() >= 1 && octet.length() <= 3) &&
                    !(octet.length() >= 2 && octet[0] == '0') &&
                    (std::stoi(octet) >= 0 && std::stoi(octet) <= 255))
                {
                    totalOctets++;
                    octet.clear();
                }
            }
            else if (c >= '0' && c <= '9')
            {
                octet.push_back(c);
            }
            else
            {
                return "Neither";
            }
        }

        if (!octet.empty() && (octet.length() >= 1 && octet.length() <= 3) &&
            !(octet.length() >= 2 && octet[0] == '0') &&
            (std::stoi(octet) >= 0 && std::stoi(octet) <= 255))
        {
            totalOctets++;
        }

        if (totalOctets == 4 && totalDots == 3)
        {
            return "IPv4";
        }
    }
    // Second testing for IPv6
    else if (dotPos == std::string::npos && colonPos != std::string::npos && colonPos != 0)
    {
        int totalHextets = 0, totalColons = 0;
        std::string hextet;

        for (const char& c : queryIP)
        {
            if (c == ':')
            {
                totalColons++;
                
                if (hextet.length() >= 1 && hextet.length() <= 4)
                {
                    totalHextets++;
                    hextet.clear();
                }
            }
            else if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
            {
                hextet.push_back(c);
            }
            else
            {
                return "Neither";
            }
        }

        if (hextet.length() >= 1 && hextet.length() <= 4)
        {
            totalHextets++;
        }

        if (totalHextets == 8 && totalColons == 7)
        {
            return "IPv6";
        }
    }

    return "Neither";
}

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