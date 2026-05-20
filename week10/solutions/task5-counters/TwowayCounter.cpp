#include "TwowayCounter.h"

TwowayCounter::TwowayCounter() : Counter()
{
}

TwowayCounter::TwowayCounter(int initial) : Counter(initial)
{
}

TwowayCounter::TwowayCounter(int initial, unsigned s) : Counter(initial, s)
{
}

void TwowayCounter::decrement()
{
    total -= static_cast<int>(step);
}
