#ifndef SCOOTER_H
#define SCOOTER_H

#include "Motorcycle.h"

class Scooter : public Motorcycle {
public:
    Scooter(const String& make,
            const String& model,
            int capacityLuggage,
            int maxCapacityOfDriver,
            const String& color);

    int getMaxCapacityOfDriver() const;
    const String& getColor() const;

    void print(std::ostream& os) const override;

private:
    int maxCapacityOfDriver = 0;
    String color;
};

#endif // SCOOTER_H
