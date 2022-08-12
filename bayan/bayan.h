#ifndef BAYAN_H
#define BAYAN_H

#include <string>
#include <vector>
#include <regex>

#include "file.h"

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

    private:
        void createFileList();
        void addFilesFromDirectory(const std::string &path, int lavel);
        bool checkDirIsExcluded(const std::string &path);
        bool checkFileIsExcludedByMasks(const std::string &filename);
        bool compareFiles(std::shared_ptr<File> &first,
                          std::shared_ptr<File> &second);

        Settings settings;
        std::vector<std::shared_ptr<File>> fileList;
    };
}

#endif // BAYAN_H