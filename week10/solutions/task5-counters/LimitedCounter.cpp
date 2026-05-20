#include "LimitedCounter.h"

LimitedCounter::LimitedCounter(int mx) : Counter(0, 1), max(mx)
{
}

LimitedCounter::LimitedCounter(int mx, int initial) : Counter(initial, 1), max(mx)
{
}

LimitedCounter::LimitedCounter(int mx, int initial, unsigned s) : Counter(initial, s), max(mx)
{
}

void LimitedCounter::increment()
{
    if (total + static_cast<int>(step) <= max)
    {
        Counter::increment();
    }
}

int LimitedCounter::getMax() const
{
    return max;
}
