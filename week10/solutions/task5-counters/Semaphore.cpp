#include "Semaphore.h"

Semaphore::Semaphore() : Counter(0, 1), LimitedTwowayCounter(0, 1)
{
}

Semaphore::Semaphore(bool initiallyAvailable)
    : Counter(initiallyAvailable ? 1 : 0, 1), LimitedTwowayCounter(0, 1, initiallyAvailable ? 1 : 0)
{
}

bool Semaphore::isAvailable() const
{
    return total > 0;
}

void Semaphore::wait()
{
    decrement();
}

void Semaphore::signal()
{
    increment();
}
