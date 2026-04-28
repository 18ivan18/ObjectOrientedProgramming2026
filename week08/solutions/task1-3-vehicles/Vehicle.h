#ifndef VEHICLE_H
#define VEHICLE_H

#include "../../string/String.h"

#include <iosfwd>

class Vehicle {
public:
    Vehicle(const String& make, const String& model, int horsepower);

    const String& getMake() const;
    const String& getModel() const;
    int getHorsepower() const;

    void print(std::ostream& os) const;

protected:
    void setHorsepower(int horsepower);

private:
    String make;
    String model;
    int horsepower = 0;
};

#endif // VEHICLE_H
