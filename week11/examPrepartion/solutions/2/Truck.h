#ifndef TRUCK_H
#define TRUCK_H
#include "Vehicle.h"
#include "RoadType.h"

class Truck : public Vehicle
{
public:
    Truck(const String &make, int maxSpeed);
    int getSpeedAccordingToRoadType(RoadType rt) override;
    Vehicle *clone() const override;
};

#endif