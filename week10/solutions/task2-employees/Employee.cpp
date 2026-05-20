#include "Employee.h"
#include <iostream>

Employee::Employee(const char *n) : name(n)
{
}

void Employee::describe() const
{
    std::cout << "Employee: " << name.cStr() << "\n";
}
