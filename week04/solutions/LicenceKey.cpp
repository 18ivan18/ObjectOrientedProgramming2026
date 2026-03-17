#include "LicenceKey.h"
#include <cstdlib>
#include <ctime>

int getMaxActivations(LicenceKey::LicenceType t)
{
    switch (t)
    {
    case LicenceKey::LicenceType::PERSONAL:
        return 1;
    case LicenceKey::LicenceType::FAMILY:
        return 5;
    case LicenceKey::LicenceType::ENTERPRISE:
        return -1;
    }
    return 1;
}

LicenceKey::LicenceKey(LicenceType t) : type(t), expirationDate(2030, 12, 31)
{
    activationsLeft = new int(getMaxActivations(t));
    if (*activationsLeft < 0)
        *activationsLeft = 999;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    key = 10000000 + (std::rand() % 90000000);
}

LicenceKey::LicenceKey(LicenceType t, int year, int month, int day)
    : type(t), expirationDate(year, month, day)
{
    activationsLeft = new int(getMaxActivations(t));
    if (*activationsLeft < 0)
        *activationsLeft = 999;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    key = 10000000 + (std::rand() % 90000000);
}

LicenceKey::LicenceKey(const LicenceKey &from)
    : key(from.key), type(from.type), expirationDate(from.expirationDate)
{
    if (from.activationsLeft)
    {
        activationsLeft = from.activationsLeft;
        from.activationsLeft = nullptr;
        if (type != LicenceType::ENTERPRISE && *activationsLeft > 0)
            (*activationsLeft)--;
    }
    else
    {
        activationsLeft = new int(0);
    }
}

LicenceKey::~LicenceKey()
{
    delete activationsLeft;
}

int LicenceKey::activate()
{
    if (!canActivate())
        return -1;
    if (type != LicenceType::ENTERPRISE && activationsLeft)
        (*activationsLeft)--;
    return key;
}

int LicenceKey::remainingActivations() const
{
    if (!activationsLeft)
        return 0;
    return *activationsLeft > 0 ? *activationsLeft : 0;
}

bool LicenceKey::canActivate() const
{
    if (isExpiredByDate())
        return false;
    if (type == LicenceType::ENTERPRISE)
        return true;
    return activationsLeft && *activationsLeft > 0;
}

bool LicenceKey::isExpired() const
{
    if (type == LicenceType::ENTERPRISE)
        return false;
    return !activationsLeft || *activationsLeft <= 0;
}

bool LicenceKey::isExpiredByDate() const
{
    return now().isAfter(expirationDate);
}
