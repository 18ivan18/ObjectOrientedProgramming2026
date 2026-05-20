#ifndef LIMITEDTWOWAYCOUNTER_H
#define LIMITEDTWOWAYCOUNTER_H

#include "LimitedCounter.h"
#include "TwowayCounter.h"

// LimitedCounter and TwowayCounter both inherit Counter virtually,
// so LimitedTwowayCounter has exactly one Counter subobject.
// As the most-derived class, LimitedTwowayCounter is responsible for
// initializing Counter directly in its initializer list.
class LimitedTwowayCounter : public LimitedCounter, public TwowayCounter
{
    int min;

public:
    LimitedTwowayCounter(int min, int max);
    LimitedTwowayCounter(int min, int max, int initial);
    LimitedTwowayCounter(int min, int max, int initial, unsigned step);
    void increment() override;
    void decrement() override;
    int getMin() const;
};

#endif // LIMITEDTWOWAYCOUNTER_H
