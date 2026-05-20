#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "../../../utils/String.h"

class Employee
{
protected:
    String name;

public:
    Employee(const char *name);
    virtual void describe() const;
    virtual ~Employee() = default;
};

#endif // EMPLOYEE_H
