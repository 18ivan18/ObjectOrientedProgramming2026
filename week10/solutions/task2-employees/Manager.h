#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"

class Manager : public Employee
{
    int teamSize;

public:
    Manager(const char *name, int teamSize);
    void describe() const override;
};

#endif // MANAGER_H
