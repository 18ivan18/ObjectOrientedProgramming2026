#include "Drink.h"
#include <cstring>
#include <iostream>

void Drink::copyFrom(const Drink& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    quantity = other.quantity;
    calories = other.calories;
    price = other.price;
}

void Drink::free() {
    delete[] name;
}

Drink::Drink(const char* name, double quantity, double calories, double price)
    : quantity(quantity), calories(calories), price(price) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

Drink::Drink(const Drink& other) {
    copyFrom(other);
}

Drink& Drink::operator=(const Drink& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Drink::Drink(Drink&& other) noexcept
    : name(other.name), quantity(other.quantity), calories(other.calories), price(other.price) {
    other.name = nullptr;
}

Drink& Drink::operator=(Drink&& other) noexcept {
    if (this != &other) {
        free();
        name = other.name;
        quantity = other.quantity;
        calories = other.calories;
        price = other.price;
        other.name = nullptr;
    }
    return *this;
}

Drink::~Drink() {
    free();
}

const char* Drink::getName() const {
    return name;
}

double Drink::getQuantity() const {
    return quantity;
}

double Drink::getCalories() const {
    return calories;
}

double Drink::getPrice() const {
    return price;
}

void Drink::setQuantity(double quantity) {
    this->quantity = quantity;
}

bool Drink::operator==(const Drink& other) const {
    return strcmp(name, other.name) == 0;
}

bool Drink::operator<(const Drink& other) const {
    return calories < other.calories;
}

std::ostream& operator<<(std::ostream& os, const Drink& drink) {
    os << drink.name << " - " << drink.quantity << " L, "
       << drink.calories << " cal/100ml, " << drink.price << " лв/L";
    return os;
}
