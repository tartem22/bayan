#include "utility.h"

std::regex utility::generateRegexMask(std::string mask)
{
    for (auto i = mask.find('*'); i != std::string::npos; i = mask.find('*', i + 2))
    {
        mask.insert(i, 1, '.');
    }
    return std::regex(mask);
}