#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include "Drink.h"

const size_t MAX_CAPACITY = 20;

class VendingMachine {
private:
    Drink* drinks[MAX_CAPACITY];
    size_t drinkCount;
    double income;

    int findDrinkByName(const char* drinkName) const;

public:
    VendingMachine();
    VendingMachine(const VendingMachine& other);
    VendingMachine(VendingMachine&& other) noexcept;
    VendingMachine& operator=(const VendingMachine& other);
    VendingMachine& operator=(VendingMachine&& other) noexcept;
    ~VendingMachine();

    bool addDrink(const Drink& toBeAdded);
    bool addDrink(Drink&& toBeAdded);
    bool fillUpDrink(const Drink& toBeFilledUp);
    double buyDrink(const char* drinkName, double money, double quantity);

    double getIncome() const;

    void sortDrinksByCalories();
};

#endif
