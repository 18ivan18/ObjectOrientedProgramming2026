#include <iostream>
#include "Garage.h"
#include "Car.h"
#include "Truck.h"
#include "Minibus.h"

double totalIncome(Garage &g)
{
    double sum = 0;
    for (auto vehicle : g.getVehicles()) {
        sum += vehicle->getParkingPrice();
    }
    return sum;
}

int main()
{
    Garage g;

    g.addNewVehicle(new Car("CB 1234 AB", true, 4));
    g.addNewVehicle(new Car("PB 5678 CD", false, 2));
    g.addNewVehicle(new Truck("CB 9999 TT", 500));
    g.addNewVehicle(new Truck("PB 1111 KK", 200));
    g.addNewVehicle(new Minibus("CB 2222 MB", true, 8, 300, 4));
    g.addNewVehicle(new Minibus("PB 3333 MB", false, 6, 100, 3));

    std::cout << "Total income: " << totalIncome(g) << " lv.\n";
}
