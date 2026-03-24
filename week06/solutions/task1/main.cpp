#include <iostream>
#include <utility>
#include "Drink.h"
#include "VendingMachine.h"

int main() {
    VendingMachine machine;

    Drink cola("Кола", 10.0, 42, 2.50);
    Drink water("Вода", 5.0, 0, 1.00);
    Drink juice("Сок", 3.0, 45, 3.00);

    std::cout << "Добавяне на напитки:" << std::endl;
    std::cout << "Кола добавена: " << (machine.addDrink(cola) ? "да" : "не") << std::endl;
    std::cout << "Вода добавена: " << (machine.addDrink(water) ? "да" : "не") << std::endl;
    std::cout << "Сок добавена: " << (machine.addDrink(juice) ? "да" : "не") << std::endl;
    std::cout << "Кола отново (вече съществува): " << (machine.addDrink(cola) ? "да" : "не") << std::endl;

    std::cout << "\nДобавяне с move semantics (rvalue):" << std::endl;
    std::cout << "Временна напитка (addDrink с rvalue): "
              << (machine.addDrink(Drink("Енергийна", 2.0, 60, 4.0)) ? "да" : "не") << std::endl;
    Drink iceTea("Леден чай", 5.0, 35, 2.80);
    std::cout << "addDrink(std::move(iceTea)): " << (machine.addDrink(std::move(iceTea)) ? "да" : "не") << std::endl;

    std::cout << "\nДоливане на Кола с 15 литра:" << std::endl;
    Drink colaRefill("Кола", 15.0, 42, 2.50);
    std::cout << "Доливане: " << (machine.fillUpDrink(colaRefill) ? "успешно" : "неуспешно") << std::endl;

    std::cout << "\nЗакупуване:" << std::endl;
    double change = machine.buyDrink("Кола", 10.0, 2.0);
    std::cout << "Купуване 2L Кола с 10 лв - ресто: " << change << " лв" << std::endl;

    change = machine.buyDrink("Вода", 0.50, 1.0);
    std::cout << "Купуване 1L Вода с 0.50 лв (недостатъчно пари) - резултат: " << change << std::endl;

    change = machine.buyDrink("Минерална", 5.0, 1.0);
    std::cout << "Купуване несъществуваща напитка - резултат: " << change << std::endl;

    std::cout << "\nПриход от продажби: " << machine.getIncome() << " лв" << std::endl;

    std::cout << "\n--- Move constructor ---" << std::endl;
    VendingMachine machine2(std::move(machine));
    std::cout << "machine2 приход (след move от machine): " << machine2.getIncome() << " лв" << std::endl;

    std::cout << "\n--- Move assignment ---" << std::endl;
    VendingMachine machine3;
    machine3.addDrink(Drink("Вода", 1.0, 0, 1.0));
    machine3 = std::move(machine2);
    std::cout << "machine3 приход (след move assignment от machine2): " << machine3.getIncome() << " лв" << std::endl;
}
