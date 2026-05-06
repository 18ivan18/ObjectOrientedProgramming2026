#include "UniqueInstance.h"

std::size_t UniqueInstance::nextId = 1;

UniqueInstance::UniqueInstance() : id(nextId++) {}

UniqueInstance::UniqueInstance(const UniqueInstance &) : id(nextId++) {}

UniqueInstance &UniqueInstance::operator=(const UniqueInstance &)
{
    // Assignment does not create a new object => id must not change.
    return *this;
}

UniqueInstance::~UniqueInstance() = default;

std::size_t UniqueInstance::getId() const
{
    return id;
}

std::size_t UniqueInstance::getNextId()
{
    return nextId;
}
