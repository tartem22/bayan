#include "hash_md5.h"
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

using namespace bayan::hash;
using namespace boost::uuids::detail;

static std::string getMd5(const char *buffer, size_t length)
{
    md5 hash;
    md5::digest_type digest;
    hash.process_bytes(buffer, length);
    hash.get_digest(digest);
    const auto intDigest = reinterpret_cast<const int *>(&digest);
    std::string result;
    boost::algorithm::hex(intDigest, intDigest + (sizeof(md5::digest_type) / sizeof(int)), std::back_inserter(result));
    return result;
}

Md5::Md5()
{
}

Md5::Md5(const char *buffer, size_t length)
{
    calculate(buffer, length);
}

bool Md5::operator==(const Hash &rhs)
{
    return equal(dynamic_cast<const Md5 &>(rhs));
}

bool Md5::operator!=(const Hash &rhs)
{
    return !equal(dynamic_cast<const Md5 &>(rhs));
}

bool Md5::equal(const Md5 &rhs)
{
    return hash == rhs.hash;
}

void Md5::calculate(const char *buffer, size_t length)
{
    hash = getMd5(buffer, length);
}
