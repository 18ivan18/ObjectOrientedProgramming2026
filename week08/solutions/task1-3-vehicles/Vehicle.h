#ifndef VEHICLE_H
#define VEHICLE_H

#include <fstream>
#include "../../string/String.h"

class Vehicle
{
public:
    Vehicle(const String &make, const String &model, int horsepower);

    const String &getMake() const;
    const String &getModel() const;
    int getHorsepower() const;

    void print(std::ostream &os) const;

protected:
    void setHorsepower(int horsepower);

private:
    String make;
    String model;
    int horsepower = 0;
};

#endif // VEHICLE_H
