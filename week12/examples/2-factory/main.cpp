#include <iostream>
#include <cstring>

class Animal {
public:
    virtual const char* name() const = 0;
    virtual void speak() const = 0;
    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    const char* name() const { return "Dog"; }
    void speak() const { std::cout << "Woof!\n"; }
};

class Cat : public Animal {
public:
    const char* name() const { return "Cat"; }
    void speak() const { std::cout << "Meow!\n"; }
};

class Bird : public Animal {
public:
    const char* name() const { return "Bird"; }
    void speak() const { std::cout << "Tweet!\n"; }
};

class AnimalFactory {
public:
    static Animal* create(const char* type) {
        if (std::strcmp(type, "dog") == 0)  { return new Dog(); }
        if (std::strcmp(type, "cat") == 0)  { return new Cat(); }
        if (std::strcmp(type, "bird") == 0) { return new Bird(); }
        return nullptr;
    }
};

int main() {
    const char* types[] = { "dog", "cat", "bird" };
    const int count = 3;

    for (int i = 0; i < count; i++) {
        Animal* animal = AnimalFactory::create(types[i]);
        if (animal) {
            std::cout << animal->name() << " says: ";
            animal->speak();
            delete animal;
        }
    }

    // Клиентският код не знае нищо за Dog, Cat или Bird.
    // Знае само интерфейса Animal и фабриката.
    Animal* mystery = AnimalFactory::create("cat");
    std::cout << "Mystery animal: ";
    mystery->speak();
    delete mystery;
}
