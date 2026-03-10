// Компилиране: g++ -o 3 3.cpp WaterDispenser.cpp
#include "WaterDispenser.h"
#include <iostream>

int main()
{
    WaterDispenser dispenser(5.0);

    dispenser.fillDispenser(3.0);
    std::cout << "След пълнене: " << dispenser.getCurrentLiters() << " л\n";

    if (dispenser.fillCup(250))
    {
        std::cout << "Чаша 250 мл напълнена. Остават: " << dispenser.getCurrentLiters() << " л\n";
    }

    if (dispenser.fillCup(500))
    {
        std::cout << "Бутилка 500 мл напълнена. Остават: " << dispenser.getCurrentLiters() << " л\n";
    }

    if (dispenser.fillCup(3000))
    {
        std::cout << "Бутилка 3000 мл напълнена. Остават: " << dispenser.getCurrentLiters() << " л\n";
    }

    if (dispenser.fillDispenser(4.0))
    {
        std::cout << "След допълнително пълнене: " << dispenser.getCurrentLiters() << " л\n";
    }
}
