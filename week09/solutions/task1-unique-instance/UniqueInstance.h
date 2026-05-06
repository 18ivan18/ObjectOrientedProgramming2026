#ifndef UNIQUE_INSTANCE_H
#define UNIQUE_INSTANCE_H

#include <cstddef>

class UniqueInstance
{
    std::size_t id;
    static std::size_t nextId;

public:
    UniqueInstance();
    UniqueInstance(const UniqueInstance &other);
    UniqueInstance &operator=(const UniqueInstance &other);
    ~UniqueInstance();

    std::size_t getId() const;

    static std::size_t getNextId();
};

#endif
