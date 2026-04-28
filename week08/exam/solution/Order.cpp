#include "Order.h"
#include <cstring>
#include <istream>
#include <ostream>

bool cstrEqual(const char *a, const char *b)
{
    if (a == nullptr || b == nullptr) {
        return a == b;
    }
    return std::strcmp(a, b) == 0;
}

bool readRaw(std::istream &in, void *dest, std::streamsize bytes)
{
    in.read((char *)(dest), bytes);
    return in.good() && (in.gcount() == bytes);
}

bool writeRaw(std::ostream &out, const void *src, std::streamsize bytes)
{
    out.write((const char *)(src), bytes);
    return out.good();
}

void Order::clearDishes()
{
    dishCount = 0;
    std::memset(dishNames, 0, sizeof(dishNames));
}

Order::Order() : tableNumber(0), receivedTime{0, 0}, dishCount(0)
{
    std::memset(dishNames, 0, sizeof(dishNames));
}

void Order::setTableNumber(size_t t)
{
    tableNumber = t;
}

void Order::setTime(unsigned h, unsigned m)
{
    receivedTime.hour = h;
    receivedTime.minute = m;
}

void Order::setTime(Time t)
{
    receivedTime = t;
}

bool Order::addDish(const char *name)
{
    if (name == nullptr) {
        return false;
    }
    size_t len = std::strlen(name);
    if (len > ORDER_MAX_DISH_NAME_LEN) {
        return false;
    }
    if (dishCount >= ORDER_MAX_DISHES) {
        return false;
    }
    for (size_t i = 0; i < dishCount; i++) {
        if (cstrEqual(dishNames[i], name)) {
            return false;
        }
    }
    std::strncpy(dishNames[dishCount], name, ORDER_MAX_DISH_NAME_LEN);
    dishNames[dishCount][ORDER_MAX_DISH_NAME_LEN] = '\0';
    dishCount++;
    return true;
}

size_t Order::getTableNumber() const
{
    return tableNumber;
}

void Order::getTime(unsigned &h, unsigned &m) const
{
    h = receivedTime.hour;
    m = receivedTime.minute;
}

Time Order::getTime() const
{
    return receivedTime;
}

bool Order::isValid() const
{
    return receivedTime.isValid();
}

size_t Order::getDishCount() const
{
    return dishCount;
}

const char *Order::getDishName(size_t index) const
{
    if (index >= dishCount) {
        return nullptr;
    }
    return dishNames[index];
}

bool skipOrderSerialized(std::istream &in)
{
    size_t table = 0;
    unsigned char hm[2] = {0, 0};
    size_t dcount = 0;
    if (!readRaw(in, &table, sizeof(table))) {
        return false;
    }
    if (!readRaw(in, hm, sizeof(hm))) {
        return false;
    }
    if (!readRaw(in, &dcount, sizeof(dcount))) {
        return false;
    }
    for (size_t i = 0; i < dcount; i++) {
        unsigned char len = 0;
        if (!readRaw(in, &len, sizeof(len))) {
            return false;
        }
        if (len > ORDER_MAX_DISH_NAME_LEN) {
            return false;
        }
        char scratch[128];
        if (len > 0) {
            if (!readRaw(in, scratch, len)) {
                return false;
            }
        }
    }
    return true;
}

bool Order::deserialize(std::istream &in)
{
    clearDishes();
    tableNumber = 0;
    receivedTime = {0, 0};

    size_t table = 0;
    unsigned char hm[2] = {0, 0};
    size_t dcount = 0;
    if (!readRaw(in, &table, sizeof(table))) {
        return false;
    }
    if (!readRaw(in, hm, sizeof(hm))) {
        return false;
    }
    if (!readRaw(in, &dcount, sizeof(dcount))) {
        return false;
    }
    if (dcount > ORDER_MAX_DISHES) {
        return false;
    }

    setTableNumber(table);
    setTime(hm[0], hm[1]);

    for (size_t i = 0; i < dcount; i++) {
        unsigned char len = 0;
        if (!readRaw(in, &len, sizeof(len))) {
            clearDishes();
            tableNumber = 0;
            receivedTime = {0, 0};
            return false;
        }
        if (len > ORDER_MAX_DISH_NAME_LEN) {
            clearDishes();
            tableNumber = 0;
            receivedTime = {0, 0};
            return false;
        }
        char buf[128];
        if (len > 0) {
            if (!readRaw(in, buf, len)) {
                clearDishes();
                tableNumber = 0;
                receivedTime = {0, 0};
                return false;
            }
        }
        buf[len] = '\0';
        if (!addDish(buf)) {
            clearDishes();
            tableNumber = 0;
            receivedTime = {0, 0};
            return false;
        }
    }
    return true;
}

bool Order::serialize(std::ostream &out) const
{
    size_t table = tableNumber;
    unsigned char hm[2] = {static_cast<unsigned char>(receivedTime.hour),
                           static_cast<unsigned char>(receivedTime.minute)};
    size_t dcount = dishCount;
    if (!writeRaw(out, &table, sizeof(table))) {
        return false;
    }
    if (!writeRaw(out, hm, sizeof(hm))) {
        return false;
    }
    if (!writeRaw(out, &dcount, sizeof(dcount))) {
        return false;
    }
    for (size_t i = 0; i < dishCount; i++) {
        size_t len = std::strlen(dishNames[i]);
        if (len > ORDER_MAX_DISH_NAME_LEN) {
            return false;
        }
        unsigned char l = static_cast<unsigned char>(len);
        if (!writeRaw(out, &l, sizeof(l))) {
            return false;
        }
        if (len > 0) {
            if (!writeRaw(out, dishNames[i], static_cast<std::streamsize>(len))) {
                return false;
            }
        }
    }
    return true;
}
