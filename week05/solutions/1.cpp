// Компилиране: g++ -o 1 1.cpp Laptop.cpp
#include "Laptop.h"
#include <iostream>

int main()
{
    Laptop defaultLaptop;
    std::cout << "По подразбиране:\n";
    defaultLaptop.print();

    Laptop laptop("Lenovo", "ThinkPad X1", 2500, 14.0, 2.8, 8, 8192, 16, 5000);
    std::cout << "\n";
    laptop.print();

    Laptop copy(laptop);
    std::cout << "\nКопие - екран: " << (copy < laptop ? "по-малък" : "същият или по-голям") << '\n';

    Laptop small("Acer", "Swift", 800, 13.3, 2.4, 4, 4096, 8, 4000);
    std::cout << "\nСравнение екрани: laptop(14\") " << (laptop > small ? ">" : "<=") << " small(13.3\")\n";
    std::cout << "laptop == small? " << (laptop == small ? "да" : "не") << '\n';

    laptop.upgradeRAM(32);
    laptop.upgradeProcessor(3.2, 12, 12288);
    std::cout << "\nСлед upgrade:\n";
    laptop.print();
}
