#include "Scooter.h"

#include <ostream>

Scooter::Scooter(const String& make,
                 const String& model,
                 int capacityLuggage,
                 int maxCapacityOfDriver,
                 const String& color)
    : Motorcycle(make, model, /*horsepower*/ 30, capacityLuggage),
      maxCapacityOfDriver(maxCapacityOfDriver),
      color(color) {}

int Scooter::getMaxCapacityOfDriver() const { return maxCapacityOfDriver; }
const String& Scooter::getColor() const { return color; }

void Scooter::print(std::ostream& os) const {
    os << "Scooter{";
    Vehicle::print(os);
    os << ", luggageCapacity=" << getCapacityLuggage() << ", maxDriverCapacity=" << maxCapacityOfDriver
       << ", color=" << color.cStr() << "}";
}

