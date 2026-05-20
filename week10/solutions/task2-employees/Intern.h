#ifndef INTERN_H
#define INTERN_H

#include "Employee.h"

class Intern : public Employee
{
    String university;

public:
    Intern(const char *name, const char *university);
    void describe() const override;
};

#endif // INTERN_H
