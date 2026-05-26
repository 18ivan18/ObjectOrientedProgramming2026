#include "Garage.h"

Garage::Garage(int maxCapacity) : vehicles(maxCapacity) {}

Garage::Garage(const Garage &other) : vehicles(other.vehicles.getCapacity())
{
    for (std::size_t i = 0; i < other.vehicles.getSize(); i++)
    {
        vehicles.pushBack(other.vehicles[i]->clone());
    }
}

Garage &Garage::operator=(const Garage &rhs)
{
    if (this != &rhs)
    {
        for (std::size_t i = 0; i < vehicles.getSize(); i++)
        {
            delete vehicles[i];
        }
        vehicles = Vector<Vehicle *>(rhs.vehicles.getCapacity());
        for (std::size_t i = 0; i < rhs.vehicles.getSize(); i++)
        {
            vehicles.pushBack(rhs.vehicles[i]->clone());
        }
    }
    return *this;
}

Garage::~Garage()
{
    for (std::size_t i = 0; i < vehicles.getSize(); i++)
    {
        delete vehicles[i];
    }
}

void Garage::addNewVehicle(Vehicle *&v)
{
    vehicles.pushBack(v);
}

void Garage::addNewVehicle(Vehicle *&&v)
{
    vehicles.pushBack(v);
}

int Garage::getAllVehiclesThatCanTravelRoad(int highwayLength, int speedLength, int thirdrateLength, int time)
{
    int cnt = 0;
    for (std::size_t i = 0; i < vehicles.getSize(); i++)
    {
        double speedHighway = vehicles[i]->getSpeedAccordingToRoadType(RoadType::Highway);
        double speedSpeedRoad = vehicles[i]->getSpeedAccordingToRoadType(RoadType::Speed);
        double speedThirdRate = vehicles[i]->getSpeedAccordingToRoadType(RoadType::ThirdClass);
        int t = highwayLength / speedHighway + speedLength / speedSpeedRoad + thirdrateLength / speedThirdRate;
        cnt += t < time;
    }
    return cnt;
}
