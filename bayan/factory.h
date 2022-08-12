#ifndef FACTORY_BAYAN_H
#define FACTORY_BAYAN_H

#include <memory>

#include "bayan.h"

namespace bayan
{
    class BayanFatory
    {
    public:
        std::shared_ptr<Bayan> create()
        {
            return std::make_shared<Bayan>(settings);
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
