#include <string>
#include <sstream>
#include <numeric>

std::string fractionAddition(const std::string &expression)
{
    std::stringstream ss(expression);

    int totalNum = 0;
    int totalDen = 1;

    int num = 0;
    char slash = 0;
    int den = 0;

    // Formatted stream extraction handles signs and delimiters automatically
    while (ss >> num >> slash >> den)
    {
        // A/B + C/D = (A*D + C*B) / (B*D)
        totalNum = totalNum * den + num * totalDen;
        totalDen = totalDen * den;

        // Simplify running fraction to prevent 32-bit integer overflow
        const int common = std::gcd(std::abs(totalNum), totalDen);
        totalNum /= common;
        totalDen /= common;
    }

    return std::to_string(totalNum) + "/" + std::to_string(totalDen);
}