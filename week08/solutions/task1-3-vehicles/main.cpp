#include "Car.h"
#include "Motorcycle.h"
#include "Scooter.h"

#include <iostream>

int main()
{
    Car c("Toyota", "Corolla", 132, 5, FuelType::Petrol);
    Motorcycle m("Honda", "CB500F", 47, 25);
    Scooter s("Vespa", "Primavera", 5, 120, "red");

    std::cout << "Task 1/3 demo\n";
    c.print(std::cout);
    std::cout << "\n";
    m.print(std::cout);
    std::cout << "\n";
    s.print(std::cout);
    std::cout << "\n\n";
}
