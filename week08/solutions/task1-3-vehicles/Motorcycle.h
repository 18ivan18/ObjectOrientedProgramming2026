#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "Vehicle.h"

class Motorcycle : public Vehicle {
public:
    Motorcycle(const String& make, const String& model, int horsepower, int capacityLuggage);

    int getCapacityLuggage() const;

    void print(std::ostream& os) const override;

private:
    int capacityLuggage = 0;
};

#endif // MOTORCYCLE_H
