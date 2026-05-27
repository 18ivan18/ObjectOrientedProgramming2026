#include <iostream>

// -----------------------------------------------------------------------
// Step 1: shared static counter in a plain base class
// -----------------------------------------------------------------------

class Entity {
    static int nextId;
    const int id;
public:
    Entity()               : id(nextId++) {}
    Entity(const Entity&)  : id(nextId++) {} // copy is a new object -> new id
    int getId() const { return id; }
};
int Entity::nextId = 0;

class Animal : public Entity {};
class Vehicle : public Entity {};

// Problem: Animal and Vehicle share the same counter.
// An Animal and a Vehicle can both end up with id == 0 if instantiated
// independently — there is no per-type uniqueness.

// -----------------------------------------------------------------------
// Step 2: CRTP — each derived class gets its own independent counter
//
// "Animal : public UniqueIdentifiable<Animal>" makes the compiler
// instantiate a *separate* class for each T, each with its own static
// nextId.  This is the Curiously Recurring Template Pattern (CRTP).
// -----------------------------------------------------------------------

template<typename T>
class UniqueIdentifiable {
    static int nextId;
    const int id;
public:
    UniqueIdentifiable()                           : id(nextId++) {}
    UniqueIdentifiable(const UniqueIdentifiable&)  : id(nextId++) {} // copy = new object -> new id
    UniqueIdentifiable(UniqueIdentifiable&& other) : id(other.id)  {} // move = relocation -> keep id

    int getId() const { return id; }
    static int count() { return nextId; }
};

template<typename T>
int UniqueIdentifiable<T>::nextId = 0;

class Sensor : public UniqueIdentifiable<Sensor> {
public:
    explicit Sensor(const char* name) : name(name) {}
    const char* name;
};

class Device : public UniqueIdentifiable<Device> {
public:
    explicit Device(const char* model) : model(model) {}
    const char* model;
};

int main() {
    // --- Shared counter (step 1) ---
    std::cout << "=== Shared counter ===\n";
    Animal cat, dog;
    Vehicle car;
    std::cout << "cat id:  " << cat.getId()  << "\n"; // 0
    std::cout << "dog id:  " << dog.getId()  << "\n"; // 1
    std::cout << "car id:  " << car.getId()  << "\n"; // 2  <- continues from Animal!

    // --- CRTP (step 2) ---
    std::cout << "\n=== CRTP: independent counters ===\n";
    Sensor temp("thermometer");
    Sensor pressure("barometer");
    Sensor humidity("hygrometer");

    Device phone("Galaxy");
    Device laptop("MacBook");

    std::cout << "temp id:     " << temp.getId()     << "\n"; // 0
    std::cout << "pressure id: " << pressure.getId() << "\n"; // 1
    std::cout << "humidity id: " << humidity.getId() << "\n"; // 2

    std::cout << "phone id:    " << phone.getId()    << "\n"; // 0  (own counter)
    std::cout << "laptop id:   " << laptop.getId()   << "\n"; // 1

    std::cout << "Sensor::count()  = " << Sensor::count()  << "\n"; // 3
    std::cout << "Device::count()  = " << Device::count()  << "\n"; // 2

    // Copy gets a new id
    Sensor tempCopy = temp;
    std::cout << "tempCopy id: " << tempCopy.getId() << "\n"; // 3
    std::cout << "Sensor::count()  = " << Sensor::count()  << "\n"; // 4

    // Move keeps the id: same logical object, just relocated in memory.
    // Practical reason: vector resizes move objects internally — ids must stay stable.
    Sensor moved = std::move(tempCopy);
    std::cout << "moved id:    " << moved.getId()    << "\n"; // 3 (same as tempCopy — move, not copy)
    std::cout << "Sensor::count()  = " << Sensor::count()  << "\n"; // 4  (no new id was minted)
}
