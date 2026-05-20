#include "Counter.h"

Counter::Counter() : total(0), step(1)
{
}

Counter::Counter(int initial) : total(initial), step(1)
{
}

Counter::Counter(int initial, unsigned s) : total(initial), step(s)
{
}

void Counter::increment()
{
    total += static_cast<int>(step);
}

int Counter::getTotal() const
{
    return total;
}

unsigned Counter::getStep() const
{
    return step;
}
