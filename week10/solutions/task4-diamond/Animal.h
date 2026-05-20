#ifndef ANIMAL_H
#define ANIMAL_H

#include "../../../utils/String.h"

class Animal
{
protected:
    String name;

public:
    Animal(const char *name);
    virtual void describe() const;
    virtual ~Animal() = default;
};

#endif // ANIMAL_H
