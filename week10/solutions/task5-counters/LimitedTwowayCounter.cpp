#include "LimitedTwowayCounter.h"

LimitedTwowayCounter::LimitedTwowayCounter(int mn, int mx) : Counter(0, 1), LimitedCounter(mx), TwowayCounter(), min(mn)
{
}

LimitedTwowayCounter::LimitedTwowayCounter(int mn, int mx, int initial)
    : Counter(initial, 1), LimitedCounter(mx, initial), TwowayCounter(initial), min(mn)
{
}

LimitedTwowayCounter::LimitedTwowayCounter(int mn, int mx, int initial, unsigned s)
    : Counter(initial, s), LimitedCounter(mx, initial, s), TwowayCounter(initial, s), min(mn)
{
}

void LimitedTwowayCounter::increment()
{
    LimitedCounter::increment();
}

void LimitedTwowayCounter::decrement()
{
    if (total - static_cast<int>(step) >= min)
    {
        total -= static_cast<int>(step);
    }
}

int LimitedTwowayCounter::getMin() const
{
    return min;
}
