#include "VendingMachine.h"
#include <cstring>

VendingMachine::VendingMachine() : drinkCount(0), income(0) {
    for (size_t i = 0; i < MAX_CAPACITY; i++) {
        drinks[i] = nullptr;
    }
}

VendingMachine::VendingMachine(const VendingMachine& other) : drinkCount(other.drinkCount), income(other.income) {
    for (size_t i = 0; i < MAX_CAPACITY; i++) {
        if (i < drinkCount) {
            drinks[i] = new Drink(*(other.drinks[i]));
        } else {
            drinks[i] = nullptr;
        }
    }
}

VendingMachine::VendingMachine(VendingMachine&& other) noexcept
    : drinkCount(other.drinkCount), income(other.income) {
    for (size_t i = 0; i < MAX_CAPACITY; i++) {
        drinks[i] = other.drinks[i];
        other.drinks[i] = nullptr;
    }
    other.drinkCount = 0;
    other.income = 0;
}

VendingMachine& VendingMachine::operator=(const VendingMachine& other) {
    if (this != &other) {
        for (size_t i = 0; i < drinkCount; i++) {
            delete drinks[i];
            drinks[i] = nullptr;
        }
        drinkCount = other.drinkCount;
        income = other.income;
        for (size_t i = 0; i < MAX_CAPACITY; i++) {
            if (i < drinkCount) {
                drinks[i] = new Drink(*(other.drinks[i]));
            } else {
                drinks[i] = nullptr;
            }
        }
    }
    return *this;
}

VendingMachine& VendingMachine::operator=(VendingMachine&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < drinkCount; i++) {
            delete drinks[i];
            drinks[i] = nullptr;
        }
        drinkCount = other.drinkCount;
        income = other.income;
        for (size_t i = 0; i < MAX_CAPACITY; i++) {
            drinks[i] = other.drinks[i];
            other.drinks[i] = nullptr;
        }
        other.drinkCount = 0;
        other.income = 0;
    }
    return *this;
}

VendingMachine::~VendingMachine() {
    for (size_t i = 0; i < drinkCount; i++) {
        delete drinks[i];
        drinks[i] = nullptr;
    }
}

int VendingMachine::findDrinkByName(const char* drinkName) const {
    for (size_t i = 0; i < drinkCount; i++) {
        if (strcmp(drinks[i]->getName(), drinkName) == 0) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool VendingMachine::addDrink(const Drink& toBeAdded) {
    if (drinkCount >= MAX_CAPACITY) {
        return false;
    }
    if (findDrinkByName(toBeAdded.getName()) != -1) {
        return false;
    }
    drinks[drinkCount++] = new Drink(toBeAdded);
    return true;
}

bool VendingMachine::addDrink(Drink&& toBeAdded) {
    if (drinkCount >= MAX_CAPACITY) {
        return false;
    }
    if (findDrinkByName(toBeAdded.getName()) != -1) {
        return false;
    }
    drinks[drinkCount++] = new Drink(std::move(toBeAdded));
    return true;
}

bool VendingMachine::fillUpDrink(const Drink& toBeFilledUp) {
    int index = findDrinkByName(toBeFilledUp.getName());
    if (index == -1) {
        return false;
    }
    drinks[index]->setQuantity(toBeFilledUp.getQuantity());
    return true;
}

double VendingMachine::buyDrink(const char* drinkName, double money, double quantity) {
    int index = findDrinkByName(drinkName);
    if (index == -1) {
        return -2.0;
    }

    Drink* drink = drinks[index];
    double availableQuantity = drink->getQuantity();
    double pricePerLiter = drink->getPrice();

    double quantityToSell = (quantity <= availableQuantity) ? quantity : availableQuantity;
    double cost = quantityToSell * pricePerLiter;

    if (money < cost) {
        income += money;
        return -1.0;
    }

    income += cost;
    double change = money - cost;
    drink->setQuantity(availableQuantity - quantityToSell);

    if (drink->getQuantity() < 0.001) {
        delete drinks[index];
        for (size_t i = static_cast<size_t>(index); i < drinkCount - 1; i++) {
            drinks[i] = drinks[i + 1];
        }
        drinks[--drinkCount] = nullptr;
    }

    return change;
}

double VendingMachine::getIncome() const {
    return income;
}

void VendingMachine::sortDrinksByCalories() {
    for (size_t i = 0; i < drinkCount; i++) {
        for (size_t j = i + 1; j < drinkCount; j++) {
            if (*(drinks[j]) < *(drinks[i])) {
                Drink* temp = drinks[i];
                drinks[i] = drinks[j];
                drinks[j] = temp;
            }
        }
    }
}
