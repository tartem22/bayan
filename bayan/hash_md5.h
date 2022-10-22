#ifndef BAYAN_HASH_MD5
#define BAYAN_HASH_MD5

#include <string>
#include "hash.h"

namespace bayan::hash
{
    class Md5 : public Hash
    {
    public:
        Md5();
        Md5(const char *buffer, size_t length);
        bool operator==(const Hash &rhs) override;
        bool operator!=(const Hash &rhs) override;

    private:
        bool equal(const Md5 &rhs);
        void calculate(const char *buffer, size_t length) override;
        std::string hash;
    };
}

#endif // BAYAN_HASH_MD5