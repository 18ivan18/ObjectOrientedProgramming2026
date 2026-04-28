#include "Car.h"

#include <ostream>

Car::Car(const String& make, const String& model, int horsepower, int seats, FuelType fuelType)
    : Vehicle(make, model, horsepower), seats(seats), fuelType(fuelType) {}

int Car::getSeats() const { return seats; }
FuelType Car::getFuelType() const { return fuelType; }

void Car::print(std::ostream& os) const {
    os << "Car{";
    Vehicle::print(os);
    os << ", seats=" << seats << ", fuel=" << toString(fuelType) << "}";
}

