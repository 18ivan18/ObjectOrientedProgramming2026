#include "Intern.h"
#include <iostream>

Intern::Intern(const char *n, const char *uni) : Employee(n), university(uni)
{
}

void Intern::describe() const
{
    std::cout << "Intern: " << name.cStr() << ", from: " << university.cStr() << "\n";
}
