#ifndef FACTORY_BAYAN_H
#define FACTORY_BAYAN_H

#include <memory>

#include "bayan.h"
#include "hash_crc32.h"
#include "hash_md5.h"

namespace bayan
{
    class BayanFatory
    {
    public:
        std::shared_ptr<Bayan> create()
        {
            if (settings.hash == "crc32")
                return std::shared_ptr<Bayan>(new BayanImpl<hash::Crc32>(settings));
            if (settings.hash == "md5")
                return std::shared_ptr<Bayan>(new BayanImpl<hash::Md5>(settings));

            return std::shared_ptr<Bayan>(new BayanImpl<hash::Crc32>(settings));
        }

        void setIncludedDirectories(const std::vector<std::string> &dirs)
        {
            settings.included = dirs;
        }

        void setExcludedDirectories(const std::vector<std::string> &dirs)
        {
            settings.excluded = dirs;
        }

        void setFileMasks(const std::vector<std::string> &masks)
        {
            settings.masks = masks;
        }

        void setScanningLavel(int lavel)
        {
            settings.lavel = lavel;
        }

        void setMinSize(int min_size)
        {
            settings.minSize = min_size;
        }

        void setBlockSize(int size)
        {
            settings.blockSize = size;
        }

        void setHashingAlgorithm(const std::string &algorithm)
        {
            settings.hash = algorithm;
        }

    private:
        Settings settings;
    };
}

#endif // FACTORY_BAYAN
