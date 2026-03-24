#ifndef DRINK_H
#define DRINK_H

#include <ostream>

class Drink {
private:
    char* name;
    double quantity;   // в литри
    double calories;   // per 100ml
    double price;      // лв/литър

    void copyFrom(const Drink& other);
    void free();

public:
    Drink(const char* name, double quantity, double calories, double price);
    Drink(const Drink& other);
    Drink& operator=(const Drink& other);
    Drink(Drink&& other) noexcept;
    Drink& operator=(Drink&& other) noexcept;
    ~Drink();

    const char* getName() const;
    double getQuantity() const;
    double getCalories() const;
    double getPrice() const;

    void setQuantity(double quantity);

    bool operator==(const Drink& other) const;
    bool operator<(const Drink& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Drink& drink);
};

#endif
