#include "bayan.h"
#include "../utility.h"

#include <filesystem>
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
    EqualFileNames equalFiles;
    equalFiles.reserve(100);

    createFileList();

    for (int i = 0; i < fileList.size() - 1; i++)
    {
        std::vector<std::string> equalFilesWithCurrent;
        equalFilesWithCurrent.reserve(1000);
        equalFilesWithCurrent.emplace_back(fileList.at(i)->getFilePath());
        for (int j = i + 1; j < fileList.size(); j++)
        {
            if (compareFiles(fileList.at(i), fileList.at(j)))
            {
                equalFilesWithCurrent.emplace_back(fileList.at(j)->getFilePath());
                fileList.erase(fileList.begin() + j);
                j--;
            }
        }
        if (equalFilesWithCurrent.size() > 1)
        {
            equalFiles.emplace_back(equalFilesWithCurrent);
        }
    }

    equalFiles.shrink_to_fit();
    return equalFiles;
}

void Bayan::createFileList()
{
    fileList.clear();
    fileList.reserve(1000);

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

void Bayan::addFilesFromDirectory(const std::string &path, int lavel)
{
    for (auto const &dirEntry : std::filesystem::directory_iterator{path})
    {
        if (dirEntry.is_directory())
        {
            if (!checkDirIsExcluded(dirEntry.path()) && (lavel + 1 < settings.lavel))
            {
                addFilesFromDirectory(dirEntry.path(), lavel + 1);
            }
        }
        else if (dirEntry.is_regular_file())
        {
            if (dirEntry.file_size() >= settings.minSize)
            {
                if (!checkFileIsExcludedByMasks(dirEntry.path().filename()))
                    fileList.emplace_back(std::make_shared<File>(dirEntry.path(), settings.blockSize));
            }
        }
    }
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

bool Bayan::checkFileIsExcludedByMasks(const std::string &filename)
{
    for (auto const &mask : settings.regexMasks)
    {
        if (std::regex_match(filename, mask))
            return true;
    }
    return false;
}

bool Bayan::compareFiles(std::shared_ptr<File> &first,
                         std::shared_ptr<File> &second)
{
    bool outOfData = false;
    int blocksCnt = 0;
    while (!outOfData)
    {
        auto [firstHasData, firstChecksum] = first->getHashOfBlock(blocksCnt);
        auto [secondHasData, secondChecksum] = second->getHashOfBlock(blocksCnt);
        blocksCnt++;
        outOfData = (!firstHasData) || (!secondHasData);
        if (!outOfData)
        {
            if (firstChecksum != secondChecksum)
            {
                return false;
            }
        }
        else if (firstHasData != secondHasData)
            return false;
    }
    return true;
}