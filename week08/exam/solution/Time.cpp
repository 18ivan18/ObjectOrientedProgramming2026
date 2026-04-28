#include "Time.h"

bool Time::isValid() const
{
    return hour <= 23 && minute <= 59;
}
