#include "Manager.h"
#include <iostream>

Manager::Manager(const char *n, int size) : Employee(n), teamSize(size)
{
}

void Manager::describe() const
{
    std::cout << "Manager: " << name.cStr() << ", team: " << teamSize << "\n";
}
