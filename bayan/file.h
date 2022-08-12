#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <vector>

namespace bayan
{
    class File
    {
    public:
        File(const std::string &path, int blockSize);
        ~File();

        bool readNextBlock();
        std::tuple<bool, int> getHashOfBlock(int blockNumber);
        std::string getFilePath();

    private:
        std::string path;
        int blockSize = 0;
        std::ifstream file;
        std::vector<uint32_t> hash;
    };
}

#endif // FILE_H