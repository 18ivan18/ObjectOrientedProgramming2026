#include "Pet.h"
#include <iostream>

Pet::Pet(const char *n, const char *o) : Animal(n), owner(o)
{
}

void Pet::describe() const
{
    std::cout << "Pet: " << name.cStr() << ", owner: " << owner.cStr() << "\n";
}
