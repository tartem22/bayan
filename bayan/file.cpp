#include "file.h"

#include <tuple>
#include <cstring>

#include <boost/crc.hpp>

using namespace bayan;

uint32_t getCrc32(const char *buffer, size_t length)
{
    boost::crc_32_type result;
    result.process_bytes(buffer, length);
    return result.checksum();
}

File::File(const std::string &path, int blockSize) : path(path),
                                                     blockSize(blockSize)
{
    hash.reserve(100);
}

File::~File()
{
    if (file.is_open())
        file.close();
}

bool File::readNextBlock()
{
    if (!file.is_open())
        file.open(path, std::ios::binary);
    char *buffer = new char[blockSize];
    memset(buffer, '\0', blockSize);
    file.read(buffer, blockSize);
    if (file.eof())
        return false;
    else
        hash.push_back(getCrc32(buffer, blockSize));
    return true;
}

std::tuple<bool, int> File::getHashOfBlock(int blockNumber)
{
    if (blockNumber >= hash.size())
    {
        if (readNextBlock())
        {
            return std::tuple<bool, int>(true, hash.at(blockNumber));
        }
        else
            return std::tuple<bool, int>(false, 0);
    }
    else
        return std::tuple<bool, int>(true, hash.at(blockNumber));
}

std::string File::getFilePath()
{
    return path;
}