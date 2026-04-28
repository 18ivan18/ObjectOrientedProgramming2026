#include "Address.h"

#include <ostream>

void Address::print(std::ostream& os) const {
    os << city.cStr() << ", " << street.cStr();
}

