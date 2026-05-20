#ifndef PET_H
#define PET_H

#include "../../../utils/String.h"
#include "Animal.h"

class Pet : virtual public Animal
{
protected:
    String owner;

public:
    Pet(const char *name, const char *owner);
    void describe() const override;
};

#endif // PET_H
