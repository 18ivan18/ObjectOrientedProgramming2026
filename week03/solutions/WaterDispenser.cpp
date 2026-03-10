#include "WaterDispenser.h"
#include <iostream>

WaterDispenser::WaterDispenser(double max) : currentLiters(0), maxLiters(max)
{
}

double WaterDispenser::getCurrentLiters() const
{
    return currentLiters;
}

double WaterDispenser::getMaxLiters() const
{
    return maxLiters;
}

bool WaterDispenser::fillCup(int milliliters)
{
    double litersNeeded = milliliters / 1000.0;
    if (litersNeeded > currentLiters)
    {
        std::cout << "Грешка: Недостатъчно вода. Има " << currentLiters << " л, нужни са " << litersNeeded << " л.\n";
        return false;
    }
    currentLiters -= litersNeeded;
    return true;
}

bool WaterDispenser::fillDispenser(double liters)
{
    double total = currentLiters + liters;
    if (total > maxLiters)
    {
        currentLiters = maxLiters;
        std::cout << "Диспенсърът е пълен. Преляха " << (total - maxLiters) << " л.\n";
        return false;
    }

    currentLiters = total;
    return true;
}
