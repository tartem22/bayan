#ifndef BAYAN_H
#define BAYAN_H

#include <string>
#include <vector>
#include <regex>
#include <filesystem>

#include "file.h"
#include "hash.h"

namespace bayan
{
    using EqualPairFileNames = std::tuple<std::string, std::string>;
    using EqualFileNames = std::vector<std::vector<std::string>>;

    struct Settings
    {
        std::vector<std::string> included;
        std::vector<std::string> excluded;
        int lavel = 0;
        int minSize = 1;
        std::vector<std::string> masks;
        std::vector<std::regex> regexMasks;
        int blockSize = 0;
        std::string hash;
    };

    class Bayan
    {
    public:
        Bayan(const Settings &settings);
        EqualFileNames find();

    protected:
        virtual EqualFileNames findImpl() = 0;
        void createFileList();
        virtual void clearFileList() = 0;
        virtual void addFilesFromDirectory(const std::string &path, int lavel) = 0;
        bool checkDirIsExcluded(const std::string &path);
        bool checkFileIsExcludedByMasks(const std::string &filename);

        Settings settings;
    };

    template <typename H>
    class BayanImpl : public Bayan
    {
    public:
        BayanImpl(const Settings &settings) : Bayan(settings) {}

    private:
        using HashedFile = File<H>;
        using HashedFilePtr = std::shared_ptr<HashedFile>;

        EqualFileNames findImpl() override
        {
            EqualFileNames equalFiles;
            equalFiles.reserve(100);

            createFileList();

            if (!fileList.empty())
            {
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
            }

            equalFiles.shrink_to_fit();
            return equalFiles;
        }

        void clearFileList() override
        {
            fileList.clear();
            fileList.reserve(1000);
        }

        void addFilesFromDirectory(const std::string &path, int lavel) override
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
                            fileList.emplace_back(std::make_shared<HashedFile>(dirEntry.path(), settings.blockSize));
                    }
                }
            }
        }

        bool compareFiles(HashedFilePtr &first, HashedFilePtr &second)
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

        std::vector<HashedFilePtr> fileList;
    };
}

#endif // BAYAN_H