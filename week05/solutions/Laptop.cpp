#include "Laptop.h"
#include <cstring>
#include <iostream>

char *copyString(const char *str)
{
    if (!str) {
        return nullptr;
    }
    size_t len = strlen(str) + 1;
    char *copy = new char[len];
    strcpy(copy, str);
    return copy;
}

Laptop::Laptop()
    : brand(nullptr), model(nullptr), price(0), screenSizeInches(0),
      processor{0, 0, 0}, ramGB(0), batteryCapacityMAh(0)
{
}

Laptop::Laptop(const Laptop &other)
    : brand(copyString(other.brand)), model(copyString(other.model)),
      price(other.price), screenSizeInches(other.screenSizeInches),
      processor(other.processor), ramGB(other.ramGB),
      batteryCapacityMAh(other.batteryCapacityMAh)
{
}

Laptop::Laptop(const char *b, const char *m, double p, double screen,
               double cpuFreq, int cores, int cacheKB, int ram, int battery)
    : brand(copyString(b)), model(copyString(m)),
      price(p), screenSizeInches(screen),
      processor{cpuFreq, cores, cacheKB}, ramGB(ram), batteryCapacityMAh(battery)
{
}

Laptop::~Laptop()
{
    clear();
}

Laptop &Laptop::operator=(const Laptop &other)
{
    if (this != &other)
    {
        clear();
        copyFrom(other);
    }
    return *this;
}

void Laptop::clear()
{
    delete[] brand;
    delete[] model;
    brand = nullptr;
    model = nullptr;
}

void Laptop::copyFrom(const Laptop &other)
{
    brand = copyString(other.brand);
    model = copyString(other.model);
    price = other.price;
}

bool Laptop::operator<(const Laptop &other) const
{
    return screenSizeInches < other.screenSizeInches;
}

bool Laptop::operator>(const Laptop &other) const
{
    return screenSizeInches > other.screenSizeInches;
}

bool Laptop::operator==(const Laptop &other) const
{
    return screenSizeInches == other.screenSizeInches;
}

bool Laptop::operator!=(const Laptop &other) const
{
    return screenSizeInches != other.screenSizeInches;
}

void Laptop::upgradeProcessor(double newFreq, int newCores, int newCacheKB)
{
    processor.clockFrequency = newFreq;
    processor.cores = newCores;
    processor.cacheSizeKB = newCacheKB;
}

void Laptop::upgradeRAM(int newRamGB)
{
    ramGB = newRamGB;
}

const char *Laptop::getBrand() const
{
    return brand ? brand : "";
}

const char *Laptop::getModel() const
{
    return model ? model : "";
}
void Laptop::print() const
{
    std::cout << getBrand() << " " << getModel() << "\n";
    std::cout << "  Цена: " << price << " лв\n";
    std::cout << "  Екран: " << screenSizeInches << "\"\n";
    std::cout << "  Процесор: " << processor.clockFrequency << " GHz, "
              << processor.cores << " ядра, " << processor.cacheSizeKB << " KB кеш\n";
    std::cout << "  RAM: " << ramGB << " GB\n";
    std::cout << "  Батерия: " << batteryCapacityMAh << " mAh\n";
}
