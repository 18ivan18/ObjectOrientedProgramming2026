#ifndef MINIVAN_H
#define MINIVAN_H
#include "RoadType.h"
#include "Vehicle.h"

class Minivan : public Vehicle
{
public:
    Minivan(const String &make, int maxSpeed);
    int getSpeedAccordingToRoadType(RoadType rt) override;
    Vehicle *clone() const override;
};

#endif