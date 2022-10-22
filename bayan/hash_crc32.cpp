#include "hash_crc32.h"
#include <boost/crc.hpp>

using namespace bayan::hash;

static uint32_t getCrc32(const char *buffer, size_t length)
{
    boost::crc_32_type result;
    result.process_bytes(buffer, length);
    return result.checksum();
}

Crc32::Crc32()
{
}

Crc32::Crc32(const char *buffer, size_t length)
{
    calculate(buffer, length);
}

bool Crc32::operator==(const Hash &rhs)
{
    return equal(dynamic_cast<const Crc32 &>(rhs));
}

bool Crc32::operator!=(const Hash &rhs)
{
    return !equal(dynamic_cast<const Crc32 &>(rhs));
}

bool Crc32::equal(const Crc32 &rhs)
{
    return crc32 == rhs.crc32;
}

void Crc32::calculate(const char *buffer, size_t length)
{
    crc32 = getCrc32(buffer, length);
}
