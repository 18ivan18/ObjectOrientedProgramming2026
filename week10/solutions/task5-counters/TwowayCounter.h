#ifndef TWOWAYCOUNTER_H
#define TWOWAYCOUNTER_H

#include "Counter.h"

class TwowayCounter : virtual public Counter
{
public:
    TwowayCounter();
    TwowayCounter(int initial);
    TwowayCounter(int initial, unsigned step);
    virtual void decrement();
};

#endif // TWOWAYCOUNTER_H
