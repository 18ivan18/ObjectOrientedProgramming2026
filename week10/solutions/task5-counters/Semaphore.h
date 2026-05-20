#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "LimitedTwowayCounter.h"

class Semaphore : public LimitedTwowayCounter
{
public:
    Semaphore();
    Semaphore(bool initiallyAvailable);
    bool isAvailable() const;
    void wait();
    void signal();
};

#endif // SEMAPHORE_H
