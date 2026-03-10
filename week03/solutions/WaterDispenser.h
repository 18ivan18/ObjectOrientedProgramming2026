#ifndef WATER_DISPENSER_H
#define WATER_DISPENSER_H

class WaterDispenser
{
private:
    double currentLiters;
    double maxLiters;

public:
    WaterDispenser(double maxLiters = 5.0);

    double getCurrentLiters() const;
    double getMaxLiters() const;

    bool fillCup(int milliliters);
    bool fillDispenser(double liters);
};

#endif
