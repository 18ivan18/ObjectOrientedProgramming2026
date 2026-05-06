// c++ -std=c++17 -Wall -Wextra UniqueInstance.cpp main.cpp -o main
#include <iostream>

#include "UniqueInstance.h"

int main()
{
    UniqueInstance a;
    UniqueInstance b;
    UniqueInstance c = a; // copy-construct => new id

    const std::size_t bIdBefore = b.getId();
    b = a; // assignment => b keeps its id
    const std::size_t bIdAfter = b.getId();

    std::cout << "a.id = " << a.getId() << "\n";
    std::cout << "b.id = " << b.getId() << "\n";
    std::cout << "c.id = " << c.getId() << "\n";
    std::cout << "b assignment kept id: " << (bIdBefore == bIdAfter) << "\n";
    std::cout << "nextId = " << UniqueInstance::getNextId() << "\n";
}
