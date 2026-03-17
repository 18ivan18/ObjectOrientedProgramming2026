// Компилиране: g++ -o 4 4.cpp LicenceKey.cpp Timestamp.cpp
#include "LicenceKey.h"
#include <iostream>

int main()
{
    LicenceKey personal(LicenceType::PERSONAL);
    std::cout << "Personal: remaining=" << personal.remainingActivations()
              << ", canActivate=" << (personal.canActivate() ? "да" : "не")
              << ", isExpired=" << (personal.isExpired() ? "да" : "не") << '\n';

    int k = personal.activate();
    std::cout << "activate()=" << k << ", remaining=" << personal.remainingActivations() << '\n';
    std::cout << "activate()=" << personal.activate() << " (изчерпан)\n";

    LicenceKey family(LicenceType::FAMILY);
    std::cout << "\nFamily: remaining=" << family.remainingActivations() << '\n';

    LicenceKey expired(LicenceType::PERSONAL, 2020, 1, 1);
    std::cout << "\nИзтекъл лиценз (2020): isExpiredByDate=" << (expired.isExpiredByDate() ? "да" : "не") << '\n';
}
