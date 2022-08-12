#ifndef UTILITY_H
#define UTILITY_H

#include <regex>

namespace utility
{
    std::regex generateRegexMask(std::string mask);
}

#endif // UTILITY_H