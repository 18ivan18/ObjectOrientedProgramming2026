#ifndef DUCK_H
#define DUCK_H

#include "IFlyable.h"
#include "IRunnable.h"
#include "ISwimmable.h"

class Duck : public IFlyable, public ISwimmable, public IRunnable
{
public:
    void fly() override;
    void swim() override;
    void run() override;
};

#endif // DUCK_H
