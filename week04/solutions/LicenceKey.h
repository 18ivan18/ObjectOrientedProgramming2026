#ifndef LICENCEKEY_H
#define LICENCEKEY_H

#include "Timestamp.h"
#include <random>

int getMaxActivations(LicenceKey::LicenceType t);

class LicenceKey
{
public:
    enum class LicenceType
    {
        PERSONAL = 1,
        FAMILY = 5,
        ENTERPRISE = -1,
    };

    LicenceKey(LicenceType type = LicenceType::PERSONAL);
    LicenceKey(LicenceType type, int year, int month, int day);
    LicenceKey(const LicenceKey &from);
    ~LicenceKey();

    int activate();

    int remainingActivations() const;
    bool canActivate() const;
    bool isExpired() const;
    bool isExpiredByDate() const;

private:
    int key;
    mutable int *activationsLeft;
    LicenceType type;
    Timestamp expirationDate;
};

#endif
