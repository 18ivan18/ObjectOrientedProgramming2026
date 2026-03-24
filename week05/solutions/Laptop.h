#ifndef LAPTOP_H
#define LAPTOP_H

#include <cstddef>

char *copyString(const char *str);


struct Processor
{
    double clockFrequency;
    int cores;
    int cacheSizeKB;
};

class Laptop
{
private:
    char *brand;
    char *model;
    double price;
    double screenSizeInches;
    Processor processor;
    int ramGB;
    int batteryCapacityMAh;

    void clear();
    void copyFrom(const Laptop &other);
public:
    Laptop();
    Laptop(const Laptop &other);
    Laptop(const char *brand, const char *model, double price, double screenSize,
           double cpuFreq, int cores, int cacheKB, int ramGB, int batteryMAh);
    ~Laptop();

    Laptop &operator=(const Laptop &other);

    bool operator<(const Laptop &other) const;
    bool operator>(const Laptop &other) const;
    bool operator==(const Laptop &other) const;
    bool operator!=(const Laptop &other) const;

    void upgradeProcessor(double newFreq, int newCores, int newCacheKB);
    void upgradeRAM(int newRamGB);
    void print() const;

    const char *getBrand() const;
    const char *getModel() const;
};

#endif
