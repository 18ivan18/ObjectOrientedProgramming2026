#ifndef ADDRESS_H
#define ADDRESS_H

#include "../../string/String.h"

#include <iosfwd>

struct Address {
    String city;
    String street;

    void print(std::ostream& os) const;
};

#endif // ADDRESS_H
