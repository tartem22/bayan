#ifndef BAYAN_HASH_CRC32
#define BAYAN_HASH_CRC32

#include <cstddef>

#include "hash.h"

namespace bayan::hash
{
    class Crc32 : public Hash
    {
    public:
        Crc32();
        Crc32(const char *buffer, size_t length);
        bool operator==(const Hash &rhs) override;
        bool operator!=(const Hash &rhs) override;

    private:
        bool equal(const Crc32 &rhs);
        void calculate(const char *buffer, size_t length) override;
        int crc32 = 0;
    };
}

#endif // BAYAN_HASH_CRC32