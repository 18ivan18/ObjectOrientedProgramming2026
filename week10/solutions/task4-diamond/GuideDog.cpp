#include "GuideDog.h"
#include <iostream>

GuideDog::GuideDog(const char *n, const char *o) : Animal(n), Pet(n, o)
{
}

void GuideDog::describe() const
{
    std::cout << "GuideDog: " << name.cStr() << ", owner: " << owner.cStr() << "\n";
}
