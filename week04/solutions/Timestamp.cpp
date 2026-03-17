#include "Timestamp.h"
#include <ctime>

Timestamp::Timestamp() : totalSeconds(0)
{
    totalSeconds = static_cast<unsigned long>(time(nullptr));
}

Timestamp::Timestamp(int year, int month, int day) : totalSeconds(0)
{
    struct tm t = {};
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_isdst = -1;
    totalSeconds = static_cast<unsigned long>(mktime(&t));
}

Timestamp::Timestamp(unsigned long seconds) : totalSeconds(seconds)
{
}

unsigned long Timestamp::toSeconds() const
{
    return totalSeconds;
}

Timestamp now()
{
    return Timestamp();
}

bool Timestamp::isBefore(const Timestamp &other) const
{
    return totalSeconds < other.totalSeconds;
}

bool Timestamp::isAfter(const Timestamp &other) const
{
    return totalSeconds > other.totalSeconds;
}
