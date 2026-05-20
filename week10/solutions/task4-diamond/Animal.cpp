#include "Animal.h"
#include <iostream>

Animal::Animal(const char *n) : name(n)
{
}

void Animal::describe() const
{
    std::cout << "Animal: " << name.cStr() << "\n";
}
