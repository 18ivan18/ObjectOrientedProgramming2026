#ifndef LIMITEDCOUNTER_H
#define LIMITEDCOUNTER_H

#include "Counter.h"

class LimitedCounter : virtual public Counter
{
protected:
    int max;

public:
    LimitedCounter(int max);
    LimitedCounter(int max, int initial);
    LimitedCounter(int max, int initial, unsigned step);
    void increment() override;
    int getMax() const;
};

#endif // LIMITEDCOUNTER_H
