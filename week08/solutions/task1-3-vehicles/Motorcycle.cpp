#include "Motorcycle.h"

#include <ostream>

Motorcycle::Motorcycle(const String& make, const String& model, int horsepower, int capacityLuggage)
    : Vehicle(make, model, horsepower), capacityLuggage(capacityLuggage) {}

int Motorcycle::getCapacityLuggage() const { return capacityLuggage; }

void Motorcycle::print(std::ostream& os) const {
    os << "Motorcycle{";
    Vehicle::print(os);
    os << ", luggageCapacity=" << capacityLuggage << "}";
}

