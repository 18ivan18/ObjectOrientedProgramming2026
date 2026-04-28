#pragma once

#include "Time.h"
#include <cstddef>
#include <iosfwd>

const size_t ORDER_MAX_DISH_NAME_LEN = 127;
const size_t ORDER_MAX_DISHES = 128;

class Order
{
private:
    size_t tableNumber;
    Time receivedTime;
    char dishNames[ORDER_MAX_DISHES][ORDER_MAX_DISH_NAME_LEN + 1];
    size_t dishCount;

    void clearDishes();

public:
    Order();
    Order(const Order &other) = default;
    Order(Order &&other) noexcept = default;
    Order &operator=(const Order &other) = default;
    Order &operator=(Order &&other) noexcept = default;
    ~Order() = default;

    void setTableNumber(size_t t);
    void setTime(unsigned h, unsigned m);
    void setTime(Time t);

    bool addDish(const char *name);

    size_t getTableNumber() const;
    void getTime(unsigned &h, unsigned &m) const;
    Time getTime() const;
    bool isValid() const;
    size_t getDishCount() const;
    const char *getDishName(size_t index) const;

    // Двоичен запис на една поръчка: size_t table; uint8_t hour, minute; size_t dishCount;
    // след това dishCount пъти: uint8_t len (≤127), следвано от len байта без '\0'.
    bool deserialize(std::istream &in);
    bool serialize(std::ostream &out) const;
};

bool skipOrderSerialized(std::istream &in);
