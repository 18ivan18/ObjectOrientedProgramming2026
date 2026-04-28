#include "Vehicle.h"

#include <ostream>

Vehicle::Vehicle(const String& make, const String& model, int horsepower)
    : make(make), model(model), horsepower(horsepower) {}

const String& Vehicle::getMake() const { return make; }
const String& Vehicle::getModel() const { return model; }
int Vehicle::getHorsepower() const { return horsepower; }

void Vehicle::setHorsepower(int horsepower) { this->horsepower = horsepower; }

void Vehicle::print(std::ostream& os) const {
    os << "make=" << make.cStr() << ", model=" << model.cStr() << ", hp=" << horsepower;
}

