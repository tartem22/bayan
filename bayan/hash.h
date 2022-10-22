#ifndef HASH_H
#define HASH_H

#include <cstddef>

class Hash
{
public:
    virtual bool operator==(const Hash &rhs) = 0;
    virtual bool operator!=(const Hash &rhs) = 0;

protected:
    virtual void calculate(const char *buffer, size_t length) = 0;
};

#endif // HASH_H