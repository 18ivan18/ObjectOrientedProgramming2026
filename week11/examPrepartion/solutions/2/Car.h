#ifndef CAR_H
#define CAR_H
#include "Vehicle.h"
#include "RoadType.h"

class Car : public Vehicle
{
public:
    Car(const String &make, int maxSpeed);
    int getSpeedAccordingToRoadType(RoadType rt) override;
    Vehicle *clone() const override;
};

#endif