#ifndef CAR_H
#define CAR_H

#include "FuelType.h"
#include "Vehicle.h"

class Car : public Vehicle {
public:
    Car(const String& make, const String& model, int horsepower, int seats, FuelType fuelType);

    int getSeats() const;
    FuelType getFuelType() const;

    void print(std::ostream& os) const override;

private:
    int seats = 0;
    FuelType fuelType = FuelType::Unknown;
};

#endif // CAR_H
