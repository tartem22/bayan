#ifndef FILE_H
#define FILE_H

#include <string>
#include <cstring>
#include <fstream>
#include <vector>

namespace bayan
{
    template <typename H>
    class File
    {
    public:
        File(const std::string &path, int blockSize) : path(path),
                                                       blockSize(blockSize)
        {
            hash.reserve(100);
        }

        ~File()
        {
            if (file.is_open())
                file.close();
        }

        bool readNextBlock()
        {
            if (!file.is_open())
                file.open(path, std::ios::binary);
            char *buffer = new char[blockSize];
            memset(buffer, '\0', blockSize);
            file.read(buffer, blockSize);
            if (file.eof())
                return false;
            else
                hash.push_back(H(buffer, blockSize));
            return true;
        }

        std::tuple<bool, H> getHashOfBlock(int blockNumber)
        {
            if (blockNumber >= hash.size())
            {
                if (readNextBlock())
                {
                    return std::tuple<bool, H>(true, hash.at(blockNumber));
                }
                else
                    return std::tuple<bool, H>(false, H());
            }
            else
                return std::tuple<bool, H>(true, hash.at(blockNumber));
        }

        std::string getFilePath()
        {
            return path;
        }

    private:
        std::string path;
        int blockSize = 0;
        std::ifstream file;
        std::vector<H> hash;
    };
}

#endif // FILE_H