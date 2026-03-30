#pragma once

#include "StrictRecord.h"
#include <iostream>

// Само изход — няма operator>> за StrictRecord, защото няма как да създадем
// временен обект без конструктор по подразбиране преди четене от реда.
inline std::ostream& operator<<(std::ostream& os, const StrictRecord& r) {
    os << r.getId() << '|' << r.getScore() << '|' << r.getName();
    return os;
}
