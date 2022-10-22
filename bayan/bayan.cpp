#include "bayan.h"
#include "../utility.h"

#include <regex>

using namespace bayan;

Bayan::Bayan(const Settings &settings) : settings(settings)
{
    for (auto &mask : (this->settings).masks)
    {
        (this->settings).regexMasks.emplace_back(utility::generateRegexMask(mask));
    }
}

EqualFileNames Bayan::find()
{
    return findImpl();
}

bool Bayan::checkDirIsExcluded(const std::string &path)
{
    for (auto const &ex : settings.excluded)
    {
        if (path == ex)
            return true;
    }
    return false;
}

void Bayan::createFileList()
{
    clearFileList();
    for (auto &in : settings.included)
    {
        if (std::filesystem::exists(in))
        {
            if (!std::filesystem::is_empty(in))
            {
                addFilesFromDirectory(in, 0);
            }
        }
    }
}

bool Bayan::checkFileIsExcludedByMasks(const std::string &filename)
{
    for (auto const &mask : settings.regexMasks)
    {
        if (std::regex_match(filename, mask))
            return true;
    }
    return false;
}