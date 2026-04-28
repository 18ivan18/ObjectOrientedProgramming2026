#ifndef FUEL_TYPE_H
#define FUEL_TYPE_H

enum class FuelType {
    Unknown = 0,
    Petrol,
    Diesel,
    LPG,
    Hybrid,
    Electric
};

inline const char* toString(FuelType fuelType) {
    switch (fuelType) {
    case FuelType::Petrol:
        return "petrol";
    case FuelType::Diesel:
        return "diesel";
    case FuelType::LPG:
        return "lpg";
    case FuelType::Hybrid:
        return "hybrid";
    case FuelType::Electric:
        return "electric";
    case FuelType::Unknown:
    default:
        return "unknown";
    }
}

#endif // FUEL_TYPE_H
